package objects.DAO;

import objects.entity.Department;
import objects.entity.Employee;
import objects.entity.HumanResources;
import org.javatuples.Pair;
import java.util.List;

public interface iDAO {
    boolean read();
    boolean save();
    HumanResources getHumanResources();

    String addDepartment(String name, long power);
    Pair<Department, String> getDepartment(long id);
    List<Department> getDepartments();
    String updateDepartment(long oldId, long newId, String name, long power);
    String deleteDepartment(long id);

    //------------------

    String addEmployee(String name, String surname, long salary, String position, long departmentId);
    Pair<Employee, String> getEmployee(long id);
    List<Employee> getEmployees();
    String updateEmployee(long oldId, long newId, String name, String surname, long salary, String position, long departmentId);
    String deleteEmployee(long id);

    Department getDepartmentByName(String name);
    Employee getEmployeeByName(String name);
}