package com;

import java.util.Random;

public class stolenObject {
    public enum State{
        inStorage, outOfStorage, inTheCar, Counted
    }
    String name;
    int value;
    State state;

    public stolenObject(){

        String alphabet = "abcdefghijklmnopqrstuvwxyz";
        name = "";
        var rand =new Random();
        int len = rand.nextInt(9) + 1;
        for(int i = 0; i < len; i++){
            name = name.concat(String.valueOf(alphabet.charAt(rand.nextInt(26))));
        }
        value = rand.nextInt(120);
        if(value > 110){
            value *= 100;
        }
        if(value > 100){
            value *= 100;
            value += rand.nextInt(120);
        }
        state = State.inStorage;
    }
}
