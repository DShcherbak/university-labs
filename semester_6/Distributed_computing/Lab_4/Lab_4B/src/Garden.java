import java.util.Random;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class Garden {

    int N;
    int[][] garden;
    ReadWriteLock lock;

    public Garden(int n){
        N = n;
        garden = new int[N][N];
        lock = new ReentrantReadWriteLock();
        Random r = new Random();
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                garden[i][j] = r.nextInt(16) * 5 + 25;
            }
        }
    }
}
