package gui;

import game.GameField;

import java.util.HashMap;
import java.util.Map;
import javax.swing.*;

public class GUI {
    public enum GuiState {StartScreen, Loading, Preparation, Game};
    private GuiState currentState;
    private Map<GuiState, Window> windows = new HashMap<>();
    public GameField gameField;

    public GUI(){
        currentState = GuiState.Preparation;
        prepareGUI();
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
        for(var state : GuiState.values()){
            var window = WindowFactory.GetWindow(this, state);
            SwingUtilities.updateComponentTreeUI(window.frame);
            windows.put(state, window);
        }
    }

    public void setGameField(GameField gf){
        gameField = gf;
        windows.get(GuiState.Game).recountField();
    }

    private Window GetCurrentWindow(){
        return windows.get(currentState);
    }

    public void setCurrentState(GuiState state){
        this.currentState = state;
    }

    public void showEventDemo(){
        for(var window : windows.values()){
            window.frame.setVisible(false);
        }
        Window currentWindow = GetCurrentWindow();
        currentWindow.setVisible(true);
    }
}