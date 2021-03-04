public class CustomReadWriteLock {
    private int currentReaders = 0;
    private int currentWriters = 0;
    private int writeRequests = 0;

    private synchronized void tryWait(){
        try{
            wait();
        } catch (InterruptedException ex){
            System.out.println("Exception: " + ex.getMessage());
        }
    }

    public synchronized void lockRead(){
        while(currentWriters > 0 || writeRequests > 0){
            tryWait();
        }
        currentReaders++;
    }

    public synchronized void unlockRead(){
        currentReaders--;
        notifyAll();
    }

    public synchronized void lockWrite(){
        writeRequests++;
        while(currentReaders > 0 && currentWriters > 0){
            tryWait();
        }
        writeRequests--;
        currentWriters++;
    }

    public synchronized void unlockWrite(){
        currentWriters--;
        notifyAll();
    }
}
