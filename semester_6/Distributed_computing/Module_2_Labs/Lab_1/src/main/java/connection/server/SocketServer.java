package connection.server;

import objects.DAO.iDAO;
import objects.DOM.XmlParser;
import objects.JDBC.JDBC;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class SocketServer {
    public static void main(String[] args)
    {
        ServerSocket server = null;
        try {
            server = new ServerSocket(1234);
            server.setReuseAddress(true);
            while (true) {
                Socket client = server.accept();
                System.out.println("New client connected" +  client.getInetAddress().getHostAddress());
                ClientHandler clientSock = new ClientHandler(client);
                new Thread(clientSock).start();
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        finally {
            if (server != null) {
                try {
                    server.close();
                }
                catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    // ClientHandler class
    private static class ClientHandler implements Runnable {
        private final Socket clientSocket;
        ObjectOutputStream out = null;
        ObjectInputStream in = null;
        iDAO dao;
        iDAO jdbc;
        iDAO xml;

        // Constructor
        public ClientHandler(Socket socket)
        {
            this.clientSocket = socket;
            jdbc = new JDBC();
            xml = new XmlParser();
            this.dao = jdbc;
        }

        public boolean iteration() {
            try {
                String request = (String) in.readObject();
                System.out.println("Request from client: " + request);

                switch (request) {
                    case "/read" -> out.writeBoolean(dao.read());
                    case "/save" -> out.writeBoolean(dao.save());
                    case "/department/add" -> out.writeObject(dao.addDepartment((String) in.readObject(), in.readLong()));
                    case "/department/get" -> out.writeObject(dao.getDepartment(in.readLong()));
                    case "/department/all" -> out.writeObject(dao.getDepartments());
                    case "/department/update" -> out.writeObject(dao.updateDepartment(in.readLong(), in.readLong(),(String) in.readObject(), in.readLong()));
                    case "/department/delete" -> out.writeObject(dao.deleteDepartment(in.readLong()));
                    case "/department/getByName" -> out.writeObject(dao.getDepartmentByName((String)in.readObject()));
                    case "/employee/add" -> out.writeObject(dao.addEmployee((String) in.readObject(), (String) in.readObject(), in.readLong(), (String) in.readObject(), in.readLong()));
                    case "/employee/get" -> out.writeObject(dao.getEmployee(in.readLong()));
                    case "/employee/all" -> out.writeObject(dao.getEmployees());
                    case "/employee/update" -> {
                        out.writeObject(dao.updateEmployee(in.readLong(), in.readLong(),(String) in.readObject(),(String) in.readObject(), in.readLong(), (String) in.readObject(), in.readLong()));
                    }
                    case "/employee/delete" -> out.writeObject(dao.deleteEmployee(in.readLong()));
                    case "/employee/getByName" -> out.writeObject(dao.getEmployeeByName((String)in.readObject()));
                    case "/humanResources" -> out.writeObject(dao.getHumanResources());
                    case "/jdbc" -> {dao = jdbc;dao.read();}
                    case "/xml" -> {dao = xml;dao.read();}
                    default -> out.writeObject("Unknown command: " + request);
                }
                out.flush();
            }  catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }

            return true;
        }

        public void run()
        {
            try {
                in = new ObjectInputStream(clientSocket.getInputStream());
                out = new ObjectOutputStream(clientSocket.getOutputStream());
                System.out.println("In&out streams are init");
                while (iteration()) {};
            }
            catch (IOException e) {
                e.printStackTrace();
            }
            finally {
                try {
                    if (out != null) {
                        out.close();
                    }
                    if (in != null) {
                        in.close();
                        clientSocket.close();
                    }
                }
                catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}