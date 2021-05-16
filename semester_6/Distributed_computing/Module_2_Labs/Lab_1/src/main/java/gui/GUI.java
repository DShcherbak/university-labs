package gui;
import connection.client.iClient;

import java.util.HashMap;
import java.util.Map;
import javax.swing.*;

public class GUI {
    public enum GuiState {StartScreen, ClientScreen, DaoScreen, DepartmentScreen, EmployeeScreen};
    private GuiState currentState;
    private Map<GuiState, Window> windows = new HashMap<>();
    private iClient client;
    public iClient Client(){
        return client;
    }

    public GUI(){
        currentState = GuiState.StartScreen;
        prepareGUI();
    }


    public void setupClient(iClient client){
        this.client = client;
    }

    public boolean connectToServer(){
        try{
            client.connect();
        }catch (Exception ex){
            System.out.println("Couldn't connect to connection.server");
            return false;
        }
        return true;
    }

    public static GUI setupGUI(){
        try{
            UIManager.setLookAndFeel("javax.swing.plaf.nimbus.NimbusLookAndFeel");
        }catch (Exception ex){
            System.out.println(ex.getMessage());
        }
        GUI gui = new GUI();
        gui.showEventDemo();
        return gui;
    }

    public static void main(String[] args){
        try{
            UIManager.setLookAndFeel("javax.swing.plaf.nimbus.NimbusLookAndFeel");
        }catch (Exception ex){
            System.out.println(ex.getMessage());
        }
        GUI gui = new GUI();
        gui.showEventDemo();
    }

    private void prepareGUI(){
     //   for(var state : GuiState.values()){
     //       var window = WindowFactory.GetWindow(this, state);
     //       SwingUtilities.updateComponentTreeUI(window.frame);
     //       windows.put(state, window);
     //   }
    }

    private Window GetCurrentWindow(){

        var window = WindowFactory.GetWindow(this, currentState);
        SwingUtilities.updateComponentTreeUI(window.frame);
        windows.put(currentState, window);
        return window;
       // return windows.get(currentState);
    }

    public void setCurrentState(GuiState state){
        this.currentState = state;
    }

    public void showEventDemo(){
        for(var window : windows.values()){
            window.setVisible(false);
        }
        Window currentWindow = GetCurrentWindow();
        currentWindow.setVisible(true);
    }
}