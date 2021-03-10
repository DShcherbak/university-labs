package com.company;

import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;

public class Checker implements Runnable{

    CancellationToken ct;
    StringHolder[] handler;

    public Checker(CancellationToken token, StringHolder[] handler){
        ct = token;
        this.handler = handler;
    }

    private int countZeros(String s){
        int result = 0;
        for(int i = 0; i < s.length(); i++){
            if(s.charAt(i) < 'C')
                result++;
        }
        return result;
    }

    @Override
    public void run() {
        int[] numbers = new int[4];
        for(int i = 0; i < 4; i++){
            numbers[i] = countZeros(handler[i].str);
            System.out.println(handler[i].str + " : " + numbers[i]);
        }
        Arrays.sort(numbers);
        if(numbers[1] == numbers[2] &&
                (numbers[0] == numbers[1] || numbers[2] == numbers[3])){
            ct.Activate();
        }
        System.out.println("---------------------------");
    }
}
