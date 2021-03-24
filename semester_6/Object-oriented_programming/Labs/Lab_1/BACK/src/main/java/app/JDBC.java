package app;

import app.models.RouteModel;
import app.models.StopModel;

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

    public ArrayList<StopModel> getStopsModel(){
        ArrayList<StopModel> stops = new ArrayList<>();
        try{
            CachedRowSet rs = getQuery("select * from stops");
            try{
                while (rs.next()) {
                    StopModel stop = new StopModel(rs.getInt(2), rs.getString(3));
                    stops.add(stop);
                }
            } catch (SQLException e ) {
                throw new Error("Couldn't parse route: ", e);
            }
        }catch (Exception ex){
            System.out.println("Couldn't access routes table.");
        }
        return stops;
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

    public void updateQuery(String query) throws SQLException {
        Connection conn = null;
        RowSetFactory factory = RowSetProvider.newFactory();
        CachedRowSet rowset = factory.createCachedRowSet();
        try {
            Statement stmt = setConnection(conn);
            try {
                stmt.executeUpdate(query);
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
    }

    public void updateRoute(int id, RouteModel route) throws SQLException {
        String query = "update routes set # where route_number = " + id;
        String updates = "stops = Array [";
        for (var stop: route.stops) {
            int t = (int)Math.round((Double) stop);
            updates += t + ", ";
        }
        updates = updates.substring(0, updates.length() - 2);
        updates += "], starttime='" + route.startTime + "', ";
        updates += "endtime='" + route.endTime + "', ";
        updates += "interval=" + route.interval + ", ";
        updates += "routetype=" + route.type + ", ";
        updates += "timetable= Array[";
        for (var tt: route.timetable) {
            int t = (int)Math.round((Double) tt);
            updates += t + ", ";
        }
        updates = updates.substring(0, updates.length() - 2);
        updates += "]";
        query = query.replaceFirst("#", updates);
        System.out.println(query);
        updateQuery(query);

    }
}
