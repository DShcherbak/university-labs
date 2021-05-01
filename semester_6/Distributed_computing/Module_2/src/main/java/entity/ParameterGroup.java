package entity;

import java.io.Serializable;
import java.sql.ResultSet;
import java.util.Objects;

public class ParameterGroup implements Serializable {
    private long id;
    private String name;

    public static ParameterGroup parseParameterGroup(ResultSet rs){
        try{
            int id = rs.getInt(1);
            String name = rs.getString(2);
            return new ParameterGroup(id, name);
        }catch (Exception ex){
            ex.printStackTrace();
        }
        return null;
    }

    public ParameterGroup(int id, String name) {
        this.id = id;
        this.name = name;
    }

    public ParameterGroup(String name) {
        this.name = name;
    }

    public String toStringUpdate() {
        String result = "";
        if(id > 0){
            result = "id = " + id + ", ";
        }
        return result + "name='" + name + "'";
    }

    public String toStringInsert(){
        return "'" + name + "'";
    }
}
