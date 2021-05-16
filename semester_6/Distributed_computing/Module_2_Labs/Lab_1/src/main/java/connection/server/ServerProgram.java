package connection.server;

import connection.common.ServerInterface;

public class ServerProgram {
    static ServerInterface server;
    public static void main(String[] args){
        server = RmiServer.createRmiServer();
    }
}
