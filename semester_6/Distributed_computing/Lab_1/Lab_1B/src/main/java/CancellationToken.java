public class CancellationToken {
    boolean isAlive = true;

    public void cancel(){
        isAlive = false;
    }

    public boolean IsAlive(){
        return isAlive;
    }
}
