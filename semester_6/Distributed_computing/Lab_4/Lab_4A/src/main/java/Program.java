import java.io.*;

public class Program {

    private static final CustomFile[] files = new CustomFile[]{
            new CustomFile("src/main/resources/phoneBook.txt"),
            new CustomFile("src/main/resources/phones.txt"),
            new CustomFile("src/main/resources/names.txt")
    };

    public static void main(String[] args) throws InterruptedException {
        int nameReaders = 3, phoneReaders = 2, writers = 3;
        Thread[] threads = new Thread[nameReaders + phoneReaders + writers];

        int j = 0;
        for(int i = 0; i < nameReaders; i++){
            threads[j] = new Thread(new GetNameThread(files));
            threads[j].start();
            j++;
        }
        for(int i = 0; i < phoneReaders; i++){
            threads[j] = new Thread(new GetPhoneThread(files));
            threads[j].start();
            j++;
        }
        for(int i = 0; i < writers; i++){
            threads[j] = new Thread(new WriterThread(files));
            threads[j].start();
            j++;
        }

        threads[0].join();


    }
}
