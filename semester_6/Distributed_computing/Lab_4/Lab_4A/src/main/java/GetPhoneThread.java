import java.util.ArrayList;
import java.util.Random;

public class GetPhoneThread extends ReaderThread implements Runnable{

    int id;
    CustomFile[] files;
    static int maxId;

    public GetPhoneThread(CustomFile[] files){
        this.files = files;
        id = maxId++;
    }

    @Override
    public void run(){
        for(int i = 0; i < 20; i++) {
            String name = GetName();
            String phone = "";
            if(!(phone = GetPhoneByName(name)).equals("")){
                System.out.println("Reader " + id + " found phone " + phone + " for the name " + name);
            } else {
                System.out.println("Reader " + id + " found no phone for the name: " + name);
            }
            try {
                Thread.sleep(3000 + new Random().nextInt(5) * 1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    String GetName(){
        var nameFile = files[2];
        return GetRandomPositionFromFile(nameFile);
    }

    private String GetPhoneByName(String name){
        ArrayList<String> namesAndPhones = GetPhoneBook(files[0]);

        for(var pair : namesAndPhones){
            String currentName = pair.split(",")[0];
            if(name.equals(currentName)){
                return pair.split(",")[1];
            }
        }
        return "";
    }
}
