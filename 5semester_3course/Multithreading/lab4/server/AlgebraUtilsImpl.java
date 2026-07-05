import java.rmi.RemoteException;

public class AlgebraUtilsImpl implements AlgebraUtils {
    // adding
    public double[][] add(double[][] matrix1, double[][] matrix2) throws RemoteException {
        int n = matrix1.length;
        if (n != matrix1[0].length || n != matrix2.length || n != matrix2[0].length) {
            throw new IllegalArgumentException("The matrix must be square and of the same size!");
        } 

        double[][] result = new double[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        } 

        System.out.println("The add(matrix1, matrix2) is performed");
        return result;
    }

    public double[] add(double[] vector1, double[] vector2) throws RemoteException {
        int n = vector1.length;
        if (n != vector2.length) {
            throw new IllegalArgumentException("The vector size must be the same!");
        } 

        double[] result = new double[n];
        for (int i = 0; i < n; i++) {
            result[i] = vector1[i] + vector2[i];
        } 
        
        System.out.println("The add(vector1, vector2) is performed");
        return result;
    }

    // subtraction
    public double[][] subtraction(double[][] matrix1, double[][] matrix2) throws RemoteException {
        int n = matrix1.length;
        if (n != matrix1[0].length || n != matrix2.length || n != matrix2[0].length) {
            throw new IllegalArgumentException("The matrix must be square and of the same size!");
        } 

        double[][] result = new double[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = matrix1[i][j] - matrix2[i][j];
            }
        } 

        System.out.println("The subtraction(matrix1, matrix2) is performed");
        return result;
    }

    public double[] subtraction(double[] vector1, double[] vector2) throws RemoteException {
        int n = vector1.length;
        if (n != vector2.length) {
            throw new IllegalArgumentException("The vector size must be the same!");
        } 

        double[] result = new double[n];
        for (int i = 0; i < n; i++) {
            result[i] = vector1[i] - vector2[i];
        } 
        
        System.out.println("The subtraction(vector1, vector2) is performed");
        return result;
    }

    // multiplying
    public double[][] multiply(double[][] matrix1, double[][] matrix2) throws RemoteException {
        int n = matrix1.length;
        if (n != matrix1[0].length || n != matrix2.length || n != matrix2[0].length) {
            throw new IllegalArgumentException("The matrix must be square and of the same size!");
        } 

        double[][] result = new double[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = matrix1[i][0] * matrix2[0][j];
                for (int k = 1; k < n; k++) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }

        System.out.println("The multiply(matrix1, matrix2) is performed");
        return result;
    }

    public double[] multiply(double[][] matrix, double[] vector) throws RemoteException {
        int n = matrix.length;
        if (n != matrix[0].length || n != vector.length) {
            throw new IllegalArgumentException("The matrix must be square and the vector size must match the matrix size!");
        } 

        double[] result = new double[n];
        for (int i = 0; i < n; i++) {
            result[i] = matrix[i][0] * vector[0];
            for (int j = 1; j < n; j++) {
                result[i] += matrix[i][j] * vector[j];
            }
        } 

        System.out.println("The multiply(matrix, vector) is performed");
        return result;
    }

    public double[] multiply(double[] vector, double[][] matrix) throws RemoteException {
        int n = matrix.length;
        if (n != matrix[0].length || n != vector.length) {
            throw new IllegalArgumentException("The matrix must be square and the vector size must match the matrix size!");
        } 

        double[] result = new double[n];
        for (int i = 0; i < n; i++) {
            result[i] = vector[0] * matrix[0][i];
            for (int j = 1; j < n; j++) {
                result[i] += vector[j] * matrix[j][i];
            }
        } 

        System.out.println("The multiply(vector, matrix) is performed");
        return result;
    }

    public double multiply(double[] vector1, double[] vector2)  throws RemoteException {
        int n = vector1.length;
        if (n != vector2.length) {
            throw new IllegalArgumentException("The vector size must be the same!");
        } 

        double result = 0;
        for (int i = 0; i < n; i++) {
            result += vector1[i] * vector2[i];
        } 

        System.out.println("The multiply(vector1, vector2) is performed");
        return result;
    }

    public double[][] multiply(double[][] matrix, double c) throws RemoteException {
        int n = matrix.length;
        double[][] result = new double[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = matrix[i][j] * c;
            }
        }
        System.out.println("The multiply(matrix, scalar) is performed");
        return result;
    }

    public double[][] multiply(double c, double[][] matrix) throws RemoteException {
        return multiply(matrix, c);
    }

    public double[] multiply(double[] vector, double c) throws RemoteException {
        int n = vector.length;
        double[] result = new double[n];
        for (int i = 0; i < n; i++) {
            result[i] = vector[i] * c;
        }
        System.out.println("The multiply(vector, scalar) is performed");
        return result;
    }

    public double[] multiply(double c, double[] vector) throws RemoteException {
        return multiply(vector, c);
    }

    // special
    public double[][] transpose(double[][] matrix) throws RemoteException {
        int n = matrix.length;

        double[][] result = new double[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[j][i] = matrix[i][j];
            }
        }
        System.out.println("The transpose(matrix) is performed");
        return result;
    }

    public void calcVectorb(double[] b) throws RemoteException {
        for (int i = 1, n = b.length; i <= n; i++) {
            b[i-1] = 21.0 / Math.pow(i, 4.0);
        }
        System.out.println("The calcVectorb is performed");
    }

    public void calcMatrixC2(double[][] C2) throws RemoteException {
        double determinator;
        for (int i = 1, n = C2.length; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                determinator = i*i-2.0*j;
                if (determinator != 0) {
                    C2[i-1][j-1] = 21.0/determinator;
                } else {
                    C2[i-1][j-1] = 0;
                }
            }
        }
        System.out.println("The calcMatrixC2 is performed");
    }
}
