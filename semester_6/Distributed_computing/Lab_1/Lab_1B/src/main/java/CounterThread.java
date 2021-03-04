import javax.swing.*;

public class CounterThread implements Runnable {
    final JSlider slider;
    boolean isIncrement;
    CancellationToken ct;

    int step = 5;

    public CounterThread(JSlider slider, boolean increment, CancellationToken ct) {
        this.slider = slider;
        this.isIncrement = increment;
        this.ct = ct;
    }

    public void run() {
        if(Main.pseudoSemaphore.compareAndSet(0,1)){
            while (ct.IsAlive()) {
                if (isIncrement){
                    int value = slider.getValue();
                    if(value < 90)
                        slider.setValue(value + step);
                }
                else {
                    int value = slider.getValue();
                    if(value > 10)
                        slider.setValue(value - step);
                }
                System.out.println("Slider value is " + slider.getValue());
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            Main.pseudoSemaphore.set(0);
        }
    }
}