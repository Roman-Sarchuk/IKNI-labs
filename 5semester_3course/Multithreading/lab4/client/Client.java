import java.util.Scanner;
import java.util.concurrent.ThreadLocalRandom;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;


public class Client {
    static final String SERVER_IP = "127.0.0.1";
    static final int SERVER_PORT = 9000;
    static final String STUB_NAME = "algebrautils";

    static final boolean SHOW_DATA = false;
    static final boolean SHOW_CALCULATION = false;

    static int n;
    static double[][] A, A1, A2, B2, C2, Y3;
    static double[] b, b1, c1, y1, y2, x;

    static double[][] tempM1, tempM2;
    static double[] tempV1, tempV2, tempV3, tempV4;
    static double tempC;

    public static void main(String[] args) {
        try {
            // === RMI registry ===
            System.out.println("Connecting to server...");
            Registry registry = LocateRegistry.getRegistry(SERVER_IP, SERVER_PORT);
            AlgebraUtils algebraUtils = (AlgebraUtils) registry.lookup(STUB_NAME);
            System.out.println("Connected to server successfully. IP: " + SERVER_IP + ":" + SERVER_PORT + ", Stub: " + STUB_NAME + "\n");

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
            A = new double[n][n];
            A1 = new double[n][n];
            A2 = new double[n][n];
            B2 = new double[n][n];
            C2 = new double[n][n];
            Y3 = new double[n][n];
            b = new double[n];
            b1 = new double[n];
            c1 = new double[n];
            y1 = new double[n];
            y2 = new double[n];
            x = new double[n];

            ThreadPool threadPool = new ThreadPool(10);

            // calc b & C2;
            System.out.println("");
            algebraUtils.calcVectorb(b);
            algebraUtils.calcMatrixC2(C2);

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
                        // fill randomly
                        threadPool.start(0, () -> fillVectorRandomly("b1", b1, 1.0, 10.0));
                        threadPool.start(1, () -> fillVectorRandomly("c1", c1, 1.0, 10.0));
                        threadPool.start(2, () -> fillMatrixRandomly("A", A, 1.0, 10.0));
                        threadPool.start(3, () -> fillMatrixRandomly("A1", A1, 1.0, 10.0));
                        threadPool.start(4, () -> fillMatrixRandomly("A2", A2, 1.0, 10.0));
                        threadPool.start(5, () -> fillMatrixRandomly("B2", B2, 1.0, 10.0));
                        threadPool.cycleJoin(6);
                        break;
                    }
                    else if (option == 2) {
                        System.out.println("");
                        // enter your own values
                        inputVector(scanner, "b1", b1);
                        inputVector(scanner, "c1", c1);
                        inputMatrix(scanner, "A", A);
                        inputMatrix(scanner, "A1", A1);
                        inputMatrix(scanner, "A2", A2);
                        inputMatrix(scanner, "B2", B2);
                        break;
                    }
                } else {
                    scanner.next(); // skip the incorrect input
                }
                System.out.println("Incorrect the option number! It must be 1 or 2");
            } 
            scanner.close();
            System.out.println("=== ===== ===\n");

            // === DATA ===
            if (SHOW_DATA) {
                System.out.println("=== DATA ===");
                printMatrix("A", A);
                printMatrix("A1", A1);
                printMatrix("A2", A2);
                printMatrix("B2", B2);
                printMatrix("C2", C2);
                printVector("b", b);
                printVector("b1", b1);
                printVector("c1", c1);
                System.out.println("=== ==== ===\n");
            }


            // === CALCULATION ===
            if (SHOW_CALCULATION) {
                System.out.println("=== CALCULATION ===");
            } else {
                System.out.println("=== CALCULATION (hidden) ===");
            }

            //// Level 1
            System.out.println("//// Level 1");
            // y1 = A*b
            y1 = algebraUtils.multiply(A, b);

            // b1+20*c1  -> v1 (avaliable after Level 2)
            tempV1 = algebraUtils.add(b1, algebraUtils.multiply(20, c1));

            // A2*B2  -> M1 (avaliable after Level 2)
            tempM1 = algebraUtils.multiply(A2, B2);

            if (SHOW_CALCULATION) {
                printVector("y1 = A*b", y1);
                printVector("b1+20*c1", tempV1);
                printMatrix("A2*B2", tempM1);
            }

            //// Level 2
            System.out.println("//// Level 2");
            // y2 = A1*(b1+20*c1)
            y2 = algebraUtils.multiply(A1, tempV1);

            // Y3 = A2*B2-C2
            Y3 = algebraUtils.subtraction(tempM1, C2);

            if (SHOW_CALCULATION) {
                printVector("y2 = A1*(b1+20*c1)", y2);
                printMatrix("Y3 = A2*B2-C2", Y3);
            }

            //// Level 3
            System.out.println("//// Level 3");
            // y2'*y2  -> c
            tempC = algebraUtils.multiply(y2, y2);
            
            // Y3*y1  -> v1 (avaliable after Level 5)
            tempV1 = algebraUtils.multiply(Y3, y1);

            // Y3^2  -> M1 (avaliable after Level 7)
            tempM1 = algebraUtils.multiply(Y3, Y3);

            if (SHOW_CALCULATION) {
                System.out.println("Constant y2'*y2:");
                System.out.println(tempC);
                System.out.println("");
                printVector("Y3*y1", tempV1);
                printMatrix("Y3^2", tempM1);
            }

            //// Level 4
            System.out.println("//// Level 4");
            // y2'*y2*Y3  -> M2 (avaliable after Level 5)
            tempM2 = algebraUtils.multiply(tempC, Y3);
            
            // Y3^2*y2  -> v2 (avaliable after Level 5)
            tempV2 = algebraUtils.multiply(tempM1, y2);

            if (SHOW_CALCULATION) {
                printMatrix("y2'*y2*Y3", tempM2);
                printVector("Y3^2*y2", tempV2);
            }

            //// Level 5
            System.out.println("//// Level 5");
            // y2'*y2*Y3*y1  -> v3 (avaliable after Level 6)
            tempV3 = algebraUtils.multiply(tempM2, y1);

            // Y3^2*y2+Y3*y1  -> v4 (avaliable after Level 6)
            tempV4 = algebraUtils.add(tempV2, tempV1);

            if (SHOW_CALCULATION) {
                printVector("y2'*y2*Y3*y1", tempV3);
                printVector("Y3^2*y2+Y3*y1", tempV4);
            }

            //// Level 6
            System.out.println("//// Level 6");
            // Y3^2*y2+Y3*y1+y2'*y2*Y3*y1  -> v1 (avaliable after Level 7)
            tempV1 = algebraUtils.add(tempV4, tempV3);

            if (SHOW_CALCULATION) {
                printVector("Y3^2*y2+Y3*y1+y2'*y2*Y3*y1", tempV1);
            }

            //// Level 7
            System.out.println("//// Level 7");
            // x = (Y3^2*y2+Y3*y1+y2'*y2*Y3*y1)'*Y3^2
            x = algebraUtils.multiply(tempV1, tempM1);

            if (SHOW_CALCULATION) {
                printVector("x = (Y3^2*y2+Y3*y1+y2'*y2*Y3*y1)'*Y3^2", x);
            }

            if (!SHOW_CALCULATION) {
                System.out.println("Calculations performed successfully.");
            }

            System.out.println("=== =========== ===");


            // --- RESULT ---
            System.out.println("\n--- RESULT ---");
            printVector("x", x);
        } catch (Exception e) {
            System.out.println("Client side error:\n" + e);
        }
    }

    // Matrix methods
    public static void fillMatrixRandomly(String name, double[][] data, double minRand, double maxRand) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                data[i][j] = ThreadLocalRandom.current().nextDouble(minRand, maxRand);
            }
        }
        System.out.println(name + " is filled randomly");
    }

    public static void inputMatrix(Scanner scanner, String name, double[][] data) {
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

    public static void printMatrix(String name, double[][] data) {
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

    // Vector methods
    public static void fillVectorRandomly(String name, double[] data, double minRand, double maxRand) {
        for (int i = 0; i < n; i++) {
            data[i] = ThreadLocalRandom.current().nextDouble(minRand, maxRand);
        }
        System.out.println(name + " is filled randomly");
    }

    public static void inputVector(Scanner scanner, String name, double[] data) {
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

    public static void printVector(String name, double[] data) {
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
}
