package app.servlets;

import app.JDBC;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;


@WebServlet(name = "RouteServlet", urlPatterns = "/route/*")
public class RouteServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException, ServletException {
        JDBC jdbc = new JDBC();
        String url = String.valueOf(req.getRequestURL());
        String num = url.substring(url.lastIndexOf("/") + 1);
        int id = Integer.parseInt(num);
        var routes = jdbc.getRoute(id);
        var out = GeneralRouteServlet.updateResp(resp);
        out.print(GeneralRouteServlet.updateRoutes(jdbc, routes));
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


}
