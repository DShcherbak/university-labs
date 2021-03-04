package com.main;

public class BinarySemaphore {
    volatile boolean taken = false;
    public synchronized void acquire() throws InterruptedException {
        if(taken){
            this.wait();
        }
        taken = true;
    }

    public synchronized void release(){
        taken = false;
        this.notify();
    }
}