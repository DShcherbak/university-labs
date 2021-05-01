package entity;

import java.io.Serializable;
import java.sql.ResultSet;
import java.sql.Timestamp;
import java.util.Scanner;

public class ProductGroup implements Serializable {
    private long id;
    private String name;

    public static ProductGroup parseProductGroup(ResultSet rs){
        try{
            int id = rs.getInt(1);
            String name = rs.getString(2);
            return new ProductGroup(id, name);
        }catch (Exception ex){
            ex.printStackTrace();
        }
        return null;
    }

    public ProductGroup(int id, String name) {
        this.id = id;
        this.name = name;
    }

    public ProductGroup(String name) {
        this.name = name;
    }

    public String toStringUpdate() {
        String result = "";
        if(id > 0){
            result = "id = " + id + ", ";
        }
        return result + "name='" + name + "'";
    }

    @Override
    public String toString() {
        return "ProductGroup{" +
                "id=" + id +
                ", name='" + name + '\'' +
                '}';
    }

    public String toStringInsert(){
        return "'" + name + "'";
    }

    public static ProductGroup createFromConsole(){
        Scanner input = new Scanner(System.in);
        System.out.print("Enter name: ");
        String name = input.next();
        return new ProductGroup(name);
    }
}
