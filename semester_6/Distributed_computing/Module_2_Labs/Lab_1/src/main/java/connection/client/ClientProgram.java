package connection.client;

import gui.GUI;
import objects.entity.Department;
import objects.entity.Employee;
import objects.entity.HumanResources;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.rmi.RemoteException;
import java.util.Scanner;

public class ClientProgram {
    public enum DaoType {XML, JDBC};

    public static GUI gui;
    public static DaoType daoType = DaoType.XML;
    public static iClient client;

    public static Department currentDepartment;
    public static Employee currentEmployee;

    public static HumanResources humanResources;

    public static void main(String[] args) throws Exception{
        gui = GUI.setupGUI();
        boolean rmi = false;
        if(rmi){
            var rmiClient = new RmiClient();
            ClientProgram.setClient(rmiClient);
            ClientProgram.connectClient();
        } else {
            ObjectOutputStream out = null;
            ObjectInputStream in = null;

            try (Socket socket = new Socket("localhost", 1234)) {
                System.out.println("Connected to the server");
                out = new ObjectOutputStream(socket.getOutputStream());
                in = new ObjectInputStream(socket.getInputStream());

                var socketClient = new SocketClient(in, out);
                ClientProgram.setClient(socketClient);
                ClientProgram.connectClient();

                boolean clientRunning = true;
                String code = "11";
                while (clientRunning) {

                }
            }catch (Exception ex){

            }
        }


    }

    public static void connectClient(){
        gui.setupClient(client);
        while(!gui.connectToServer()){
            try{
                Thread.sleep(2000);
            }catch (Exception ignored){ }
        }
        try{
            gui.Client().read();
        }catch (Exception ex){
            System.out.println("Couldn't read from connection.client: " + ex.getMessage());
        }
    }

    public static Department getCurrentDepartment() {
        return currentDepartment;
    }

    public static void setCurrentDepartment(String currentDepartmentName) {
        try{
            ClientProgram.currentDepartment = client.getDepartmentByName(currentDepartmentName);
        }catch (Exception ignored){}
    }

    public static Employee getCurrentEmployee() {
        return currentEmployee;
    }

    public static void setCurrentEmployee(String currentEmployeeName) {
        try{
            ClientProgram.currentEmployee = client.getEmployeeByName(currentEmployeeName);
        }catch (Exception ignored){}
    }

    public static HumanResources getHumanResources() {
        try {
            humanResources = gui.Client().getHumanResources();
        } catch (RemoteException remoteException) {
            remoteException.printStackTrace();
        }
        return humanResources;
    }


    public static void setDaoType(DaoType type){
        daoType = type;
    }

    public static GUI getGui() {
        return gui;
    }

    public static void setGui(GUI gui) {
        ClientProgram.gui = gui;
    }

    public static DaoType getDaoType() {
        return daoType;
    }

    public static iClient getClient() {
        return client;
    }

    public static void setClient(iClient client) {
        ClientProgram.client = client;
    }


}
