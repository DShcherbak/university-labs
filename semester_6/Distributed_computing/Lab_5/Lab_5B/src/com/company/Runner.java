package com.company;

import java.util.Random;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class Runner implements Runnable{

    StringHolder myString;
    boolean goRunning;
    CyclicBarrier barrier;
    CancellationToken token;

    private String insertIntoPosition(StringHolder s, char c, int pos){
        return s.str.substring(0, pos) + c + s.str.substring(pos + 1);
    }

    private String revertChar(StringHolder s, int pos){
        return switch (s.str.charAt(pos)) {
            case 'A' -> insertIntoPosition(s, 'C', pos);
            case 'B' -> insertIntoPosition(s, 'D', pos);
            case 'C' -> insertIntoPosition(s, 'A', pos);
            default -> insertIntoPosition(s, 'B', pos);
        };
    }

    public Runner(StringHolder s, CyclicBarrier barrier, CancellationToken ct){
        myString = s;
        goRunning = true;
        this.barrier = barrier;
        token = ct;
    }

    @Override
    public void run() {
        while(goRunning){
            int p = new Random().nextInt(myString.str.length());
            boolean doChange = new Random().nextBoolean();
            if(doChange){
                myString.str = revertChar(myString, p);
            }
            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }
            goRunning = !token.isActive();
        }
    }
}
