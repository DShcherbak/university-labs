package objects.JDBC;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class ConnectionPool {
    private static final ConnectionPool cp = new ConnectionPool();

    private final String url = "jdbc:postgresql:hr?user=postgres&password=pass";
    //private final String url = "jdbc:sqlserver://localhost;user=postgres;password=pass";

    private final BlockingQueue<Connection> connections;

    private ConnectionPool() {
        try {
            Class.forName("org.postgresql.Driver");
        } catch (ClassNotFoundException e) {
            System.out.println("JDBC Driver not found");
            e.printStackTrace();
        }

        int MAX_CONNECTIONS = 4;
        connections = new LinkedBlockingQueue<>(MAX_CONNECTIONS);

        try {
            for(int i = 0; i < MAX_CONNECTIONS; ++i) {
                connections.put(DriverManager.getConnection(url));
            }
        } catch (SQLException | InterruptedException e) {
            e.printStackTrace();
        }

    }

    public static ConnectionPool getConnectionPool() {
        return cp;
    }

    public Connection getConnection() throws InterruptedException, SQLException {
        Connection c = connections.take();
        if (c.isClosed()) {
            c = DriverManager.getConnection(url);
        }
        return c;
    }

    public void releaseConnection(Connection c) throws InterruptedException {
        connections.put(c);
    }
}
