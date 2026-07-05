import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject; 


public class Server {
    static final String SERVER_IP = "127.0.0.1";
    static final int SERVER_PORT = 9000;
    static final String STUB_NAME = "algebrautils";

    public static void main(String [] args) {
		try {

			System.out.println("Server is booting....");
			System.setProperty("java.rmi.server.hostname", SERVER_IP); 

			// We create objects from class and share them using
            AlgebraUtilsImpl algebraUtilsImpl = new AlgebraUtilsImpl();

            // Export object before registered in Registry. 
            AlgebraUtils stub = (AlgebraUtils) UnicastRemoteObject.exportObject(algebraUtilsImpl, 0);


            // Get the RMI registry.
            Registry registry = LocateRegistry.createRegistry(SERVER_PORT);

            // Registered the exported object in rmi registry so that client can
            // lookup in this registry and call the object methods.
            registry.rebind(STUB_NAME, stub);

            System.out.println("Server started successfully at " + SERVER_IP + ":" + SERVER_PORT + ", Stub: " + STUB_NAME);
            System.out.println("");

		} catch (Exception e) {
			System.out.println("Server side error:\n" + e);
		}

	}
}
