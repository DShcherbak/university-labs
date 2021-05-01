package entity;

import javax.sql.RowSet;
import java.io.Serializable;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.Objects;

public class Product implements Serializable {
    private long id;
    private String name;
    private String description;
    private long groupId;
    private Timestamp timestamp;

    public static Product parseProduct(RowSet rs) {
        try {
            int id = rs.getInt(1);
            String name = rs.getString(2);
            String description = rs.getString(4);
            int groupId = rs.getInt(3);
            Timestamp time = rs.getTimestamp(5);
            return new Product(id, name, groupId, description, time);
        }catch (Exception ex) {
            ex.printStackTrace();
        }
        return null;
    }


    public Product(long id, String name, long groupId, String description, Timestamp timestamp) {
        this.id = id;
        this.name = name;
        this.groupId = groupId;
        this.description = description;
        this.timestamp = timestamp;
    }

    public Product(String name, long groupId, String description, Timestamp timestamp) {
        this.name = name;
        this.groupId = groupId;
        this.description = description;
        this.timestamp = timestamp;
    }

    @Override
    public String toString() {
        return "Product{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", groupId=" + groupId +
                ", description='" + description + '\'' +
                ", timestamp=" + timestamp +
                '}';
    }


    public String toStringUpdate() {
        String result = "";
        if(id > 0){
            result = "id = " + id + ", ";
        }
        return result + "name='" + name + "', " +
                "groupId=" + groupId + ", " +
                "description='" + description + "', " +
                "creationDate='" + timestamp.toString() + "'";
    }

    public String toStringInsert(){
        return "'" + name + "', " +
                "" + groupId + ", " +
                "'" + description + "', " +
                "'" + timestamp.toString() + "'";

    }
}

