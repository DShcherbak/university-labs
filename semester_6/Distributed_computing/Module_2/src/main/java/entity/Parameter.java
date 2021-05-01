package entity;

import java.io.Serializable;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Objects;

public class Parameter implements Serializable {
    private long id;
    private String name;
    private String unit;
    private long groupId;

    public static Parameter parseParameter(ResultSet rs){
        try{
            String name = rs.getString(2);
            String unit = rs.getString(3);
            int groupId = rs.getInt(4);
            return new Parameter(name, unit, groupId);
        }catch (Exception ex){
            ex.printStackTrace();
        }
        return null;
    }

    public Parameter(String name, String unit, long groupId) {
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

    public void setGroupId(long groupId) {
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
}

