import java.util.Random;

public class Gardener implements Runnable{

    Garden garden;
    int N;

    public Gardener(Garden garden){
        this.garden = garden;
        N = garden.N;
    }

    @Override
    public void run() {
        for(int p = 0; p < 40; p++){
            int i = new Random().nextInt(N);
            int j = new Random().nextInt(N);
            var lock = garden.lock;
            lock.readLock().lock();
            boolean needFix = garden.garden[i][j] <= 20 && garden.garden[i][j] >= 0;
            lock.readLock().unlock();

            if(needFix){
                lock.writeLock().lock();
                garden.garden[i][j] += 80;
                System.out.println("Gardener watering at : (" + i + ", " + j + ")");
                lock.writeLock().unlock();
            }

            try {
                Thread.sleep(1000 + new Random().nextInt(10) * 100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}