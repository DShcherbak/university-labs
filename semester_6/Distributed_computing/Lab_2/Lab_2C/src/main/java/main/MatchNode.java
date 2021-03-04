package main;

import java.util.Random;

public class MatchNode {
    Fighter fighter1;
    Fighter fighter2;
    MatchNode left;
    MatchNode right;
    int winner = 0;

    public MatchNode(Fighter n1, Fighter n2, MatchNode left, MatchNode right){
        fighter1 = n1;
        fighter2 = n2;
        this.left = left;
        this.right = right;
        if(left == null && right == null){
            winner = 0;
        }
        else if(left == null){
            winner = 2;
        }
        else if(right == null){
            winner = 1;
        } else {
            winner = 0;
        }
    }

    public void performMatch() throws InterruptedException {
        System.out.println("Match started...");
        Thread leftMatch = null;
        Thread rightMatch = null;
        if(left != null && left.winner == 0){
            leftMatch = new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        left.performMatch();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            });
            leftMatch.start();
            leftMatch.join();
        }
        if(right != null && right.winner == 0){
            rightMatch = new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        right.performMatch();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            });
            rightMatch.start();
            rightMatch.join();
        }

        if(left != null){
            fighter1 = left.winner == 1 ? left.fighter1 : left.fighter2;
        }
        if(right != null){
            fighter2 = right.winner == 1 ? right.fighter1 : right.fighter2;
        }
        if(fighter1 == null){
            winner = 2;
            return;
        }

        if(fighter2 == null){
            winner = 1;
            return;
        }

        if(Math.abs(fighter1.powerZi - fighter2.powerZi) < 10){
            System.out.println("Epic battle");
        } else if (Math.abs(fighter1.powerZi - fighter2.powerZi) > 50){
            System.out.println("Flawless victory");
        }
        if(fighter1.powerZi == fighter2.powerZi){
            System.out.println("Legendary battle!");
            var rand = new Random();
            winner = 2 - (rand.nextInt() % 2);
            return;
        }
        winner = fighter1.powerZi > fighter2.powerZi ? 1 : 2;
    }

    public void printResult(int depth){
        System.out.print('|');
        for(int i = 0; i < depth; i++){
            System.out.print("\t|");
        }
        String match = GetMatchResult();
        System.out.println("---" + match);
        if(left != null)
            left.printResult(depth + 1);
        for(int i = 0; i < depth; i++){
            System.out.print("\t|");
        }
        System.out.println("\n");
        if(right != null)
            right.printResult(depth + 1);

    }

    public String GetMatchResult(){
        String match = "";
        if(winner > 0){
            if(fighter1 == null && fighter2 == null){
                match = "No match here";
            }
            else if(fighter1 == null){
                match = "(" + 1 + ")"+fighter2.name;
            }
            else if(fighter2 == null){
                match = "(" + 1 + ")"+fighter1.name;
            }
            else {
                match = "(" + winner + ")"+fighter1.name + "."+fighter2.name;
            }
        }else {
            match = "winner is not established yet.";
        }
        return match;
    }
}
