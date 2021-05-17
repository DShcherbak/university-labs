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

public class DepartmentWindow extends Window {
    protected Map<String, JTextField> fieldMap = new HashMap<>();
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
            } else if (command.equals("UPDATE")){
                String name = fieldMap.get("NAME").getText();
                String power = fieldMap.get("POWER").getText();
                if(correctName(name) && correctNumber(power)){
                    labelMap.get("HEAD").setText("");
                    var currentDepartment = ClientProgram.getCurrentDepartment();
                    if(currentDepartment.getName() != name ||
                        currentDepartment.getPower() != Long.parseLong(power)){
                        try{
                            String result = gui.Client().updateDepartment(currentDepartment.getId(),
                                    currentDepartment.getId(),
                                    name,
                                    Long.parseLong(power));
                            labelMap.get("HEAD").setText(result);
                        }catch (Exception ex){
                            System.out.println("Couldn't update department: " + ex.getMessage());
                        }
                    }
                } else {
                    labelMap.get("HEAD").setText("INCORRECT DATA!");
                }
            } else if (command.equals("DELETE")){
                try{
                    var id = ClientProgram.getCurrentDepartment().getId();
                    String result = gui.Client().deleteDepartment(id);
                    labelMap.get("HEAD").setText(result);
                }catch (Exception ex){
                    System.out.println("Couldn't delete department: " + ex.getMessage());
                }
            } else if (command.equals("ADD")){
                String name = fieldMap.get("NAME").getText();
                String power = fieldMap.get("POWER").getText();
                if(correctName(name) && correctNumber(power)){
                    try{
                        String result = gui.Client().addDepartment(name,Long.parseLong(power));
                        labelMap.get("HEAD").setText(result);
                    }catch (Exception ex){
                        System.out.println("Couldn't add department: " + ex.getMessage());
                    }
                } else {
                    labelMap.get("HEAD").setText("INCORRECT DATA!");
                }
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

    public void addList(JList<String> list, int x, int y, int w, int h){
        list.setBounds(x,y, w,h);
        list.setSize(w,h);
        frame.add(list);
    }
}
