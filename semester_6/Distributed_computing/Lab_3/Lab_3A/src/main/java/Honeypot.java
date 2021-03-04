public class Honeypot {
    private int volume = 0;
    private int maxVolume = 10;

    public boolean isFull(){
        return  volume == maxVolume;
    }

    public void insertHoney(){
        volume++;
    }

    public boolean eatHoney(){
        if(volume > 0){
            volume = 0;
            return true;
        }
        return false;

    }

}
