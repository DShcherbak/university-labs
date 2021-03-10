package com.company;

import java.util.Random;
import java.util.concurrent.CyclicBarrier;

public class Main {

    public static char GetRandomChar(){
        int r = new Random().nextInt(4);
        return switch (r) {
            case 0 -> 'A';
            case 1 -> 'B';
            case 2 -> 'C';
            default -> 'D';
        };
    }

    public static String GenerateRandomString(){
        StringBuilder result = new StringBuilder();
        for(int i = 0; i < 8; i++)
        {
            result.append(GetRandomChar());
        }
        return result.toString();
    }

    public static void main(String[] args) throws InterruptedException {
        var ct = new CancellationToken();

        StringHolder[] strings = new StringHolder[4];
        Thread[] threads = new Thread[4];
        CyclicBarrier bar = new CyclicBarrier(4, new Checker(ct, strings));
        for(int i = 0; i < 4; i++){
            strings[i] = new StringHolder(GenerateRandomString());
            threads[i] = new Thread(new Runner(strings[i], bar, ct));
            threads[i].start();
        }
        for(int i = 0; i < 4; i++)
            threads[i].join();
        System.out.println("===========================");
        System.out.println("FINAL STATE: ");
        for(int i = 0; i < 4; i++){
            System.out.println(strings[i].str);
        }

    }
}
