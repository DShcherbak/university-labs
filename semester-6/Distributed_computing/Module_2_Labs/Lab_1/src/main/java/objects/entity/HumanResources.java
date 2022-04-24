package objects.entity;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class HumanResources implements Serializable {
    public ArrayList<String> departments;
    public HashMap<String, ArrayList<String>> employees;

    public HumanResources(){
        departments = new ArrayList<>();
        employees = new HashMap<>();
    }

    public HumanResources(List<Department> departmentList){
        departments = new ArrayList<>();
        employees = new HashMap<>();
        for(var department : departmentList){
            departments.add(department.getName());
            employees.put(department.getName(), new ArrayList<>());
            for(var employee : department.getEmployees()){
                employees.get(department.getName()).add(employee.getFullName());
            }
        }
    }
}
