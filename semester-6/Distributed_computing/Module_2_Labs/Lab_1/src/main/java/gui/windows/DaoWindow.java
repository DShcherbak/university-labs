package gui.windows;

import gui.GUI;
import gui.Window;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class DaoWindow extends Window {
    public JPanel treePanel;
    public DaoWindow(JFrame frame, String title, GUI gui) {
        super(frame, title, gui);
        this.listener = new DaoWindowListener();
    }

    private class DaoWindowListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String command = e.getActionCommand();
            System.out.println(command);
            if(command.startsWith("ADD DEP")){
                gui.setCurrentState(GUI.GuiState.AddDepartmentScreen);
                gui.showEventDemo();
            } else if (command.equals("ADD EMP")){
                gui.setCurrentState(GUI.GuiState.AddEmployeeScreen);
                gui.showEventDemo();
            } else if (command.equals("SAVE")){
                try{
                    gui.Client().save();
                }catch (Exception ex){
                    System.out.println("Couldn't save: " + ex.getMessage());
                }
            }

        }
    }

    @Override
    public void setVisible(boolean visibility){
        frame.setVisible(visibility);
        for (var button : buttonMap.values()) {
            button.setVisible(visibility);
        }
        for (var label : labelMap.values()) {
            label.setVisible(visibility);
        }
        treePanel.setVisible(visibility);
    }
}
