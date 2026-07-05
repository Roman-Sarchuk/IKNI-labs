package prg;

import mpi.*;


public class AlgebraUtil {
    String[] args;

    AlgebraUtil(String[] args) {
        this.args = args;
    }

    public double[] multiply(double[][] matrix, int rowM, int colM, double[] vector, int sizeV) {
        // Init
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.Rank();
        int size = MPI.COMM_WORLD.Size();   // p
        int rowBlockCount = 2;              // s
        int colBlockCount = size / 2;       // q
        /* p=s*q */

        int rowCell = rowM / rowBlockCount;
        int colCell = colM / colBlockCount;
        int cellElemCount = rowCell * colCell;

        // Sent the block of vector
        double[] localV = new double[colCell];

        if (rank < colBlockCount) {
            // processors 0..3
            MPI.COMM_WORLD.Scatter(vector, 0, colCell, MPI.DOUBLE,
                    localV, 0, colCell, MPI.DOUBLE, 0);
        } else {
            // processors 4..7 recive the same as the processors 0..3
            int sameAs = rank - colBlockCount; // тобто 4→0, 5→1, 6→2, 7→3
            MPI.COMM_WORLD.Bcast(localV, 0, colCell, MPI.DOUBLE, sameAs);
        }

        // Sent the block of matrix
        double[][] localA = new double[rowCell][colCell];

        double[] sendBuffer = null;
        if (rank == 0) {
            sendBuffer = new double[rowM * colM];
            for (int r = 0; r < rowBlockCount; r++)
                for (int c = 0, blockIndex, start; c < colBlockCount; c++) {
                    blockIndex = r * colBlockCount + c;
                    start = blockIndex * cellElemCount;
                    for (int i = 0; i < rowCell; i++)
                        System.arraycopy(matrix[r * rowCell + i], c * colCell, sendBuffer, start + i * colCell, colCell);
                }
        }

        double[] localBuffer = new double[cellElemCount];
        MPI.COMM_WORLD.Scatter(sendBuffer, 0, cellElemCount, MPI.DOUBLE,
                localBuffer, 0, cellElemCount, MPI.DOUBLE, 0);

        // Fill localA
        for (int i = 0; i < rowCell; i++)
            System.arraycopy(localBuffer, i * colCell, localA[i], 0, colCell);

        // Calculation
        double[] localResult = new double[rowCell];
        for (int i = 0; i < rowCell; i++)
            for (int j = 0; j < colCell; j++)
                localResult[i] += localA[i][j] * localV[j];

        double[] partialSum = new double[rowCell];

        int color = rank % colBlockCount; // 0..3
        Intracomm columnComm = MPI.COMM_WORLD.Split(color, rank);

        columnComm.Reduce(localResult, 0, partialSum, 0, rowCell, MPI.DOUBLE, MPI.SUM, 0);

        // Gather result
        double[] result = null;
        if (rank == 0)
            result = new double[rowM];

        // тільки процеси 0 і 1, 2, 3 мають повні частини, їх і збираємо
        if (rank < colBlockCount) {
            MPI.COMM_WORLD.Gather(partialSum, 0, rowCell, MPI.DOUBLE,
                    result, 0, rowCell, MPI.DOUBLE, 0);
        }

        // Finalize
        MPI.Finalize();

        return result;
    }
}