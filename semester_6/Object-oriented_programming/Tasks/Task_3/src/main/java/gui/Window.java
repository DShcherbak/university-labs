package gui;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

public class Window {
    public final static int width = 800;
    public final static int height = 600;
    public final static int a = 40;
    public JFrame frame;
    String title;
    ActionListener listener;
    Map<String, JButton> buttonMap = new HashMap<>();
    Map<String, JLabel> labelMap = new HashMap<>();
    GuiShip[] ships = new GuiShip[10];
    int currentShip = -1;
    public GUI gui;

    public Window(JFrame frame, String title, GUI gui) {
        this.frame = frame;
        this.title = title;
        this.gui = gui;
        this.listener = new ButtonClickListener();
    }

    public void addButton(JButton button, String name, int x, int y, int w, int h){
        button.setBounds(x,y, w,h);
        button.setSize(w,h);
        frame.add(button);
        buttonMap.put(name, button);
        button.addActionListener(listener);
    }

    public void addField(int dx, int dy){
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++){
                JButton fieldButton = new JButton();
                fieldButton.setActionCommand("field" + i + "" + j);
                addButton(fieldButton,"field" + i + "" + j, dx+a*j,dy+a*i,a,a);
            }
        }
    }

    public void addLabel(JLabel label, String name, int x, int y, int w, int h){
        label.setBounds(x,y,w,h);
        frame.add(label);
        labelMap.put(name, label);
    }

    public void setVisible(boolean visibility){
        frame.setVisible(visibility);
        for (var button : buttonMap.values()) {
            button.setVisible(visibility);
        }
        for (var label : labelMap.values()) {
            label.setVisible(visibility);
        }
    }

    private class ButtonClickListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String command = e.getActionCommand();
            System.out.println(command);
            if( command.equals( "START" ))  {
                gui.setCurrentState(GUI.GuiState.Loading);
                gui.showEventDemo();
                try {
                    Thread.sleep(2000);
                } catch (InterruptedException interruptedException) {
                    interruptedException.printStackTrace();
                }
                gui.setCurrentState(GUI.GuiState.Preparation);
                gui.showEventDemo();
                //           gui.setCurrentState(GUI.GuiState.Preparation);
                //           gui.showEventDemo();
            }

        }
    }
}
