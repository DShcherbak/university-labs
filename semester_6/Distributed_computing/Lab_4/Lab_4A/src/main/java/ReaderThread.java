import java.util.ArrayList;
import java.util.Random;

public class ReaderThread {

    public String GetRandomPositionFromFile(CustomFile nameFile){
        var namesLock = nameFile.getLock();
        String result = "";

        namesLock.lockRead();

        var n = nameFile.getLength();
        if(n > 0){
            Random rand = new Random();
            int c = rand.nextInt(n) + 1;
            result = nameFile.ReadLine(c);
        }


        namesLock.unlockRead();
        return result;
    }

    public ArrayList<String> GetPhoneBook(CustomFile phoneBookFile){
        ArrayList<String> result;
        var phoneBookLock = phoneBookFile.getLock();

        phoneBookLock.lockRead();
        result = phoneBookFile.ReadToEnd();
        phoneBookLock.unlockRead();
        return result;
    }

}
