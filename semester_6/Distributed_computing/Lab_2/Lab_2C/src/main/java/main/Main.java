package main;

import java.util.ArrayList;
import java.util.Random;

public class Main {

    public static class Tournament implements Runnable {
        int count;
        ArrayList<MatchNode> currentNodes = new ArrayList<>();
        MatchNode root;

        public Tournament(ArrayList<Fighter> fighters) {
            for(int i = 0; i < fighters.size(); i+=2){
                if(i + 1 < fighters.size()){
                    currentNodes.add(new MatchNode(fighters.get(i), fighters.get(i + 1), null, null));
                }
            }
            if(fighters.size() % 2 == 1){
                currentNodes.add(new MatchNode(fighters.get(fighters.size() - 1), null, null, null));
            }
            int n = currentNodes.size();


            while(n > 1){
                ArrayList<MatchNode> nextNodes = new ArrayList<>();
                for(int i = 0; i < n; i+=2) {
                    if(i + 1 < n){
                        nextNodes.add(new MatchNode(null, null, currentNodes.get(i), currentNodes.get(i+1)));
                    }
                }
                if(n % 2 == 1){
                    nextNodes.add(new MatchNode(null, null, currentNodes.get(n-1), null));
                }
                currentNodes = nextNodes;
                n = currentNodes.size();
            }
            root = currentNodes.get(0);
        }




        public void run() {
            try {
                root.performMatch();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            if(root.winner == 0){
                System.out.print("Something went wrong...");
            }
            else {
                var champion = root.winner == 1 ? root.fighter1 : root.fighter2;
                System.out.println(champion.clan + " is the winner");
            }
            root.printResult(0);
        }
    }


    public static void main(String[] args) throws InterruptedException {
        System.out.println("\n\n");
        int numberOfFighters = 5;
        var rand = new Random();
        ArrayList<Fighter> fighters = new ArrayList<>();
        for(int i = 0; i < numberOfFighters; i++){
            fighters.add(new Fighter(rand.nextInt(100), i % 2 == 0 ? Fighter.Clan.Yin : Fighter.Clan.Jang));
        }
        Thread tournament = new Thread(new Tournament(fighters));
        tournament.start();
        tournament.join();
        System.out.println("\n\n\n\n\n");

    }
}
