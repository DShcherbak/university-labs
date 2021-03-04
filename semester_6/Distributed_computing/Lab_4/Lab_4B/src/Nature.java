import java.util.Random;

public class Nature implements Runnable{

    Garden garden;
    int N;

    public Nature(Garden garden){
        this.garden = garden;
        N = garden.N;
    }

    @Override
    public void run() {
        for(int p = 0; p < 40; p++){
            int caser = new Random().nextInt(10);
            if(caser < 3){
                garden.lock.writeLock().lock();
                for(int i = 0; i < N; i++){
                    for(int j = 0; j < N; j++){
                        garden.garden[i][j] -= 5;
                    }
                }
                garden.lock.writeLock().unlock();
                System.out.println("Nature: Autumn is coming");
            } else  if (caser < 5) {
                garden.lock.writeLock().lock();
                for(int i = 0; i < N; i++){
                    for(int j = 0; j < N; j++){
                        if(garden.garden[i][j] > 0)
                            garden.garden[i][j] += 5;
                    }
                }
                garden.lock.writeLock().unlock();
                System.out.println("Nature: It's raining!");
            }else {
                int i = new Random().nextInt(N);
                int j = new Random().nextInt(N);

                garden.lock.writeLock().lock();
                if(caser < 8){
                    garden.garden[i][j] -= 30;
                    System.out.println("Nature: Sun is hot today");
                }
                else {
                    garden.garden[i][j] = Math.max(100, garden.garden[i][j] + 40);
                    System.out.println("Nature: Intense growth!");
                }
                garden.lock.writeLock().unlock();
            }

            try {
                Thread.sleep(1000 + new Random().nextInt(10) * 100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }


}
