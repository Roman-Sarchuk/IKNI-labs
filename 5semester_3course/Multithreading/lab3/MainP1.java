package lab3;

import java.util.Scanner;


public class MainP1 {
    private static int count;

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
        
        // Calc with one-time assignment
        count = 0;
        
        System.out.println("\nCalculating Y=A*B with one-time assignment...");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int c[] = new int[n+1];
                for (int k = 0; k < n; k++) {
                    c[k+1] = c[k] + a[i][k] * b[k][j];
                    count++;
                }
                y[i][j] = c[n];
            }
        }
        Utilities.printMatrix(y, n, "Y=A*B");
        System.out.println("\nCount of operations: " + count);

        // end
        scanner.close();
    }
}
