package gui.windows;

import objects.entity.Department;
import gui.GUI;
import gui.Window;
import org.javatuples.Pair;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.rmi.RemoteException;

public class DaoWindow extends Window {
    public JPanel treePanel;
    public DaoWindow(JFrame frame, String title, GUI gui) {
        super(frame, title, gui);
        this.listener = new DaoWindow.XmlWindowListener();
    }

    private class XmlWindowListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String command = e.getActionCommand();
            System.out.println(command);
            if(command.startsWith("GET/")){
                Pair<Department, String> pair = null;
                try {
                    pair = gui.Client().getDepartment(0);
                    if(pair.getValue1().equals("OK")){
                        System.out.println(pair.getValue0().getName());
                    }else{
                        System.out.println(pair.getValue1());
                    }
                } catch (RemoteException remoteException) {
                    remoteException.printStackTrace();
                }
            } else if (command.equals("JDBC")){
                gui.setCurrentState(GUI.GuiState.StartScreen);
                gui.showEventDemo();
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
