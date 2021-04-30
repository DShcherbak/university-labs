package main;

import jdbc.JDBC;

import javax.sql.rowset.CachedRowSet;
import java.sql.SQLException;

public class DAOtask7 {
    public static void main(String[] args){
                try{
                    CachedRowSet rs = JDBC.getQuery("select * from Product");
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
            System.out.println(res);
    }
}
