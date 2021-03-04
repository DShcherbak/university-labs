import java.util.ArrayList;
import java.util.Random;

public class GetNameThread extends ReaderThread implements Runnable{

        int id;
        CustomFile[] files;
        static int maxId = 0;

        public GetNameThread(CustomFile[] files){
            this.files = files;
            id = maxId++;
        }

        @Override
        public void run(){
            for(int i = 0; i < 20; i++) {
                String phone = GetPhone();
                String name = "";
                if(!(name = GetNameByPhone(phone)).equals("")){
                    System.out.println("Reader " + id + " found name " + name + " for the phone " + phone);
                } else {
                    System.out.println("Reader " + id + " found no name for the phone: " + phone);
                }
                try {
                    Thread.sleep(3000 + new Random().nextInt(5) * 1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

        String GetPhone(){
            var nameFile = files[1];
            return GetRandomPositionFromFile(nameFile);
        }

        private String GetNameByPhone(String phone){
            ArrayList<String> namesAndPhones = GetPhoneBook(files[0]);

            for(var pair : namesAndPhones){
                String currentPhone = pair.split(",")[1];
                if(phone.equals(currentPhone)){
                    return pair.split(",")[0];
                }
            }
            return "";
        }
    }

