package main;

import java.util.Random;

public class Fighter {
    public enum Clan{
        Yin, Jang
    }

    int powerZi;
    String name;
    Clan clan;

    private String generateName(){
        String alphabet = "abcdefghijklmnopqrstuvwxyz";
        String name = "";
        var rand =new Random();
        int len = 5;
        for(int i = 0; i < len; i++){
            name = name.concat(String.valueOf(alphabet.charAt(rand.nextInt(26))));
        }
        return name;
    }

    public Fighter(int power, Clan clan){
        powerZi = power;
        this.clan = clan;
        name = generateName();
    }

}
