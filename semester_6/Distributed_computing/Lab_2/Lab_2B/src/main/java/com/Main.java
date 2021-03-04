package com;

import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicInteger;

public class Main {


    public static ArrayList<stolenObject> storage = new ArrayList<>();
    public static AtomicInteger stolenRevenue = new AtomicInteger(0);
    public static AtomicInteger peopleInSeats = new AtomicInteger(0);


    public static class Ivan implements Runnable {
        int count;

        public Ivan() {
        }

        public synchronized void run() {
            for(int i = 0; i < storage.size(); i++){
                try {
                    Thread.sleep(300);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                var target = storage.get(i);
                synchronized (target){
                    if(target.state == stolenObject.State.inStorage){
                        target.state = stolenObject.State.outOfStorage;
                        System.out.printf("Ivanchuk took %s from storage.\n", target.name);
                    }

                }
            }
            System.out.println("Ivanchuk: looks like I'm done");
            peopleInSeats.incrementAndGet();
        }
    }

    public static class Petrov implements Runnable {
        int count;

        public Petrov() {
        }

        public void transport(stolenObject target) {
            target.state = stolenObject.State.inTheCar;
            System.out.printf("Petrov put %s in the car.\n", target.name);

        }

        public synchronized void run() {

            int transported = 0, nextTransport = 0;
            while (transported < storage.size()) {
                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                boolean ok = false;
                var target = storage.get(nextTransport);
                synchronized (target) {
                    if (target.state == stolenObject.State.outOfStorage) {
                        transport(target);
                        nextTransport++;
                        transported++;
                        ok = true;
                    }
                }
                if (!ok) {
                    for (int i = 0; i < storage.size(); i++) {
                        target = storage.get(i);
                        synchronized (target) {
                            if (target.state == stolenObject.State.outOfStorage) {
                                transport(target);
                                nextTransport = i + 1;
                                transported++;
                            }
                        }
                    }
                }



            }
            System.out.println("Petrow: I'm done heve too");
            peopleInSeats.incrementAndGet();
        }
    }

    public static class Nechyporiuk implements Runnable {
        int count;

        public Nechyporiuk() {
        }

        public void count(stolenObject target) {
            target.state = stolenObject.State.Counted;
            int total = stolenRevenue.addAndGet(target.value);
            System.out.printf("Nechyporiuk counted %s, it costs %d\n", target.name, target.value);
            System.out.printf("Total value of stolen objects: %d\n", total);

        }


        public synchronized void run() {

            int transported = 0, nextCount = 0;
            while (transported < storage.size()) {
                try {
                    Thread.sleep(700);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                boolean ok = false;
                var target = storage.get(nextCount);
                synchronized (target) {
                    if (target.state == stolenObject.State.inTheCar) {
                        count(target);
                        nextCount++;
                        transported++;
                        ok = true;
                    }
                }
                if (!ok) {
                    for (int i = 0; i < storage.size(); i++) {
                        target = storage.get(nextCount);
                        synchronized (target) {
                            if (target.state == stolenObject.State.inTheCar) {
                                count(target);
                                nextCount = i + 1;
                                transported++;
                            }
                        }
                    }
                }
            }

            System.out.println("Nechyporiuk: let's get going");
            peopleInSeats.incrementAndGet();
        }
    }


    public static class Car implements Runnable {
        int count;

        public Car() {
        }

        public synchronized void run() {
            try {
                while(peopleInSeats.get() < 3){
                    Thread.sleep(100);
                }
                System.out.printf("*Car noice* They got away with %d dollars", stolenRevenue.get());
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        int numberOfObjects = 20;
        for(int i = 0; i < numberOfObjects; i++){
            storage.add(new stolenObject());
        }
        Thread IvanovThread = new Thread(new Ivan());
        Thread PetrovThread = new Thread(new Petrov());
        Thread NechyporiukThread = new Thread(new Nechyporiuk());
        Thread CarThread = new Thread(new Car());

        IvanovThread.start();
        PetrovThread.start();
        NechyporiukThread.start();
        CarThread.start();

        CarThread.join();

    }
}
