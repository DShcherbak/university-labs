import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.Semaphore;

public class Main {

    public static void main(String[] args) throws InterruptedException {
        System.out.println("\n\n");
        int n = 3;
        Honeypot honeypot = new Honeypot();
        Semaphore semaphore = new Semaphore(1, true);
        semaphore.acquire();
        ArrayList<Thread> hiveThreads = new ArrayList<>();
        for(int i = 0; i < n; i++){
            hiveThreads.add(new Thread(new Bee(semaphore, honeypot)));
        }
        for(var th : hiveThreads){
            th.setDaemon(true);
            th.start();
        }
        Thread bearThread = new Thread(new Bear(semaphore, honeypot));
        bearThread.setDaemon(true);
        bearThread.start();
        bearThread.join();
    }
}
