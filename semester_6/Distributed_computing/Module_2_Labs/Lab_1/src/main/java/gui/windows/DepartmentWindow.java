package gui.windows;

import connection.client.ClientProgram;
import connection.client.RmiClient;
import gui.GUI;
import gui.Window;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class DepartmentWindow extends Window {
    public DepartmentWindow(JFrame frame, String title, GUI gui) {
        super(frame, title, gui);
        this.listener = new DepartmentWindowListener();
    }

    private class DepartmentWindowListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String command = e.getActionCommand();
            System.out.println(command);
            if(command.equals("BACK")){
                gui.setCurrentState(GUI.GuiState.DaoScreen);
                gui.showEventDemo();
                return;
            }
        }
    }
}
