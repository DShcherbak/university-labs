import javax.swing.*;

public class Counterthread implements Runnable {
    final JSlider slider;
    boolean isIncrement;
    int cntIterations;
    int step = 5;

    public Counterthread(JSlider slider, boolean increment, int cntIterations) {
        this.slider = slider;
        this.isIncrement = increment;
        this.cntIterations = cntIterations;
    }

    public void resetPriority(int newPriority){
    }

    public void run() {
        for (int i = 0; i < cntIterations; i++) {
            if (isIncrement){
                synchronized (slider){
                    int value = slider.getValue();
                    if(value < 90)
                        slider.setValue(value + step);
                }
            }
            else {
                synchronized (slider){
                    int value = slider.getValue();
                    if(value > 10)
                        slider.setValue(value - step);
                }
            }
            System.out.println("Slider value is " + slider.getValue());
            try {
                int priority = Thread.currentThread().getPriority();
                Thread.sleep(10-priority);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}