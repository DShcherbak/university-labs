package rmi;

import entity.*;

import java.rmi.AccessException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;

public class RmiClientTask7 {

    static Scanner input;

    private RmiClientTask7() { }

    private static int inputInt(String s) {
        System.out.print(s);
        return input.nextInt();
    }

    public static void main(String[] args) throws RemoteException {
        input = new Scanner(System.in);
        System.out.println("Operation codes are two-digit integers XY, where X stands for operation type and Y stands for entity type");
        System.out.println("Possible X values:\n 1 - select all\n 2 - select by id\n3 - create\n4 - update\5 - delete ");
        System.out.println("Possible Y values:\n 1 - product\n 2 - parameter\n3 - product group\n4 - parameter group");
        System.out.println("Also codes 01-06 correspond to 6 specific queries apart from CRUD. Code 00 corresponds to exit");
        System.out.println("All other codes aren't valid");

        try {
            Registry registry = LocateRegistry.getRegistry(1235);
            IRmiServer server = (IRmiServer) registry.lookup("productDatabase");

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
                    switch (entityCode) {
                        case 1 -> {
                            groupId = inputInt("Enter group id:");
                            result = server.task1(groupId);
                        }
                        case 2 -> {
                            parameterId = inputInt("Enter parameter id:");
                            result = server.task2(parameterId);
                        }
                        case 3 -> {
                            groupId = inputInt("Enter group id:");
                            result = server.task3(groupId);
                        }
                        case 4 -> {
                            groupId = inputInt("Enter group id:");
                            result = server.task4(groupId);
                            //result.add(new ProductWithParameters(new Product("a", 1, "b", new Timestamp(0)), new HashMap<>()));
                        }
                        case 5 -> {
                            int n = inputInt("Enter number of parameters:");
                            System.out.println("Enter " + n + " parameter ids");
                            ArrayList<Integer> params = new ArrayList<>(n);
                            for (int i = 0; i < n; i++) {
                                params.set(i, inputInt(""));
                            }
                            server.task5(params);
                        }
                        case 6 -> {
                            parameterId = inputInt("Enter parameter id:");
                            int oldProductId = inputInt("Enter old product group id:");
                            int newProductId = inputInt("Enter old product group id:");
                            server.task6(parameterId, oldProductId, newProductId);
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
                        result = switch (entityCode) {
                            case 1 -> server.selectParameterList();
                            case 2 -> server.selectProductList();
                            case 3 -> server.selectParameterGroupList();
                            case 4 -> server.selectProductGroupList();
                            default -> null;
                        };
                        if(result != null) {
                            for (var elem : result) {
                                System.out.println(elem.toString());
                            }
                        }
                    } else if(operationCode == 2) {
                        int id = inputInt("Enter id: ");
                        var T = switch (entityCode) {
                            case 1 -> server.selectParameter(id);
                            case 2 -> server.selectProduct(id);
                            case 3 -> server.selectParameterGroup(id);
                            case 4 -> server.selectProductGroup(id);
                            default -> null;
                        };
                        System.out.println(T.toString());
                    } else if(operationCode == 3) {
                        switch (entityCode) {
                            case 1 -> {
                                Parameter p = Parameter.createFromConsole();
                                server.insertParameter(p);
                            }
                            case 2 -> {
                                Product p = Product.createFromConsole();
                                server.insertProduct(p);
                            }
                            case 3 -> {
                                ParameterGroup p = ParameterGroup.createFromConsole();
                                server.insertParameterGroup(p);
                            }
                            case 4 -> {
                                ProductGroup p = ProductGroup.createFromConsole();
                                server.insertProductGroup(p);
                            }
                            default -> {}
                        };
                    } else if(operationCode == 4) {
                        int id = inputInt("Enter id: ");
                        switch (entityCode) {
                            case 1 -> {
                                Parameter p = Parameter.createFromConsole();
                                server.updateParameter(id, p);
                            }
                            case 2 -> {
                                Product p = Product.createFromConsole();
                                server.updateProduct(id, p);
                            }
                            case 3 -> {
                                ParameterGroup p = ParameterGroup.createFromConsole();
                                server.updateParameterGroup(id, p);
                            }
                            case 4 -> {
                                ProductGroup p = ProductGroup.createFromConsole();
                                server.updateProductGroup(id, p);
                            }
                            default -> {}
                        };
                    } else if(operationCode == 5) {
                        int id = inputInt("Enter id: ");
                        switch (entityCode) {
                            case 1 -> server.deleteParameter(id);
                            case 2 -> server.deleteProduct(id);
                            case 3 -> server.deleteParameterGroup(id);
                            case 4 -> server.deleteProductGroup(id);
                            default -> {
                            }
                        }
                        ;
                    } else {
                        System.out.println("Incorrect operation code, try again");
                    }
                }
            }
        } catch (NotBoundException e) {
            e.printStackTrace();
        }
    }
}

