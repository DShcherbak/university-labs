package com.main;

public class Main {
    static BinarySemaphore customerSemaphore = new BinarySemaphore();
    static BinarySemaphore barberSemaphore = new BinarySemaphore();
    //static Semaphore customerSemaphore = new Semaphore(1);
    //static Semaphore barberSemaphore = new Semaphore(1);

    public static class Customer implements Runnable{
        String name;
        public Customer(String name){
            this.name = name;
        }
        @Override
        public void run() {
            while(true){
                try {
                    customerSemaphore.acquire();
                    barberSemaphore.release();
                    System.out.println(name + " is in the chair");
                    Thread.sleep(100);
                    barberSemaphore.acquire();
                    System.out.println(name + " is happy with his/her new look");
                    customerSemaphore.release();
                    Thread.sleep(1000 * 100);

                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static class Barber implements Runnable {

        @Override
        public void run() {
            while(true){
                try {
                    barberSemaphore.acquire();
                    Thread.sleep(50);
                    System.out.println("com.main.Barber is working...");
                    Thread.sleep(200);
                    barberSemaphore.release();
                    Thread.sleep(50);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        barberSemaphore.acquire();
        Thread barber = new Thread(new Barber());
        barber.setDaemon(true);
        barber.start();
        int n = 5;
        Thread[] customers = new Thread[n];
        for(int i = 0; i < n; i++){
            char letter = (char) ((int) 'A' + i);
            customers[i] = new Thread(new Customer(letter + "anny"));
            customers[i].setDaemon(true);
            customers[i].start();
        }
        barber.join();
    }
}
