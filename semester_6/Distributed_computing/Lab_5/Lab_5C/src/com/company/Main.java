package com.company;

import java.util.Random;
import java.util.concurrent.CyclicBarrier;

public class Main {

    int length = 8;

    public static int[] GenerateRandomArray(){
        int[] result = new int[8];
        Random rnd = new Random();
        for(int i = 0; i < 8; i++)
        {
            result[i] = rnd.nextInt(10);
        }
        return result;
    }

    public static void main(String[] args) throws InterruptedException {
        var ct = new CancellationToken();

        ArrayHolder[] ar = new ArrayHolder[3];
        Thread[] threads = new Thread[3];
        CustomCyclicBarrier bar = new CustomCyclicBarrier(3);
        for(int i = 0; i < 3; i++){
            ar[i] = new ArrayHolder(GenerateRandomArray());
            threads[i] = new Thread(new Runner(ar, i, bar, ct));
            threads[i].start();
        }
        for(int i = 0; i < 3; i++)
            threads[i].join();
        System.out.println("===========================");
        System.out.println("FINAL STATE: ");
        for(int i = 0; i < 3; i++){
            System.out.println(ar[i].ToString());
        }

    }
}
