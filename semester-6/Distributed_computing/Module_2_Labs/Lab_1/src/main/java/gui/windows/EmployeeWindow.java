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
    protected JComboBox<String> comboBox;
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
            } else if (command.equals("UPDATE")){
                String surname = fieldMap.get("SURNAME").getText();
                String name = fieldMap.get("NAME").getText();
                String position = fieldMap.get("POSITION").getText();
                String departmentName = comboBox.getItemAt(comboBox.getSelectedIndex());
                String salary = fieldMap.get("SALARY").getText();
                if(correctName(name) &&
                        correctName(surname) &&
                        correctNumber(salary) &&
                        correctName(position)){
                    try{
                        ClientProgram.setCurrentDepartment(departmentName);
                        var department = ClientProgram.getCurrentDepartment();
                        var employee = ClientProgram.getCurrentEmployee();
                        String result = gui.Client().updateEmployee(employee.getId(), employee.getId(), name,surname,
                                Long.parseLong(salary),position, department.getId());
                        labelMap.get("HEAD").setText(result);
                    }catch (Exception ex){
                        System.out.println("Couldn't add department: " + ex.getMessage());
                    }
                } else {
                    labelMap.get("HEAD").setText("INCORRECT DATA!");
                }
            } else if (command.equals("DELETE")){
                try{
                    var id = ClientProgram.getCurrentEmployee().getId();
                    String result = gui.Client().deleteEmployee(id);
                    labelMap.get("HEAD").setText(result);
                }catch (Exception ex){
                    System.out.println("Couldn't delete employee: " + ex.getMessage());
                }
            }else if (command.equals("ADD")){
                String name = fieldMap.get("NAME").getText();
                String surname = fieldMap.get("SURNAME").getText();
                String salary = fieldMap.get("SALARY").getText();
                String position = fieldMap.get("POSITION").getText();
                String departmentName = comboBox.getItemAt(comboBox.getSelectedIndex());
                if(correctName(name) &&
                        correctName(surname) &&
                        correctNumber(salary) &&
                        correctName(position)){
                    try{
                        ClientProgram.setCurrentDepartment(departmentName);
                        var department = ClientProgram.getCurrentDepartment();
                        String result = gui.Client().addEmployee(name,surname,
                                                                    Long.parseLong(salary),position, department.getId());
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

    public void addComboBox(JComboBox<String> list, int x, int y, int w, int h){
        list.setBounds(x,y, w,h);
        list.setSize(w,h);
        frame.add(list);
        comboBox = list;
    }
}
