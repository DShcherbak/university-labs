package common;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.concurrent.Exchanger;
import java.util.concurrent.atomic.AtomicInteger;

public class ServerObject implements ServerInterface {

    AtomicInteger numberOfPlayers = new AtomicInteger(0);
    String firstClientMessage = "Hello, @, you play with # and your move is first!";
    String secondClientMessage = "Hello, @, you play with # and you move second, his move is e4!";
    MessageObject leftResponse;
    MessageObject rightResponse;
    Exchanger<MessageObject> registrationExchanger = new Exchanger<>();
    Map<Integer, GameInstance> games = new HashMap<>();
    Integer lastGameId = -1;

    @Override
    public MessageObject registerForGame(MessageObject requestMessage){
        Thread thread;
        if(games.size() == 2){
            return new MessageObject("Server error: too many players, try later");
        }
        if(numberOfPlayers.compareAndSet(0, 1)){
            try {
                lastGameId = Math.abs(new Random().nextInt()) / 10 * 10;
                int currentGame  = lastGameId;
                games.put(lastGameId, new GameInstance(lastGameId, lastGameId + 1, lastGameId + 2));
                thread = new Thread(new OnGameThread(games.get(currentGame), true, requestMessage.getMyMessage()));
                thread.start();
                thread.join();
                return new MessageObject(requestMessage.getMyMessage(), lastGameId+1, "You play with " + games.get(currentGame).getMessage(1));
            }catch(Exception ex){
                return new MessageObject("Server error: " + ex.getMessage());
            }
        }else if(numberOfPlayers.compareAndSet(1, 0)){
            try{
                int currentGame  = lastGameId;
                thread = new Thread(new OnGameThread(games.get(currentGame), false, requestMessage.getMyMessage()));
                thread.start();
                thread.join();
                return new MessageObject(requestMessage.getMyMessage(), lastGameId+2, "You play with " + games.get(currentGame).getMessage(2));
            }catch(Exception ex){
                return new MessageObject("Server error: " + ex.getMessage());
            }
        }
        return new MessageObject("Server error: unhandled move");
    }

    @Override
    public MessageObject performMove(MessageObject requestMessage){
        Thread thread;
        Integer gameId=requestMessage.clientId / 10 * 10;
        try{
            var game = games.get(gameId);
            thread = new Thread(new OnGameThread(game, requestMessage.clientId % 10 == 1, requestMessage.getMyMessage()));
            thread.start();
            thread.join();
            return new MessageObject(requestMessage.getMyMessage(), requestMessage.getClientId(), game.getMessage(requestMessage.clientId % 10));
        }catch(Exception ex){
            return new MessageObject("Server error: " + ex.getMessage());
        }
    }
}
