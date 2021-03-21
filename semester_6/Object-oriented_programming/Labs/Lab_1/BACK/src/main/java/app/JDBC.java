package app;

import app.models.RouteModel;

import javax.sql.rowset.CachedRowSet;
import javax.sql.rowset.RowSetFactory;
import javax.sql.rowset.RowSetProvider;
import java.sql.*;
import java.util.ArrayList;
import java.util.Dictionary;
import java.util.HashMap;

public class JDBC {

    private Statement setConnection(Connection conn) throws ClassNotFoundException, SQLException {
        Class.forName("org.postgresql.Driver");
        String url = "jdbc:postgresql:dbprod?user=myuser&password=topsecret";
        conn = DriverManager.getConnection(url);
        return conn.createStatement();
    }

    private ArrayList<RouteModel> getRoutesInternal(String query){
        ArrayList<RouteModel> routes = new ArrayList<>();
        try{
            CachedRowSet rs = getQuery(query);
            try{
                while (rs.next()) {
                    RouteModel route = parseRoute(rs);
                    routes.add(route);
                }
            } catch (SQLException e ) {
                throw new Error("Couldn't parse route: ", e);
            }
        }catch (Exception ex){
            System.out.println("Couldn't access routes table.");
        }
        return routes;
    }

    public ArrayList<RouteModel> getRoute(int id) {
        return getRoutesInternal("select * from routes where route_number = " + id);
    }

    public ArrayList<RouteModel> getRoutes() {
        return getRoutesInternal("select * from routes order by route_id");
    }

    private RouteModel parseRoute(ResultSet rs) throws SQLException {
        int routeNumber = rs.getInt(2);
        Object[] stops = (Object[]) rs.getArray(3).getArray();
        String startTime = rs.getString(4);
        String endTime = rs.getString(5);
        int interval = rs.getInt(6);
        int type = rs.getInt(7);
        Object[] timetable = (Object[]) rs.getArray(8).getArray();
        return new RouteModel(routeNumber, stops, startTime, endTime, interval, type, timetable);
    }

    public HashMap<Integer, String> getStops()  {
        HashMap<Integer, String> stops = new HashMap<>();
        try{
            CachedRowSet rs = getQuery("select * from stops");
            try{
                while (rs.next()) {
                    int stop_id = rs.getInt(2);
                    String name = rs.getString(3);
                    stops.put(stop_id, name);
                }
            } catch (SQLException e ) {
                throw new Error("Couldn't parse route: ", e);
            }
        } catch (Exception ex){
            System.out.println("Couldn't access stops table.");
        }
        return stops;
    }

    public CachedRowSet getQuery(String query) throws SQLException {
        Connection conn = null;
        RowSetFactory factory = RowSetProvider.newFactory();
        CachedRowSet rowset = factory.createCachedRowSet();
        try {
            Statement stmt = setConnection(conn);
            try {
                ResultSet rs = stmt.executeQuery(query);
                rowset.populate(rs);
            } catch (SQLException e ) {
                throw new Error("Problem", e);
            } finally {
                if (stmt != null) { stmt.close(); }
            }
        } catch (SQLException | ClassNotFoundException e) {
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
}
