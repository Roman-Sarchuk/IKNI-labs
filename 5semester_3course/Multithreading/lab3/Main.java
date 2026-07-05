package lab3;

import java.util.Scanner;


public class Main {
    private static final boolean SHOW_AB = false;
    private static final boolean SHOW_Y = false;
    private static int totalOperations;

    public static void main(String[] args) {
        // Enter n
        Scanner scanner = new Scanner(System.in);
        int n = Utilities.getN(scanner);
        System.out.println();

        // init the matrixes
        int A[][] = new int[n][n];
        int B[][] = new int[n][n];
        int Y[][] = new int[n][n];

        Utilities.fillA(A, n);
        Utilities.fillB(B, n);

        if (SHOW_AB) {
            Utilities.printMatrix(A, n, "A");
            Utilities.printMatrix(B, n, "B");
            System.out.println();
        }
        
        // Calc with one-time assignment
        int c[][][] = oneTimeAssignment(A, B, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                Y[i][j] = c[i][j][n];
            }
        }
        if (SHOW_Y)
            Utilities.printMatrix(Y, n, "Y (OTA)");

        System.out.println();
        // Calc with optimized local Recursive
        Y = optimizedLocalRecursive(A, B, n);
        if (SHOW_Y)
            Utilities.printMatrix(Y, n, "Y (OLR)");

        // end
        scanner.close();
    }

    private static int[][][] oneTimeAssignment(int[][] A, int[][] B, int n) {
        totalOperations = 0;
        int С[][][] = new int[n][n][n+1];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    С[i][j][k+1] = С[i][j][k] + A[i][k] * B[k][j];
                    totalOperations++;
                }
            }
        }

        System.out.println("One Time Assignment: ");
        System.out.println("totalOperations = " + totalOperations);
        return С;
    }

    private static int[][] optimizedLocalRecursive(int[][] A, int[][] B, int n) {
        totalOperations = 0;

        int C[][][] = new int[n+1][n][n];
        int A3D[][][] = new int[n][n][n];
        int B3D[][][] = new int[n][n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A3D[0][i][j] = A[i][j];
                B3D[0][i][j] = B[i][j];
            }
        }

        if (n <= 40)
            OpLcRecursiveF(C, A3D, B3D, n, 0, 0, 0);
        else if (n <= 80) 
            OpLcRecursiveH(C, A3D, B3D, n, 0, 0);
        else
            OpLcRecursiveC(C, A3D, B3D, n);

        System.out.println("Optimized Local Recursive: ");
        System.out.println("totalOperations = " + totalOperations);
        return C[n];
    }

    private static void OpLcRecursiveF(int C[][][], int A[][][], int B[][][], int n, int i, int j, int r) {
        if (i >= n) 
            return;
        if (j >= n) {
            OpLcRecursiveF(C, A, B, n, i+1, 0, 0);
            return;
        }
        if (r >= n) {
            OpLcRecursiveF(C, A, B, n, i, j+1, 0);
            return;
        }

        if (r < n - 1) {
            A[r + 1][i][j] = A[r][i][j];
            B[r + 1][i][j] = B[r][i][j];
        } else {
            A[0][i][j] = A[r][i][j];
            B[0][i][j] = B[r][i][j];
        }

        if (A[r][i][r] != 0 && B[r][r][j] != 0)
        {
            C[r+1][i][j] = C[r][i][j] + A[r][i][r] * B[r][r][j];
            totalOperations++;
        }
        else {
            C[r+1][i][j] = C[r][i][j];
        }

        OpLcRecursiveF(C, A, B, n, i, j, r+1);
    }

    private static void OpLcRecursiveH(int C[][][], int A[][][], int B[][][], int n, int i, int j) {
        if (i >= n) 
            return;
        if (j >= n) {
            OpLcRecursiveH(C, A, B, n, i+1, 0);
            return;
        }

        for (int r = 0; r < n; r++) {
            if (r < n - 1) {
                A[r + 1][i][j] = A[r][i][j];
                B[r + 1][i][j] = B[r][i][j];
            } else {
                A[0][i][j] = A[r][i][j];
                B[0][i][j] = B[r][i][j];
            }

            if (A[r][i][r] != 0 && B[r][r][j] != 0)
            {
                C[r+1][i][j] = C[r][i][j] + A[r][i][r] * B[r][r][j];
                totalOperations++;
            }
            else {
                C[r+1][i][j] = C[r][i][j];
            }
        }

        OpLcRecursiveH(C, A, B, n, i, j+1);
    }

    private static void OpLcRecursiveC(int C[][][], int A[][][], int B[][][], int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int r = 0; r < n; r++) {
                    if (r < n - 1) {
                        A[r + 1][i][j] = A[r][i][j];
                        B[r + 1][i][j] = B[r][i][j];
                    } else {
                        A[0][i][j] = A[r][i][j];
                        B[0][i][j] = B[r][i][j];
                    }

                    if (A[r][i][r] != 0 && B[r][r][j] != 0)
                    {
                        C[r+1][i][j] = C[r][i][j] + A[r][i][r] * B[r][r][j];
                        totalOperations++;
                    }
                    else {
                        C[r+1][i][j] = C[r][i][j];
                    }
                }
            }
        }
    }
}
