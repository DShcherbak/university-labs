import javax.swing.*;
import java.awt.*;

public class Main {

    static int leftPriority = 1;
    static int rightPriority = 1;
    static JLabel leftLabel;
    static JLabel rightLabel;

    static Thread incThread;
    static Thread decThread;

    public static void main(String[] args) {
        JFrame frame = new JFrame();//creating instance of JFrame

        JButton[] buttons = createButtons(frame);
        JSlider slider = createSlider(frame);
        initialiseFrame(frame);
        initialiseThreads(slider);

        incThread.start();
        decThread.start();
    }

    private static JButton[] createButtons(JFrame frame){
        JButton[] buttons = new JButton[4];
        buttons[0] = new JButton("+");
        buttons[1] = new JButton("-");
        buttons[2] = new JButton("+");
        buttons[3] = new JButton("-");

        buttons[0].setBounds(100,200,100, 40);
        buttons[1].setBounds(100,250,100, 40);
        buttons[2].setBounds(400,200,100, 40);
        buttons[3].setBounds(400,250,100, 40);

        buttons[0].addActionListener(ae -> { // possible new thread
            leftPriority++;
            leftLabel.setText(String.valueOf(leftPriority));
            incThread.setPriority(leftPriority);

        });
        buttons[1].addActionListener(ae -> {
            if (leftPriority > 0) {
                leftPriority--;
                leftLabel.setText(String.valueOf(leftPriority));
                incThread.setPriority(leftPriority);
            }
        });
        buttons[2].addActionListener(ae -> {
            rightPriority++;
            rightLabel.setText(String.valueOf(rightPriority));
            decThread.setPriority(rightPriority);
        });
        buttons[3].addActionListener(ae -> {
            if (rightPriority > 0) {
                rightPriority--;
                rightLabel.setText(String.valueOf(rightPriority));
                decThread.setPriority(rightPriority);
            }
        });

        for (var button : buttons){
            frame.add(button);
        }
        return buttons;
    }

    private static JSlider createSlider(JFrame frame) {
        var slider = new JSlider(JSlider.VERTICAL, 0, 100, 50);
        slider.setBounds(200, 100, 200, 400);
        frame.add(slider);
        return slider;
    }

    private static void createLabels(JFrame frame) {
        leftLabel = new JLabel(String.valueOf(leftPriority));
        rightLabel = new JLabel(String.valueOf(rightPriority));

        leftLabel.setBounds(100, 300, 100, 50);
        rightLabel.setBounds(400, 300, 100, 50);
        leftLabel.setBackground(Color.GREEN);
        rightLabel.setBackground(Color.GREEN);

        leftLabel.setVerticalAlignment(JLabel.CENTER);
        leftLabel.setHorizontalAlignment(JLabel.CENTER);

        rightLabel.setVerticalAlignment(JLabel.CENTER);
        rightLabel.setHorizontalAlignment(JLabel.CENTER);

        frame.add(leftLabel);
        frame.add(rightLabel);
    }

    private static void initialiseFrame(JFrame frame){
        createLabels(frame);
        frame.setSize(600,600);
        frame.setLayout(null);//using no layout managers
        frame.setVisible(true);//making the frame visible
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private static void initialiseThreads(JSlider slider) {
        incThread = new Thread(new Counterthread(slider, true, 10000));
        decThread = new Thread(new Counterthread(slider, false, 10000));
        incThread.setPriority(1);
        decThread.setPriority(1);
        incThread.setDaemon(true);
        decThread.setDaemon(true);
    }
}