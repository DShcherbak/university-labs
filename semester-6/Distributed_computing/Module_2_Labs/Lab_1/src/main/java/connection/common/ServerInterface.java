package connection.common;

import objects.entity.Department;
import objects.entity.Employee;
import objects.entity.HumanResources;
import org.javatuples.Pair;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

public interface ServerInterface extends Remote {
    boolean read() throws RemoteException;
    boolean save() throws RemoteException;
    HumanResources getHumanResources() throws RemoteException;

    String addDepartment(String name, long power) throws RemoteException;
    Pair<Department, String> getDepartment(long id) throws RemoteException;
    List<Department> getDepartments() throws RemoteException;
    String updateDepartment(long oldId, long newId, String name, long power) throws RemoteException;
    String deleteDepartment(long id) throws RemoteException;

    //------------------

    String addEmployee(String name, String surname, long salary, String position, long departmentId) throws RemoteException;
    Pair<Employee, String> getEmployee(long id) throws RemoteException;
    List<Employee> getEmployees() throws RemoteException;
    String updateEmployee(long oldId, long newId, String name, String surname, long salary, String position, long departmentId) throws RemoteException;
    String deleteEmployee(long id) throws RemoteException;

    Employee getEmployeeByName(String name) throws RemoteException;
    Department getDepartmentByName(String name) throws RemoteException;

    void switchToJDBC() throws RemoteException;
    void switchToXML() throws RemoteException;

}
