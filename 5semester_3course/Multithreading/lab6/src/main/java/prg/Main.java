package prg;


public class Main {
    // Utils
    static final boolean SHOW_INPUT_DATA = false;
    // Sizes
    static int rowM = 80;
    static int colM = 120;

    public static void main(String[] args) throws Exception {
        // Init data
        double[][] A = new double[rowM][colM];
        double[] b =  new double[colM];

        // Fill data (0-10)
        for (int j = 0; j < colM; j++) {
            b[j] = (int) (Math.random() * 11);
            for (int i = 0; i < rowM; i++) {
                A[i][j] = (int) (Math.random() * 11);
            }
        }

        // Show input data
        if (SHOW_INPUT_DATA) {
            printMatrix("Matrix", A, rowM, colM);
            System.out.println();
            printVector("Vector", b, colM);
            System.out.println();
        }

        // Calculate
        AlgebraUtil algebraUtil = new AlgebraUtil(args);
        double[] c = algebraUtil.multiply(A, rowM, colM, b, colM);

        // Show result
        printVector("Result", c, rowM);
    }

    public static void printMatrix(String name, double[][] data, int row, int col) {
        synchronized (System.out) {
            System.out.println("Matrix " + name + ":");
            for (int i = 0; i < row; i++) {
                System.out.print("|\t");
                for (int j = 0; j < col; j++) {
                    System.out.print(data[i][j] + "\t");
                }
                System.out.println("|");
            }
            System.out.println("");
        }
    }

    public static void printVector(String name, double[] data, int size) {
        synchronized (System.out) {
            System.out.println("Vector " + name + ":");
            System.out.print("|\t");
            for (int i = 0; i < size; i++) {
                System.out.print(data[i] + "\t");
            }
            System.out.println("|");
            System.out.println("");
        }
    }
}