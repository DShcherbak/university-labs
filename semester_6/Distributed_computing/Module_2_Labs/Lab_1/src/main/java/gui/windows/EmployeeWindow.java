package gui.windows;

import connection.client.ClientProgram;
import connection.client.RmiClient;
import gui.GUI;
import gui.Window;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

public class EmployeeWindow extends Window {
    protected Map<String, JTextField> fieldMap = new HashMap<>();
    public EmployeeWindow(JFrame frame, String title, GUI gui) {
        super(frame, title, gui);
        this.listener = new EmployeeWindowListener();
    }

    private class EmployeeWindowListener implements ActionListener {
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

    public void addField(JTextField field, String name, int x, int y, int w, int h){
        field.setBounds(x,y, w,h);
        field.setSize(w,h);
        frame.add(field);
        fieldMap.put(name, field);
        field.addActionListener(listener);
    }

    public void addComboBox(JComboBox<String> list, int x, int y, int w, int h){
        list.setBounds(x,y, w,h);
        list.setSize(w,h);
        frame.add(list);
    }
}
