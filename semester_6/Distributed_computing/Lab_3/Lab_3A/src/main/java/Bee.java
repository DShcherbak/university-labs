import java.util.Random;
import java.util.concurrent.Semaphore;

public class Bee implements Runnable {
    static int maxId = 0;
    int id = 0;
    Semaphore semaphore;
    final Honeypot honeypot;

    public Bee(Semaphore semaphore, Honeypot honeypot){
        id = maxId++;
        this.semaphore = semaphore;
        this.honeypot = honeypot;
    }

    public void getHoney() {
        Random rand = new Random(Runtime.getRuntime().hashCode());
        try{
            Thread.sleep(100 + (int) (Math.random() * 900));
        } catch (Exception ignored){}



    }

    @Override
    public void run() {
        int counter = 10000;
        while(counter > 0) {
            counter--;
            try {
                boolean Berrimor = false;
                getHoney();
                synchronized (honeypot) {
                    if(honeypot.isFull())
                        continue;
                    System.out.println("Bee number " + id + " came with some honey!");
                    honeypot.insertHoney();

                    if (honeypot.isFull()) {
                        Berrimor = true;
                    }
                }
                if(Berrimor){
                    System.out.println("Bee " + id + " is Berrimor");
                    System.out.println("SEMAPHORE: NO BEES ALLOWED!");
                    semaphore.release();
                    semaphore.acquire();
                    System.out.println("SEMAPHORE: BEES ALLOWED!");
                }

            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
