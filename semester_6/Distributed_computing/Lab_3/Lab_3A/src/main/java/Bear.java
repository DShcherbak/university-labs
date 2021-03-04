import java.util.concurrent.Semaphore;

public class Bear implements Runnable{

    Semaphore semaphore;
    final Honeypot honeypot;
    public Bear(Semaphore semaphore, Honeypot honeypot){
        this.semaphore = semaphore;
        this.honeypot = honeypot;
    }
    @Override
    public void run() {
        while(true) {
            try {
                semaphore.acquire();
                synchronized (honeypot) {
                    if(honeypot.eatHoney())
                        System.out.println("BEAR: Я ПОЇВ");
                }
                semaphore.release();
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
