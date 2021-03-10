package com.company;

public class CustomCyclicBarrier {
    private final int threadNumber ;
    private final Runnable onBarrier;
    private int waitFor;

    public CustomCyclicBarrier(int number, Runnable onBarrier) {
        this.onBarrier = onBarrier;
        this.threadNumber = number;
        this.waitFor = number;
    }

    public CustomCyclicBarrier(int parties) {
        this.threadNumber = parties;
        this.onBarrier = null;
        waitFor = parties;
    }


    public synchronized void await() throws InterruptedException {
        --waitFor;
        if (waitFor == 0) {
            waitFor = threadNumber;
            notifyAll();
            if (onBarrier != null)
                onBarrier.run();
        } else {
            this.wait();
        }
    }

    public void printStatus() {
        System.out.println((threadNumber - waitFor) + " threads are waiting. " + waitFor + " left.\n");
    }
}