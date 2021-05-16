package objects.entity;

import java.io.Serializable;
import java.util.List;

public class Department implements Serializable {
    long id;
    String name;
    long power;
    List<Employee> employees;

    public Department(long id, String name, long power, List<Employee> employees) {
        this.id = id;
        this.name = name;
        this.power = power;
        this.employees = employees;
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

    public long getPower() {
        return power;
    }

    public void setPower(long power) {
        this.power = power;
    }

    public List<Employee> getEmployees() {
        return employees;
    }

    public void setEmployees(List<Employee> employees) {
        this.employees = employees;
    }

    public void addEmployee(Employee employee){
        this.employees.add(employee);
    }

    public void deleteEmployee(Employee employee){
        this.employees.remove(employee);
    }
}
