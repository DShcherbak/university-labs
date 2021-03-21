package app.servlets;

import app.JDBC;
import app.models.RouteModel;
import com.google.gson.Gson;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;


@WebServlet(name = "RoutesServlet", urlPatterns = "/routes")
public class RoutesServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException, ServletException {
        JDBC jdbc = new JDBC();
        var routes = jdbc.getRoutes();
        var stops = jdbc.getStops();
        updateRoutes(routes, stops);
        PrintWriter out = resp.getWriter();
        resp.setContentType("application/json");
        resp.setCharacterEncoding("UTF-8");
        String employeeJsonString = new Gson().toJson(routes);
        out.print(employeeJsonString);
        out.flush();
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException, ServletException {
        RequestDispatcher requestDispatcher = req.getRequestDispatcher("views/add.jsp");
        PrintWriter writer = resp.getWriter();
        String name = req.getParameter("name");
        String password = req.getParameter("pass");
        req.setAttribute("name", name);
        req.setAttribute("pass", password);
        writer.println("You have posted: " + name + ", " + password);
        requestDispatcher.forward(req, resp);
    }

    private void updateRoutes(ArrayList<RouteModel> routes, HashMap<Integer, String> stops){
        for (RouteModel route: routes) {
            for(int i = 0; i < route.stops.length; i++){
                route.stops[i] = stops.get((Integer) route.stops[i]);
            }
        }
    }
}
