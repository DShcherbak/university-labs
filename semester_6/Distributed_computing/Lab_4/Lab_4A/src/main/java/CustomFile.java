import java.io.*;
import java.util.ArrayList;

public class CustomFile {

    String path;
    int length = 0;
    CustomReadWriteLock lock;

    private void recountLength(){
        length = 0;
        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            String s;
            while(true){
                s = br.readLine();
                if(s == null)
                    return;
                length++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public CustomFile(String path){
        this.path = path;
        recountLength();
        lock = new CustomReadWriteLock();
    }

    public int getLength(){
        return length;
    }

    public CustomReadWriteLock getLock(){
        return lock;
    }


    public ArrayList<String> ReadToEnd() {
        ArrayList<String> result = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            String s;
            while(true){
                s = br.readLine();
                if(s == null)
                    break;
                result.add(s);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return result;
    }

    public String ReadLine(int c) {
        String result = "";
        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            for(int i = 0; i < c; i++){
                result = br.readLine();
                if(result == null)
                    return "";
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return result;
    }

    public void WriteFile(String fileContains)  {
        try (BufferedWriter br = new BufferedWriter(new FileWriter(path))) {
            br.write(fileContains);
        } catch (IOException e) {
            e.printStackTrace();
        }
        recountLength();
    }
}
