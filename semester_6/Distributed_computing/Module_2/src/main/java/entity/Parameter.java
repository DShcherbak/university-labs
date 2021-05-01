package entity;

import java.io.Serializable;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Objects;
import java.util.Scanner;

public class Parameter implements Serializable {
    private int id;
    private String name;
    private String unit;
    private int groupId;

    public static Parameter parseParameter(ResultSet rs){
        try{
            int id = rs.getInt(1);
            String name = rs.getString(2);
            String unit = rs.getString(3);
            int groupId = rs.getInt(4);
            return new Parameter(id, name, unit, groupId);
        }catch (Exception ex){
            ex.printStackTrace();
        }
        return null;
    }

    public Parameter(int id, String name, String unit, int groupId) {
        this.id = id;
        this.name = name;
        this.unit = unit;
        this.groupId = groupId;
    }

    public Parameter(String name, String unit, int groupId) {
        this.name = name;
        this.unit = unit;
        this.groupId = groupId;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setUnit(String unit) {
        this.unit = unit;
    }

    @Override
    public String toString() {
        return "Parameter{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", unit='" + unit + '\'' +
                ", groupId=" + groupId +
                '}';
    }

    public void setGroupId(int groupId) {
        this.groupId = groupId;
    }

    public String toStringUpdate() {
        String result = "";
        if(id > 0){
            result = "id = " + id + ", ";
        }
        return result + "name='" + name + "', " +
                "unit='" + unit + "', " +
                "groupId=" + groupId;
    }

    public String toStringInsert(){
        return "'" + name + "', " +
                "'" + unit + "', " +
                "" + groupId;
    }

    public static Parameter createFromConsole(){
        Scanner input = new Scanner(System.in);
        Parameter result = null;
        System.out.print("Enter name: ");
        String name = input.next();
        System.out.print("Enter groupId: ");
        int groupId = input.nextInt();
        System.out.print("Enter unit: ");
        String unit = input.next();
        return new Parameter(name,unit, groupId);
    }
}

