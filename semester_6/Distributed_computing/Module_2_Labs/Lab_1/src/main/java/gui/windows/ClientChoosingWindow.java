package gui.windows;

import connection.client.ClientProgram;
import connection.client.RmiClient;
import gui.GUI;
import gui.Window;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.rmi.RemoteException;

public class ClientChoosingWindow extends Window {
    public ClientChoosingWindow(JFrame frame, String title, GUI gui) {
        super(frame, title, gui);
        this.listener = new ClientChoosingWindowListener();
    }

    private class ClientChoosingWindowListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String command = e.getActionCommand();
            System.out.println(command);
            if(command.equals("RMI")){
                gui.setCurrentState(GUI.GuiState.DaoScreen);
                ClientProgram.setClient(new RmiClient());
            } else if (command.equals("JDBC")){
                return;
            }
            ClientProgram.setClient(new RmiClient());
            ClientProgram.connectClient();
            gui.showEventDemo();

        }
    }
}


