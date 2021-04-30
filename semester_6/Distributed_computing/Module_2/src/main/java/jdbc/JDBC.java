package jdbc;

import javax.sql.rowset.CachedRowSet;
import javax.sql.rowset.RowSetFactory;
import javax.sql.rowset.RowSetProvider;
import java.sql.*;

public class JDBC {


    public static void updateQuery(String query) throws SQLException {
        System.out.println("JDBC: " + query);
        Connection conn = null;
        RowSetFactory factory = RowSetProvider.newFactory();
        CachedRowSet rowset = factory.createCachedRowSet();
        try {
            try (Statement stmt = setConnection(conn)) {
                stmt.executeUpdate(query);
            } catch (SQLException e) {
                throw new Error("Problem", e);
            }
        } catch (ClassNotFoundException e) {
            throw new Error("Problem", e);
        } finally {
            try {
                if (conn != null) {
                    conn.close();
                }
            } catch (SQLException ex) {
                System.out.println(ex.getMessage());
            }
        }
    }

    public static CachedRowSet getQuery(String query) throws SQLException {
        Connection conn = null;
        RowSetFactory factory = RowSetProvider.newFactory();
        CachedRowSet rowset = factory.createCachedRowSet();
        try {
            try (Statement stmt = setConnection(conn)) {
                ResultSet rs = stmt.executeQuery(query);
                rowset.populate(rs);
            } catch (SQLException e) {
                throw new Error("Problem", e);
            }
        } catch (ClassNotFoundException e) {
            throw new Error("Problem", e);
        } finally {
            try {
                if (conn != null) {
                    conn.close();
                }
            } catch (SQLException ex) {
                System.out.println(ex.getMessage());
            }
        }
        return rowset;
    }

    private static Statement setConnection(Connection conn) throws ClassNotFoundException, SQLException {
        Class.forName("org.postgresql.Driver");
        String url = "jdbc:postgresql:module2?user=postgres&password=pass";
        conn = DriverManager.getConnection(url);
        return conn.createStatement();
    }
}
