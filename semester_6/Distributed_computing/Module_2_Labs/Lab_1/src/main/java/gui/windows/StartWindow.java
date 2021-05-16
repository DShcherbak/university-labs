package gui.windows;

import connection.client.ClientProgram;
import gui.GUI;
import gui.Window;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class StartWindow extends Window {

    public StartWindow(JFrame frame, String title, GUI gui) {
        super(frame, title, gui);
        this.listener = new StartWindowListener();
    }

    private class StartWindowListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String command = e.getActionCommand();
            System.out.println(command);
            if(command.equals("XML")){
                ClientProgram.setDaoType(ClientProgram.DaoType.XML);
            } else if (command.equals("JDBC")){
                ClientProgram.setDaoType(ClientProgram.DaoType.JDBC);
            }
            gui.setCurrentState(GUI.GuiState.ClientScreen);
            gui.showEventDemo();
        }
    }
}
