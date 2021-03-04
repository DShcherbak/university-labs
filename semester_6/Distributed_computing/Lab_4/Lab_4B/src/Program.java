public class Program {

    static int N = 5;
    static Garden garden = new Garden(N);

    public static void main(String[] args) throws InterruptedException {
        Thread gardener = new Thread(new Gardener(garden));
        gardener.start();
        Thread nature = new Thread(new Nature(garden));
        nature.start();
        Thread monitor_1 = new Thread(new Monitor(garden, true));
        monitor_1.start();
        Thread monitor_2 = new Thread(new Monitor(garden, false));
        monitor_2.start();
        gardener.join();

    }
}
