import javax.swing.*;
import java.awt.*;
import java.util.concurrent.atomic.AtomicInteger;

public class Main {

    static JLabel leftLabel;
    static JLabel rightLabel;

    static Thread incThread;
    static Thread decThread;

    static CancellationToken incToken;
    static CancellationToken decToken;

    static AtomicInteger pseudoSemaphore = new AtomicInteger(0);

    public static void main(String[] args) {
        JFrame frame = new JFrame();//creating instance of JFrame

        JSlider slider = createSlider(frame);
        JButton[] buttons = createButtons(frame, slider);
        initialiseFrame(frame);
    }

    private static JButton[] createButtons(JFrame frame, JSlider slider){
        JButton[] buttons = new JButton[4];
        buttons[0] = new JButton("ПУСК 1");
        buttons[1] = new JButton("СТОП 1");
        buttons[2] = new JButton("ПУСК 2");
        buttons[3] = new JButton("СТОП 2");

        buttons[0].setBounds(100,200,100, 40);
        buttons[1].setBounds(100,250,100, 40);
        buttons[2].setBounds(400,200,100, 40);
        buttons[3].setBounds(400,250,100, 40);

        buttons[0].addActionListener(ae -> { // possible new thread
            leftLabel.setText("Зайнято...");
            buttons[2].setEnabled(false);
            buttons[3].setEnabled(false);
            incThread = initialiseThreads(slider, true);
            incThread.start();
        });

        buttons[1].addActionListener(ae -> {
            leftLabel.setText("Вільна каса!");
            buttons[2].setEnabled(true);
            buttons[3].setEnabled(true);
            incToken.cancel();
        });

        buttons[2].addActionListener(ae -> {
            leftLabel.setText("Зайнято...");
            buttons[0].setEnabled(false);
            buttons[1].setEnabled(false);
            decThread = initialiseThreads(slider, false);
            decThread.start();
        });

        buttons[3].addActionListener(ae -> {
            leftLabel.setText("Вільна каса!");
            buttons[0].setEnabled(true);
            buttons[1].setEnabled(true);
            decToken.cancel();
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
        leftLabel = new JLabel("Вільна каса!");

        leftLabel.setBounds(240, 50, 120, 50);
        leftLabel.setBackground(Color.GREEN);

        leftLabel.setVerticalAlignment(JLabel.CENTER);
        leftLabel.setHorizontalAlignment(JLabel.CENTER);

        frame.add(leftLabel);
    }

    private static void initialiseFrame(JFrame frame){
        createLabels(frame);
        frame.setSize(600,600);
        frame.setLayout(null);//using no layout managers
        frame.setVisible(true);//making the frame visible
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private static Thread initialiseThreads(JSlider slider, boolean increment) {
        CancellationToken ct = new CancellationToken();
        incThread = new Thread(new CounterThread(slider, increment, ct));
        incThread.setPriority(1);
        incThread.setDaemon(true);
        if(increment)
            incToken = ct;
        else
            decToken = ct;
        return incThread;
    }
}