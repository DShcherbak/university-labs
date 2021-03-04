import java.util.Random;

public class WriterThread extends ReaderThread implements Runnable {

    int id;
    CustomFile[] files;

    public WriterThread(CustomFile[] files){
        this.files = files;
    }

    @Override
    public void run(){
        for(int i = 0; i < 20; i++) {
            try {
                Thread.sleep(3000 + new Random().nextInt(5) * 1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            Random rand = new Random();
            if(rand.nextBoolean()){
                DeleteRandom();
            } else {
                InsertRandom();
            }
        }
    }

    private void DeleteRandom(){
        String pair = DeleteFromFile(files[0], null);
        if(pair.equals(""))
            return;
        System.out.println("Deleting: " + pair);
        String currentName = pair.split(",")[0];
        String currentPhone = pair.split(",")[1];
        DeleteFromFile(files[1], currentPhone);
        DeleteFromFile(files[2], currentName);
    }

    private String DeleteFromFile(CustomFile file, String ex){
        String target = "";
        var lock = file.getLock();
        lock.lockWrite();

        var n = file.getLength();
        if(n > 0){

            var list = file.ReadToEnd();
            n = list.size();
            int c = new Random().nextInt(n);
            StringBuilder newFile = new StringBuilder();

            for(int i = 0; i < n; i++){
                if((ex == null && i == c) || list.get(i).equals(ex))
                    target = list.get(i);
                else
                    newFile.append(list.get(i)).append("\n");
            }

            file.WriteFile(newFile.toString());
        }
        lock.unlockWrite();
        return target;
    }

    private void InsertRandom(){
        String name = RandomName();
        String phone = RandomPhone();
        System.out.println("Inserting: " + name + "," + phone);
        InsertIntoFile(files[0], name + "," + phone);
        InsertIntoFile(files[1], phone);
        InsertIntoFile(files[2], name);
    }

    private void InsertIntoFile(CustomFile file, String newLine){
        var lock = file.getLock();
        lock.lockWrite();

        var list = file.ReadToEnd();
        StringBuilder newFile = new StringBuilder();

        for(var line : list){
            newFile.append(line).append("\n");
        }
        newFile.append(newLine).append("\n");

        file.WriteFile(newFile.toString());
        lock.unlockWrite();
    }

    private String RandomName(){
        return new String(new char[]{Character.toUpperCase(Cons()), Vow(), Cons(), Cons(), Vow()});
    }

    private String RandomPhone(){
        return new String(new char[]{Digit(), Digit(), Digit(),
                                        '-',
                                        Digit(), Digit(), Digit(),
                                        '-',
                                        Digit(), Digit(),
                                        '-',
                                        Digit(), Digit()});
    }

    private char Vow(){
        String vowels = "aoiyue";
        return vowels.charAt(new Random().nextInt(6));
    }

    private char Cons(){
        String vowels = "qwrtpsdfghjklzxcvbnm";
        return vowels.charAt(new Random().nextInt(20));
    }

    private char Digit(){
        String vowels = "0123456789";
        return vowels.charAt(new Random().nextInt(10));
    }

}
