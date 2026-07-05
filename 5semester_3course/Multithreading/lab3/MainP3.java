package lab3;

import java.util.Scanner;


public class MainP2 {
    private static int count; // Current row index

    public static void main(String[] args) {
        // Enter n
        Scanner scanner = new Scanner(System.in);
        int n = Utilities.getN(scanner);

        // init the matrixes
        int a[][] = new int[n][n];
        int b[][] = new int[n][n];
        int y[][] = new int[n][n];

        Utilities.fillA(a, n);
        Utilities.fillB(b, n);

        System.out.println();
        Utilities.printMatrix(a, n, "A");
        System.out.println();
        Utilities.printMatrix(b, n, "B");

        // Calc with recursion
        count = 0;
        System.out.println("\nCalculating Y=A*B with recursion...");
        recursiveMultiply(y, a, b, n, 0, 0);
        Utilities.printMatrix(y, n, "Y=A*B");
        System.out.println("\nCount of operations: " + count);

        // end
        scanner.close();
    }


    private static void recursiveMultiply(int y[][], int[][] a, int[][] b, int n, int i, int j) {
    if (i >= n) return;
    if (j >= n) {
        recursiveMultiply(y, a, b, n, i + 1, 0);
        return;
    }

    int sum = 0;
    for (int k = 0; k < n; k++) {
        sum += a[i][k] * b[k][j];
    }
    y[i][j] = sum;

    recursiveMultiply(y, a, b, n, i, j + 1);
}

    private static int computeSum(int[][] a, int[][] b, int n, int i, int j, int k) {
        if (k >= n) {
            return 0; // all elements processed
        }
        count++;
        return computeSum(a, b, n, i, j, k+1) + a[i][k] * b[k][j];
    }
}
