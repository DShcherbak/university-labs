package gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class WindowFactory {
    public static Window GetWindow(GUI gui, GUI.GuiState state){
        return switch (state) {
            case StartScreen -> createStartWindow(gui);
            case Loading -> createLoadingWindow(gui);
            case Preparation -> createConstructorWindow(gui);
            case Game -> createGameWindow(gui);
            default -> new Window(new JFrame(), "Alter", gui);
        };
    }
    private static JFrame defaultJFrame(String title){
        JFrame f = new JFrame(title);
        GridBagLayout layout = new GridBagLayout();
        f.setLayout(null);
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension dimension = toolkit.getScreenSize();
        f.setBounds(dimension.width/2 - Window.width/2, dimension.height/2 - Window.height/2, Window.width,Window.height);
        f.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent windowEvent){
                System.exit(0);
            }
        });
        return f;
    }

    private static JFrame GameFrame(String title){
        JFrame f = defaultJFrame(title);
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension dimension = toolkit.getScreenSize();
        f.setBounds(dimension.width/2 - Window.width/2, dimension.height/2 - Window.height/2, Window.width * 3 / 2,Window.height);
        return f;
    }

    private static Window createStartWindow(GUI gui){
        JFrame startGameFrame = defaultJFrame("Java SWING Examples");
        var window = new Window(startGameFrame,  "Start Screen", gui);

        JButton startButton = new JButton("START");
        startButton.setActionCommand("START");
        window.addButton(startButton,"START", 250,225,300, 50);

        return window;
    }

    private static Window createLoadingWindow(GUI gui){
        JFrame loadingFrame = defaultJFrame("Loading");
        var window = new Window(loadingFrame,  "Loading...", gui);

        JLabel label = new JLabel("Waiting for other player to join...",JLabel.CENTER );
        window.addLabel(label,"LOADING", 350,175,100, 50);

        return window;
    }

    private static Window createConstructorWindow(GUI gui){
        JFrame loadingFrame = defaultJFrame("Game preparations");
        var window = new ConstructionWindow(loadingFrame,  "Place your ships", gui);

        JLabel label = new JLabel("Place your ships!",JLabel.CENTER );
        window.addLabel(label,"PLACE", 325,0,150, 50);

        JButton startButton = new JButton("READY");
        startButton.setActionCommand("READY");
        window.addButton(startButton,"READY", 685,500,100, 50);

        JButton randomButton = new JButton("RANDOM");
        randomButton.setActionCommand("RANDOM");
        window.addButton(randomButton,"RANDOM", 685,430,100, 50);

        JButton rotateButton = new JButton("ROTATE");
        rotateButton.setActionCommand("ROTATE");
        window.addButton(rotateButton,"ROTATE", 685,360,100, 50);

        window.addField(100,100);
        window.ships = GuiShip.getStartingShips();

        for (int i = 0; i < 10; i++) {
            System.out.println(window.ships[i].size);
            for(int t = 0; t < window.ships[i].size; t++){
                int shipBlock = 20;
                JButton shipButton = new JButton();
                shipButton.setActionCommand("ship" + i);
                window.addButton(shipButton, "ship" + i + "" + t, window.ships[i].x + t * shipBlock, window.ships[i].y, shipBlock, shipBlock);
            }
        }

        return window;
    }

    private static Window createGameWindow(GUI gui){
        JFrame loadingFrame = GameFrame("Battle sea");
        var window = new GameWindow(loadingFrame, "Battle sea", gui);

        JLabel label = new JLabel("Wait for your turn",JLabel.CENTER );
        window.addLabel(label,"HEAD", 325,0,150, 50);

        JButton exitButton = new JButton("EXIT");
        exitButton.setActionCommand("EXIT");
        window.addButton(exitButton,"EXIT", 685,500,100, 50);

        window.addMyField(100,100);
        window.addField(700,100);

        return window;
    }
}
