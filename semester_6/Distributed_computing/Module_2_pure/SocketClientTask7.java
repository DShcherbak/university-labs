package socket;

import entity.*;

import java.io.*;
import java.net.*;
import java.time.LocalDateTime;
import java.util.*;

// Client class
public class SocketClientTask7 {

    static Scanner input;
    private static int inputInt(String s) {
        System.out.print(s);
        return input.nextInt();
    }

    // driver code
    public static void main(String[] args)
    {
        ObjectOutputStream out = null;
        ObjectInputStream in = null;
        input = new Scanner(System.in);

        try (Socket socket = new Socket("localhost", 1234)) {
            System.out.println("Connected to the server");
            out = new ObjectOutputStream(socket.getOutputStream());
            in = new ObjectInputStream(socket.getInputStream());


            boolean clientRunning = true;
            String code = "11";
            while (clientRunning) {
                if(!code.equals(""))
                    System.out.print("SELECT OPERATION CODE: ");
                code = input.nextLine();
                int groupId, parameterId;
                if(code.equals("") || code.equals("\n"))
                    continue;
                int operationCode = code.charAt(0) - '0';
                int entityCode = code.charAt(1) - '0';
                List result = null;
                if(operationCode == 0) {
                    if(entityCode == 0) {
                        clientRunning = false;
                        continue;
                    }
                    out.writeObject("/task/" + entityCode);
                    switch (entityCode) {
                        case 1,2,3,4 -> {
                            if(entityCode == 2){
                                parameterId = inputInt("Enter parameter id:");
                                out.writeInt(parameterId);
                            } else {
                                groupId = inputInt("Enter group id:");
                                out.writeInt(groupId);                            }
                            out.flush();
                            result = (List) in.readObject();
                        }
                        case 5 -> {
                            int n = inputInt("Enter number of parameters:");
                            System.out.println("Enter " + n + " parameter ids");
                            ArrayList<Integer> params = new ArrayList<>(n);
                            for (int i = 0; i < n; i++) {
                                params.set(i, inputInt(""));
                            }
                            out.writeObject(params);
                        }
                        case 6 -> {
                            parameterId = inputInt("Enter parameter id:");
                            int oldProductId = inputInt("Enter old product group id:");
                            int newProductId = inputInt("Enter new product group id:");
                            ArrayList<Integer> list = new ArrayList<>();
                            list.add(parameterId);
                            list.add(oldProductId);
                            list.add(newProductId);
                            out.writeObject(list);
                        }
                    }
                    if(result != null) {
                        for (var elem : result) {
                            System.out.println(elem.toString());
                        }
                    }
                } else {
                    if(entityCode > 4 || entityCode < 1) {
                        System.out.println("Incorrect operation code, try again");
                        continue;
                    }
                    if(operationCode == 1) {
                        switch (entityCode) {
                            case 1 -> out.writeObject("/selectAll/parameter");
                            case 2 -> out.writeObject("/selectAll/product");
                            case 3 -> out.writeObject("/selectAll/parameterGroup");
                            case 4 -> out.writeObject("/selectAll/productGroup");
                            default -> {
                            }
                        }
                        out.flush();
                        result = (List) in.readObject();
                        if(result != null) {
                            for (var elem : result) {
                                System.out.println(elem.toString());
                            }
                        }
                    } else if(operationCode == 2) {
                        int id = inputInt("Enter id: ");
                        switch (entityCode) {
                            case 1 -> out.writeObject("/select/parameter");
                            case 2 -> out.writeObject("/select/product");
                            case 3 -> out.writeObject("/select/parameterGroup");
                            case 4 -> out.writeObject("/select/productGroup");
                            default -> {
                            }
                        }
                        out.writeInt(id);
                        out.flush();
                        var T = in.readObject();
                        System.out.println(T.toString());
                    } else if(operationCode == 3) {
                        switch (entityCode) {
                            case 1 -> {
                                Parameter p = Parameter.createFromConsole();
                                out.writeObject("/create/parameter");
                                out.writeObject(p);
                            }
                            case 2 -> {
                                Product p = Product.createFromConsole();
                                out.writeObject("/create/product");
                                out.writeObject(p);
                            }
                            case 3 -> {
                                ParameterGroup p = ParameterGroup.createFromConsole();
                                out.writeObject("/create/parameterGroup");
                                out.writeObject(p);
                            }
                            case 4 -> {
                                ProductGroup p = ProductGroup.createFromConsole();
                                out.writeObject("/create/productGroup");
                                out.writeObject(p);
                            }
                            default -> {}
                        };
                        out.flush();
                    } else if(operationCode == 4) {
                        int id = inputInt("Enter id: ");
                        switch (entityCode) {
                            case 1 -> {
                                Parameter p = Parameter.createFromConsole();
                                out.writeObject("/update/parameter");
                                out.writeInt(id);
                                out.writeObject(p);
                            }
                            case 2 -> {
                                Product p = Product.createFromConsole();
                                out.writeObject("/update/product");
                                out.writeInt(id);
                                out.writeObject(p);
                            }
                            case 3 -> {
                                ParameterGroup p = ParameterGroup.createFromConsole();
                                out.writeObject("/update/parameterGroup");
                                out.writeInt(id);
                                out.writeObject(p);
                            }
                            case 4 -> {
                                ProductGroup p = ProductGroup.createFromConsole();
                                out.writeObject("/update/productGroup");
                                out.writeInt(id);
                                out.writeObject(p);
                            }
                            default -> {}
                        };
                    } else if(operationCode == 5) {
                        int id = inputInt("Enter id: ");
                        switch (entityCode) {
                            case 1 -> out.writeObject("/delete/parameter");
                            case 2 -> out.writeObject("/delete/product");
                            case 3 -> out.writeObject("/delete/parameterGroup");
                            case 4 -> out.writeObject("/delete/productGroup");
                            default -> {
                            }
                        }
                        out.writeInt(id);
                        ;
                    } else {
                        System.out.println("Incorrect operation code, try again");
                    }
                }
            }
            out.close();
            in.close();
        }
        catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }

    }
}
