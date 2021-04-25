package common;

public class OnGameThread implements Runnable{

    String message;
    boolean first;
    GameInstance game;

    OnGameThread(GameInstance game, boolean first, String message){
        this.game = game;
        this.message = message;
        this.first = first;
    }
    @Override
    public synchronized void run() {
        String response = null;
        try {
            response =  game.getExchanger().exchange(message);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        if(first)
            game.setLeftMessage(response);
        else
            game.setRightMessage(response);

    }
}
