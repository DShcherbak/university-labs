package com.company;

import java.util.HashSet;
import java.util.Random;

public class Runner implements Runnable{

    ArrayHolder[] myArray;
    boolean goRunning;
    CustomCyclicBarrier barrier;
    CancellationToken token;
    int id;

    private int[] changeArray(int[] arr){
        Random random = new Random();
        int pos = random.nextInt(arr.length);
        int amount = random.nextInt(3) - 1;
        arr[pos] += amount;
        return arr;
    }

    private int sumOfArray(int[] arr){
        int sum = 0;
        for(var a : arr){
            sum += a;
        }
        return sum;
    }


    public Runner(ArrayHolder[] s, int id, CustomCyclicBarrier barrier, CancellationToken ct){
        myArray = s;
        goRunning = true;
        this.barrier = barrier;
        token = ct;
        this.id = id;
    }

    private void waitForBarrier(){
        try {
            barrier.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        while(goRunning){

            myArray[id].arr = changeArray(myArray[id].arr);
            System.out.println("Thread " + id + ": " + myArray[id].ToString() + " :: " + sumOfArray(myArray[id].arr));
            waitForBarrier();

            HashSet<Integer> numbers = new HashSet<>();
            for (ArrayHolder arrayHolder : myArray) {
                numbers.add(sumOfArray(arrayHolder.arr));
            }
            if(numbers.size() == 1)
                token.Activate();

            waitForBarrier();

            goRunning = !token.isActive();
        }
    }
}
