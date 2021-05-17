package gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

public class Window {
    public final static int width = 800;
    public final static int height = 600;
    public final static int a = 40;
    public JFrame frame;
    public String title;
    protected ActionListener listener;
    protected Map<String, JButton> buttonMap = new HashMap<>();
    protected Map<String, JLabel> labelMap = new HashMap<>();
    public GUI gui;

    public Window(JFrame frame, String title, GUI gui) {
        this.frame = frame;
        this.title = title;
        this.gui = gui;
    }

    public void addButton(JButton button, String name, int x, int y, int w, int h){
        button.setBounds(x,y, w,h);
        button.setSize(w,h);
        frame.add(button);
        buttonMap.put(name, button);
        button.addActionListener(listener);
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

    public boolean correctName(String name){
        for(int i = 0; i < name.length(); i++){
            if((Character.toLowerCase(name.charAt(i)) >= 'a' && Character.toLowerCase(name.charAt(i)) <= 'z')
                || name.charAt(i) == ' ' || name.charAt(i) == '-'){
                continue;
            }
            return false;
        }
        return true;
    }

    public boolean correctNumber(String name){
        for(int i = 0; i < name.length(); i++){
            if(name.charAt(i) <= '9' && name.charAt(i) >= '0'){
                continue;
            }
            return false;
        }
        return true;
    }
}
