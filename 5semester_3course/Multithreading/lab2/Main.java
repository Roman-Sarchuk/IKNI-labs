 package lab2;

import java.util.Scanner;
import java.util.concurrent.ThreadLocalRandom;
import java.io.*;


class AlgebraUtils {
    // adding
    public static Matrix add(Matrix matrix1, Matrix matrix2) {
        if (matrix1.n != matrix2.n) {
            throw new IllegalArgumentException("The matrix size must be the same!");
        } 

        Matrix result = new Matrix(matrix1.n);
        for (int i = 0; i < matrix1.n; i++) {
            for (int j = 0; j < matrix1.n; j++) {
                result.data[i][j] = matrix1.data[i][j] + matrix2.data[i][j];
            }
        } 

        return result;
    }

    public static Vector add(Vector vector1, Vector vector2) {
        if (vector1.n != vector2.n) {
            throw new IllegalArgumentException("The vector size must be the same!");
        } 

        Vector result = new Vector(vector1.n);
        for (int i = 0; i < vector1.n; i++) {
            for (int j = 0; j < vector1.n; j++) {
                result.data[i] = vector1.data[i] + vector2.data[i];
            }
        } 
        return result;
    }

    // subtraction
    public static Matrix subtraction(Matrix matrix1, Matrix matrix2) {
        if (matrix1.n != matrix2.n) {
            throw new IllegalArgumentException("The matrix size must be the same!");
        } 

        Matrix result = new Matrix(matrix1.n);
        for (int i = 0; i < matrix1.n; i++) {
            for (int j = 0; j < matrix1.n; j++) {
                result.data[i][j] = matrix1.data[i][j] - matrix2.data[i][j];
            }
        } 

        return result;
    }

    public static Vector subtraction(Vector vector1, Vector vector2) {
        if (vector1.n != vector2.n) {
            throw new IllegalArgumentException("The vector size must be the same!");
        } 

        Vector result = new Vector(vector1.n);
        for (int i = 0; i < vector1.n; i++) {
            for (int j = 0; j < vector1.n; j++) {
                result.data[i] = vector1.data[i] - vector2.data[i];
            }
        } 
        return result;
    }

    // multiplying
    public static Matrix multiply(Matrix matrix1, Matrix matrix2) {
        if (matrix1.n != matrix2.n) {
            throw new IllegalArgumentException("The matrix1 column size must be the same as the matrix2 row size!");
        } 

        Matrix result = new Matrix(matrix1.n);
        
        for (int i = 0; i < matrix1.n; i++) {
            for (int j = 0; j < matrix1.n; j++) {
                result.data[i][j] = matrix1.data[i][0] * matrix2.data[0][j];
                for (int k = 1; k < matrix1.n; k++) {
                    result.data[i][j] += matrix1.data[i][k] * matrix2.data[k][j];
                }
            }
        }

        return result;
    }

    public static Vector multiply(Matrix matrix, Vector vector) {
        if (matrix.n != vector.n) {
            throw new IllegalArgumentException("The matrix column size must be the same as the vector size!");
        } 

        Vector result = new Vector(matrix.n);
        
        for (int i = 0; i < matrix.n; i++) {
            result.data[i] = matrix.data[i][0] * vector.data[0];
            for (int k = 1; k < matrix.n; k++) {
                result.data[i] += matrix.data[i][k] * vector.data[k];
            }
        }

        return result;
    }

    public static Vector multiply(Vector vector, Matrix matrix) {
        if (matrix.n != vector.n) {
            throw new IllegalArgumentException("The vector size must be the same as the matrix row size!");
        } 

        Vector result = new Vector(matrix.n);
        
        for (int j = 0; j < matrix.n; j++) {
            result.data[j] = vector.data[0] * matrix.data[0][j];
            for (int k = 1; k < matrix.n; k++) {
                result.data[j] += vector.data[k] * matrix.data[k][j];
            }
        }

        return result;
    }

    public static double multiply(Vector vector1, Vector vector2) {
        if (vector1.n != vector2.n) {
            throw new IllegalArgumentException("The vector1 size must be the same as the vactor2 size!");
        } 

        double result = 0;

        for (int k = 0; k < vector1.n; k++) {
            result += vector1.data[k] * vector2.data[k];
        }

        return result;
    }

    public static Matrix multiply(Matrix matrix, double c) {
        Matrix result = new Matrix(matrix.n);

        for (int i = 0; i < matrix.n; i++) {
            for (int j = 0; j < matrix.n; j++) {
                result.data[i][j] = matrix.data[i][j] * c;
            }
        }

        return result;
    }

    public static Matrix multiply(double c, Matrix matrix) {
        return multiply(matrix, c);
    }

    public static Vector multiply(Vector vector, double c) {
        Vector result = new Vector(vector.n);

        for (int i = 0; i < vector.n; i++) {
            result.data[i] = vector.data[i] * c;
        }

        return result;
    }

    public static Vector multiply(double c, Vector vector) {
        return multiply(vector, c);
    }

    // transpose
    public static Matrix transpose(Matrix matrix) {
        Matrix reslut = new Matrix(matrix.n);

        for (int i = 0; i < matrix.n; i++) {
            for (int j = 0; j < matrix.n; j++) {
                reslut.data[i][j] = matrix.data[j][i];
            }
        }

        return reslut;
    }
}


interface Fillable {
    double minRand = 1;
    double maxRand = 101;

    public void fillRandomly();
    public void inputData(Scanner scanner);
    public void printData();
}


class Matrix implements Fillable {
    int n;
    double[][] data;
    String name;
    
    Matrix(int n, String name) {
        this.n = n;
        this.name = name;
        data = new double[n][n];
    }

    Matrix(int n) {
        this(n, "None");
    }

    public void fillRandomly() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                data[i][j] = ThreadLocalRandom.current().nextDouble(minRand, maxRand);
            }
        }
        System.out.println(name + " is filled randomly");
    }

    public void inputData(Scanner scanner) {
        System.out.println("Enter matrix " + name + ":");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                while (true) {
                    System.out.print("Enter element [" + i + "][" + j + "]: ");
                    if (scanner.hasNextDouble()) {
                        data[i][j] = scanner.nextDouble();
                        break;
                    } else {
                        System.out.println("Incorrect value! It must be a number");
                        scanner.next(); // skip the incorrect input
                    }
                }
            }
        }
    }

    public void printData() {
        synchronized (System.out) {
            System.out.println("Matrix " + name + ":");
            for (int i = 0; i < n; i++) {
                System.out.print("|\t");
                for (int j = 0; j < n; j++) {
                    System.out.print(data[i][j] + "\t");
                }
                System.out.println("|");
            }
            System.out.println("");
        }
    }

    public void setData(Matrix matrix) {
        data = matrix.data;
    }

    public void setDataWithPrint(Matrix matrix) {
        setData(matrix);
        printData();
    }
}


class Vector implements Fillable {
    int n;
    double[] data;
    String name;

    Vector(int n, String name) {
        this.n = n;
        this.name = name;
        data = new double[n];
    }

    Vector(int n) {
        this(n, "None");
    }

    public void fillRandomly() {
        for (int i = 0; i < n; i++) {
            data[i] = ThreadLocalRandom.current().nextDouble(minRand, maxRand);
        }
        System.out.println(name + " is filled randomly");
    }

    public void inputData(Scanner scanner) {
        System.out.println("Vector " + name + ":");
        for (int i = 0; i < n; i++) {
            while (true) {
                System.out.print("Enter element [" + i + "]: ");
                if (scanner.hasNextDouble()) {
                    data[i] = scanner.nextDouble();
                    break;
                } else {
                    System.out.println("Incorrect value! It must be a number");
                    scanner.next(); // skip the incorrect input
                }
            }
        }
    }

    public void printData() {
        synchronized (System.out) {
            System.out.println("Vector " + name + ":");
            System.out.print("|\t");
            for (int i = 0; i < n; i++) {
                System.out.print(data[i] + "\t");
            }
            System.out.println("|");
            System.out.println("");
        }
    }

    public void setData(Vector vector) {
        data = vector.data;
    }

    public void setDataWithPrint(Vector vector) {
        setData(vector);
        printData();
    }
}


class Constant {
    double data;
    String name = "None";

    public void setData(double number) {
        data = number;
    }

    public void setDataWithPrint(double number) {
        setData(number);
        synchronized (System.out) {
            System.out.println("Constant " + name + ":");
            System.out.println(data);
            System.out.println("");
        }
    }
}


class ThreadPool {
    Thread[] pool;

    ThreadPool(int size) {
        pool = new Thread[size];
    }

    public void start(int i, Runnable task) {
        pool[i] = new Thread(task);
        pool[i].start();
    }

    public void cycleJoin(int start, int end) {
        for (int i = start; i < end; i++) {
            join(i);
        }
    }

    public void cycleJoin(int count) {
        cycleJoin(0, count);
    }
    

    public void join(int i) {
        try {
            pool[i].join();
        } catch (InterruptedException e) {
            e.printStackTrace();
            Thread.currentThread().interrupt();
        }
    }
}


public class Main {
    static int n;
    static Matrix A, A1, A2, B2, C2, Y3;
    static Vector b, b1, c1, y1, y2, x;
    // input: n, A, A1, A2, B2, b1, c1
    // calc: C2, b
    // res: y1, y2, Y3, x

    public static void main(String[] args) {
        // === INPUT ===
        // input n
        System.out.println("=== INPUT ===");
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.print("1) Enter n: ");
            if (scanner.hasNextInt()) {
                n = scanner.nextInt();
                if (n>=3 && n<=8000) { break; }
            } else {
                scanner.next(); // skip the incorrect input
            }
            System.out.println("Incorrect input! The Number n must be >= 3 and <=8000");
       }
        // initializing
        A = new Matrix(n, "A");
        A1 = new Matrix(n, "A1");
        A2 = new Matrix(n, "A2");
        B2 = new Matrix(n, "B2");
        C2 = new Matrix(n, "C2");
        Y3 = new Matrix(n, "Y3");
        b = new Vector(n, "b");
        b1 = new Vector(n, "b1");
        c1 = new Vector(n, "c1");
        y1 = new Vector(n, "y1");
        y2 = new Vector(n, "y2");
        x = new Vector(n, "x");
        Matrix[] inputMatrices = {A, A1, A2, B2};
        Vector[] inputVectors = {b1, c1};
        ThreadPool threadPool = new ThreadPool(inputMatrices.length + inputVectors.length);
        
        // calc b & C2;
        System.out.println("");
        threadPool.start(0, () -> calcVectorb());
        threadPool.start(1, () -> calcMatrixC());

        threadPool.cycleJoin(2);

        // input Vectors & Matrices
        System.out.println("\n2) Choose a option number:");
        System.out.println("1. Fill in randomly");
        System.out.println("2. Enter your own");
        int option;
        while (true) {
            System.out.print("> ");
            if (scanner.hasNextInt()) {
                option = scanner.nextInt();
                if (option == 1) {
                    System.out.println("");
                    // randomly
                    byte i = 0;
                    for (Vector v : inputVectors) {
                        threadPool.start(i, () -> v.fillRandomly());
                        i++;
                    }
                    for (Matrix m : inputMatrices) {
                        threadPool.start(i, () -> m.fillRandomly());
                        i++;
                    }
                    threadPool.cycleJoin(inputMatrices.length + inputVectors.length);
                    break;
                }
                else if (option == 2) {
                    System.out.println("");
                    // entering
                    for (Vector v : inputVectors) {
                        v.inputData(scanner);
                    }
                    for (Matrix m : inputMatrices) {
                        m.inputData(scanner);
                    }
                    break;
                }
            } else {
                scanner.next(); // skip the incorrect input
            }
            System.out.println("Incorrect the option number! It must be 1 or 2");
        } 
        scanner.close();
        System.out.println("=== ===== ===\n");

        // I/O interception into the output.txt file
        PrintStream console = System.out;
        try {
            PrintStream fileOut = new PrintStream(new FileOutputStream("lab2/output.txt"));
            System.setOut(new PrintStream(new OutputStream() {
                @Override
                public void write(int b) throws IOException {
                    console.write(b);
                    fileOut.write(b);
                }
            }));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        // === DATA ===
        System.out.println("=== DATA ===");
        for (Vector v : inputVectors) {
            v.printData();
        }
        b.printData();
        for (Matrix m : inputMatrices) {
            m.printData();
        }
        C2.printData();
        System.out.println("=== ==== ===\n");


        // === CALCULATION ===
        System.out.println("=== CALCULATION ===");
        Matrix tempM1 = new Matrix(n), tempM2 = new Matrix(n);
        Vector tempV1 = new Vector(n), tempV2 = new Vector(n), tempV3 = new Vector(n), tempV4 = new Vector(n);

        //// Level 1
        System.out.println("//// Level 1");
        // y1 = A*b
        threadPool.start(0, () -> y1.setDataWithPrint(AlgebraUtils.multiply(A, b)));

        // b1+20*c1  -> v1 (avaliable after Level 2)
        tempV1.name = "b1+20*c1";
        threadPool.start(1, () -> tempV1.setDataWithPrint(AlgebraUtils.add(b1, AlgebraUtils.multiply(20, c1))));

        // A2*B2  -> M1 (avaliable after Level 2)
        tempM1.name = "A2*B2";
        threadPool.start(2, () -> tempM1.setDataWithPrint(AlgebraUtils.multiply(A2, B2)));

        threadPool.cycleJoin(3);

        //// Level 2
        System.out.println("//// Level 2");
        // y2 = A1*(b1+20*c1)
        threadPool.start(0, () -> y2.setDataWithPrint(AlgebraUtils.multiply(A1, tempV1)));

        // Y3 = A2*B2-C2
        threadPool.start(1, () -> Y3.setDataWithPrint(AlgebraUtils.subtraction(tempM1, C2)));

        threadPool.cycleJoin(2);

        //// Level 3
        System.out.println("//// Level 3");
        // y2'*y2  -> c
        Constant tempC = new Constant();
        tempC.name = "y2'*y2";
        threadPool.start(0, () -> tempC.setDataWithPrint(AlgebraUtils.multiply(y2, y2)));
        
        // Y3*y1  -> v1 (avaliable after Level 5)
        tempV1.name = "Y3*y1";
        threadPool.start(1, () -> tempV1.setDataWithPrint(AlgebraUtils.multiply(Y3, y1)));

        // Y3^2  -> M1 (avaliable after Level 7)
        tempM1.name = "Y3^2";
        threadPool.start(2, () -> tempM1.setDataWithPrint(AlgebraUtils.multiply(Y3, Y3)));

        threadPool.join(3);

        //// Level 4
        System.out.println("//// Level 4");
        // y2'*y2*Y3  -> M2 (avaliable after Level 5)
        tempM2.name = "y2'*y2*Y3";
        threadPool.start(0, () -> tempM2.setDataWithPrint(AlgebraUtils.multiply(tempC.data, Y3)));
        
        // Y3^2*y2  -> v2 (avaliable after Level 5)
        tempV2.name = "Y3^2*y2";
        threadPool.start(1, () -> tempV2.setDataWithPrint(AlgebraUtils.multiply(tempM1, y2)));

        threadPool.cycleJoin(2);

        //// Level 5
        System.out.println("//// Level 5");
        // y2'*y2*Y3*y1  -> v3 (avaliable after Level 6)
        tempV3.name = "y2'*y2*Y3*y1";
        threadPool.start(0, () -> tempV3.setDataWithPrint(AlgebraUtils.multiply(tempM2, y1)));

        // Y3^2*y2+Y3*y1  -> v4 (avaliable after Level 6)
        tempV4.name = "Y3^2*y2+Y3*y1";
        threadPool.start(1, () -> tempV4.setDataWithPrint(AlgebraUtils.add(tempV2, tempV1)));

        threadPool.cycleJoin(2);

        //// Level 6
        System.out.println("//// Level 6");
        // Y3^2*y2+Y3*y1+y2'*y2*Y3*y1  -> v1 (avaliable after Level 7)
        tempV1.name = "Y3^2*y2+Y3*y1+y2'*y2*Y3*y1";
        threadPool.start(0, () -> tempV1.setDataWithPrint(AlgebraUtils.add(tempV4, tempV3)));

        threadPool.join(0);

        //// Level 7
        System.out.println("//// Level 7");
        // x = (Y3^2*y2+Y3*y1+y2'*y2*Y3*y1)'*Y3^2
        threadPool.start(0, () -> x.setDataWithPrint(AlgebraUtils.multiply(tempV1, tempM1)));

        threadPool.join(0);
        System.out.println("=== =========== ===");
        

        // --- RESULT ---
        System.out.println("\n--- RESULT ---");
        x.printData();
    }

    private static void calcVectorb() {
        for (int i = 1; i <= b.n; i++) {
            b.data[i-1] = 21.0 / Math.pow(i, 4.0);
        }
        System.out.println("The vector b is calculated");
    }

    private static void calcMatrixC() {
        double determinator;
        for (int i = 1; i <= b.n; i++) {
            for (int j = 1; j <= b.n; j++) {
                determinator = i*i-2.0*j;
                if (determinator != 0) {
                    C2.data[i-1][j-1] = 21.0/determinator;
                } else {
                    C2.data[i-1][j-1] = 0;
                }
            }
        }
        System.out.println("The matrix C2 is calculated");
    }
}
