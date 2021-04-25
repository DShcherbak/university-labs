package client;

import common.ServerInterface;
import common.MessageObject;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class RmiClient {
    public static void main(String[] args) throws RemoteException, NotBoundException{
        Registry registry = LocateRegistry.getRegistry("127.0.0.1");
        ServerInterface serverInterface = (ServerInterface) registry.lookup("GameInstance");

        Scanner sc= new Scanner(System.in); //System.in is a standard input stream.
        System.out.print("Enter your name: ");
        String name = sc.nextLine(); //reads string.

        MessageObject mo = serverInterface.registerForGame(new MessageObject(name));
        Integer gameUid = mo.getClientId();
        System.out.println("GAME ID: " + gameUid);
        boolean gameOver = false;
        MessageObject response;
        if(gameUid % 10 == 2){
            response = serverInterface.performMove(new MessageObject(name, gameUid, "", "-"));
            if(response.getMyMessage().equals("WIN")){
                gameOver = true;
                System.out.println("You won!");
            } else {
                System.out.println("Opponent's move: " + response.getMyMessage());
            }
        } else {
            System.out.println("You go first!");
        }
        while(!gameOver){
            System.out.print("Enter your next move: ");
            String move = sc.nextLine();
            serverInterface.performMove(new MessageObject(name, gameUid, "", move));
            response = serverInterface.performMove(new MessageObject(name, gameUid, "", "-"));
            if(response.getMyMessage().equals("WIN")){
                gameOver = true;
                System.out.println("You won!");
            } else {
                System.out.println("Opponent's move: " + response.getMyMessage());
            }
        }
    }
}