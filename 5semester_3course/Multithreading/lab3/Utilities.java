package lab3;

import java.util.Random;
import java.util.Scanner;


class Utilities {
    public static int getN(Scanner scanner) {
        int n;
        while (true) {
            System.out.print("Enter n: ");
            if (scanner.hasNextInt()) {
                n = scanner.nextInt();
                if (n>=2 && n<=600) { break; }
            } else {
                scanner.next(); // skip the incorrect input
            }
            System.out.println("Incorrect input! The Number n must be >= 2 and <=600");
       }
       return n;
    }

    public static void fillA(int[][] a, int n) {
        /* Fill the main diagonal of the matrix with descending numbers from n to 1 */
        for (int i = 0; i < n; i++) {
            a[i][i] = n - i;
        }
    }   

    public static void fillB(int[][] b, int n) {
        /* Fill the upper triangular part of the matrix with random numbers in the range [1, 10] */
        Random rand = new Random();
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                b[i][j] = rand.nextInt(10) + 1;
            }
        }
    }   

    public static void printMatrix(int[][] matrix, int n, String name) {
        System.out.println("Matrix " + name + ":");
        for (int i = 0; i < n; i++) {
            System.out.print("|\t");
            for (int j = 0; j < n; j++) {
                System.out.print(matrix[i][j] + "\t");
            }
            System.out.println("|");
        }
    }
}
