import java.rmi.Remote;
import java.rmi.RemoteException;


public interface AlgebraUtils extends Remote {
    // adding
    public double[][] add(double[][] matrix1, double[][] matrix2) throws RemoteException;

    public double[] add(double[] vector1, double[] vector2) throws RemoteException;

    // subtraction
    public double[][] subtraction(double[][] matrix1, double[][] matrix2) throws RemoteException;

    public double[] subtraction(double[] vector1, double[] vector2) throws RemoteException;

    // multiplying
    public double[][] multiply(double[][] matrix1, double[][] matrix2) throws RemoteException;

    public double[] multiply(double[][] matrix, double[] vector) throws RemoteException;

    public double[] multiply(double[] vector, double[][] matrix) throws RemoteException;

    public double multiply(double[] vector1, double[] vector2)  throws RemoteException;

    public double[][] multiply(double[][] matrix, double c) throws RemoteException;

    public double[][] multiply(double c, double[][] matrix) throws RemoteException;

    public double[] multiply(double[] vector, double c) throws RemoteException;

    public double[] multiply(double c, double[] vector) throws RemoteException;

    // special
    public double[][] transpose(double[][] matrix) throws RemoteException;

    public void calcVectorb(double[] b) throws RemoteException;

    public void calcMatrixC2(double[][] C2) throws RemoteException;
}
