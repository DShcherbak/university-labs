package com.company;

public class CancellationToken {

    private boolean cancelled = false;
    public synchronized void Activate(){
        cancelled = true;
    }

    public synchronized boolean isActive(){
        return cancelled;
    }
}
