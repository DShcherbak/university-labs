import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Key {
    private ArrayList<BigInteger> Entity;

    public Key(BigInteger[] keys){
        Entity = new ArrayList<>();
        Entity.addAll(Arrays.asList(keys));
    }
    public Key(String path) throws FileNotFoundException {
        readFromFile(path);
    }

    public BigInteger get(int index){
        if (index >= Entity.size()) {
            throw new IllegalArgumentException("Out of key bounds exception");
        }
        return Entity.get(index);
    }

    public void readFromFile(String path) throws FileNotFoundException {
        Scanner scanner = new Scanner(new FileReader(path));
        Entity = new ArrayList<>();
        while (scanner.hasNextBigInteger()){
            Entity.add(scanner.nextBigInteger());
        }
        scanner.close();
    }

    public void writeToFile(String path) throws FileNotFoundException {
        PrintWriter printWriter = new PrintWriter(path);
        for (BigInteger element : Entity){
            printWriter.println(element);
        }
        printWriter.close();
    }
}
