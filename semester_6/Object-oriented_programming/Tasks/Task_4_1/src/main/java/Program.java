import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.CyclicBarrier;

public class Program {
    public static Random random = new Random();
    public static CyclicBarrier cb;

    public static class ListWorker implements Runnable{
        private SkipList list;
        private List<Integer> workedWith = new ArrayList<Integer>();

        public ListWorker(){}
        public ListWorker(SkipList list){
            this.list = list;
        }

        @Override
        public void run() {
            for(int i=0 ;i<10;++i) {
                int v = random.nextInt(20);
                list.add(v);
                workedWith.add(v);
            }

            try {
                cb.await();
            } catch (Exception ex) {
                System.out.println(ex.getMessage());
            }

            for(int i=0;i<5;++i) {
                list.remove(workedWith.get(random.nextInt(5)));
            }

        }
    }

    public static class PrintList implements Runnable{
        private SkipList list;

        public PrintList(SkipList list) {
            super();
            this.list = list;
        }

        @Override
        public void run() {
            System.out.println("Size " + list.size.get());
            System.out.println(list);
        }
    }


    public static void main(String[] args) throws InterruptedException {
        SkipList list = new SkipList(5);
        Thread[] th = new Thread[3];

        cb = new CyclicBarrier(3, new PrintList(list));

        for(int i=0;i<3;++i) {
            th[i] = new Thread(new ListWorker(list));
            th[i].start();
        }
        for(int i=0;i<3;++i) {
            th[i].join();
        }
        System.out.println("Size "+list.size.get());
        System.out.println(list);
    }
}
