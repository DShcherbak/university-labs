package socket;
import dao.DAOtask7;
import entity.Parameter;
import entity.ParameterGroup;
import entity.Product;
import entity.ProductGroup;

import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.List;

// Server class
public class SocketServerTask7 {
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
        DAOtask7 dao;

        // Constructor
        public ClientHandler(Socket socket)
        {
            this.clientSocket = socket;
            this.dao = new DAOtask7();
        }

        public boolean iteration() {
            try {
                String request = (String) in.readObject();
                System.out.println("Request from client: " + request);

                switch (request) {
                    case "/task/1" -> {
                        int id = in.readInt();
                        out.writeObject(dao.task1(id));
                    }
                    case "/task/2" -> {
                        int id = in.readInt();
                        out.writeObject(dao.task2(id));
                    }
                    case "/task/3" -> {
                        int id = in.readInt();
                        out.writeObject(dao.task3(id));
                    }
                    case "/task/4" -> {
                        int id = in.readInt();
                        out.writeObject(dao.task4(id));
                    }
                    case "/task/5" -> {
                        ArrayList<Integer> ids = (ArrayList<Integer>) in.readObject();
                        dao.task5(ids);
                    }
                    case "/task/6" -> {
                        ArrayList<Integer> ids = (ArrayList<Integer>) in.readObject();
                        dao.task6(ids.get(0), ids.get(1), ids.get(2));
                    }

                    case "/selectAll/parameter" -> {
                        out.writeObject(dao.selectParameterList());
                    }
                    case "/selectAll/product" -> {
                        out.writeObject(dao.selectProductList());
                    }
                    case "/selectAll/parameterGroup" -> {
                        out.writeObject(dao.selectParameterGroupList());
                    }
                    case "/selectAll/productGroup" -> {
                        out.writeObject(dao.selectProductGroupList());
                    }

                    case "/select/parameter" -> {
                        int id = in.readInt();
                        out.writeObject(dao.selectParameter(id));
                    }
                    case "/select/product" -> {
                        int id = in.readInt();
                        out.writeObject(dao.selectProduct(id));
                    }
                    case "/select/parameterGroup" -> {
                        int id = in.readInt();
                        out.writeObject(dao.selectParameterGroup(id));
                    }
                    case "/select/productGroup" -> {
                        int id = in.readInt();
                        out.writeObject(dao.selectProductGroup(id));
                    }

                    case "/create/parameter" -> {
                        Parameter parameter = ((Parameter) in.readObject());
                        dao.insertParameter(parameter);
                    }
                    case "/create/product" -> {
                        Product product = ((Product) in.readObject());
                        dao.insertProduct(product);
                    }
                    case "/create/parameterGroup" -> {
                        ParameterGroup group = ((ParameterGroup) in.readObject());
                        dao.insertParameterGroup(group);
                    }
                    case "/create/productGroup" -> {
                        ProductGroup group = ((ProductGroup) in.readObject());
                        dao.insertProductGroup(group);
                    }

                    case "/update/parameter" -> {
                        int id = in.readInt();
                        Parameter parameter = ((Parameter) in.readObject());
                        dao.updateParameter(id, parameter);
                    }
                    case "/update/product" -> {
                        int id = in.readInt();
                        Product product = ((Product) in.readObject());
                        dao.updateProduct(id, product);
                    }
                    case "/update/parameterGroup" -> {
                        int id = in.readInt();
                        ParameterGroup group = ((ParameterGroup) in.readObject());
                        dao.updateParameterGroup(id, group);
                    }
                    case "/update/productGroup" -> {
                        int id = in.readInt();
                        ProductGroup group = ((ProductGroup) in.readObject());
                        dao.updateProductGroup(id, group);
                    }

                    case "/delete/parameter" -> {
                        int id = in.readInt();
                        dao.deleteParameter(id);
                    }
                    case "/delete/product" -> {
                        int id = in.readInt();
                        dao.deleteProduct(id);
                    }
                    case "/delete/parameterGroup" -> {
                        int id = in.readInt();
                        dao.deleteParameterGroup(id);
                    }
                    case "/delete/productGroup" -> {
                        int id = in.readInt();
                        dao.deleteProductGroup(id);
                    }

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
