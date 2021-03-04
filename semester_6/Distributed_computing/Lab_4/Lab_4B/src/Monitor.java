import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class Monitor implements Runnable{

    Garden garden;
    int N;
    boolean writeToFile;

    public Monitor(Garden garden, boolean toFile){
        this.garden = garden;
        N = garden.N;
        writeToFile = toFile;
    }

    @Override
    public void run() {
        for(int p = 0; p < 40; p++){
            StringBuilder builder = new StringBuilder();
            garden.lock.readLock().lock();
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    builder.append(getLetter(garden.garden[i][j]));
                }
                builder.append("\n");
            }

            print(builder.toString());
            garden.lock.readLock().unlock();
            try {
                Thread.sleep(1000 + new Random().nextInt(10) * 100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }


    }

    private void print(String s){
        if(writeToFile){
            try (BufferedWriter br = new BufferedWriter(new FileWriter("src/GardenHistory.txt", true))) {
                br.write(s + "\n----------------\n");
            } catch (IOException e) {
                e.printStackTrace();
            }

        } else {
            System.out.println(s);
            System.out.println("----------------");
        }
    }

    private char getLetter(int n){
        if(n < 0){
            return '*';
        } else if (n < 20){
            return 'E';
        } else if (n < 40){
            return 'D';
        } else if (n < 60){
            return 'C';
        } else if (n < 80){
            return 'B';
        } else {
            return 'A';
        }
    }

}
