package objects.DAO;

import objects.entity.Department;
import objects.entity.Employee;
import objects.entity.HumanResources;
import org.javatuples.Pair;

import java.util.ArrayList;
import java.util.List;

public class DAO implements iDAO{
    protected ArrayList<Department> departments;
    protected ArrayList<Employee> employees;

    public DAO(){
        departments = new ArrayList<>();
        employees = new ArrayList<>();
    }

    public static DAO createDAO(){
        DAO dao = new DAO();
        dao.read();
        return dao;
    }

    public boolean read(){
        return false;
    }

    public boolean save(){
        return false;
    }

    public HumanResources getHumanResources(){
        return null;
    }

    public String addDepartment(String name, long power){
        return "";
    }

    public Pair<Department, String> getDepartment(long id){
        return null;
    }
    public List<Department> getDepartments(){
        return departments;
    }
    public String updateDepartment(long oldId, long newId, String name, long power){
        return "";
    }

    public String deleteDepartment(long id){
        return "";
    }

    //------------------

    public String addEmployee(String name, String surname, long salary, String position, long departmentId){
        return "";
    }

    public Pair<Employee, String> getEmployee(long id){
        return null;
    }
    public List<Employee> getEmployees(){
        return employees;
    }
    public String updateEmployee(long oldId, long newId, String name, String surname, long salary, String position, long departmentId){
        return "";
    }

    public String deleteEmployee(long id){
        return "";
    }

    @Override
    public Department getDepartmentByName(String name) {
        return null;
    }

    @Override
    public Employee getEmployeeByName(String name) {
        return null;
    }

}
