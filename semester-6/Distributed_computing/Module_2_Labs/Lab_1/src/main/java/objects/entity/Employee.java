package objects.entity;

import javax.sql.rowset.CachedRowSet;
import java.io.Serializable;

public class Employee implements Serializable {
    long id;
    String name;
    String surname;
    long salary;
    String position;
    long departmentId;



    public Employee(long id, String name, String surname, long salary, String position, long departmentId) {
        this.id = id;
        this.name = name;
        this.surname = surname;
        this.salary = salary;
        this.position = position;
        this.departmentId = departmentId;
    }

    public static Employee parseEmployee(CachedRowSet rs){
        try{
            long id = rs.getInt(1);
            String name = rs.getString(2);
            String surname = rs.getString(3);
            long salary = rs.getInt(4);
            String position = rs.getString(5);
            long departmentId = rs.getInt(6);
            return new Employee(id, name, surname, salary, position, departmentId);
        }catch (Exception ex){
            ex.printStackTrace();
        }
        return null;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSurname() {
        return surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public String getFullName(){
        return name + " " + surname;
    }

    public long getSalary() {
        return salary;
    }

    public void setSalary(long salary) {
        this.salary = salary;
    }

    public String getPosition() {
        return position;
    }

    public void setPosition(String position) {
        this.position = position;
    }

    public long getDepartmentId() {
        return departmentId;
    }

    public void setDepartmentId(long departmentId) {
        this.departmentId = departmentId;
    }
}
