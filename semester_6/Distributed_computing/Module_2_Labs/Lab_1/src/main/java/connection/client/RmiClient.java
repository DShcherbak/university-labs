package connection.client;

import connection.common.ServerInterface;
import objects.entity.Department;
import objects.entity.Employee;
import objects.entity.HumanResources;
import org.javatuples.Pair;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.List;

public class RmiClient implements iClient {
    ServerInterface server;
    @Override
    public boolean read() throws RemoteException {
        return server.read();
    }

    @Override
    public boolean save() throws RemoteException {
        return server.save();
    }

    @Override
    public HumanResources getHumanResources() throws RemoteException{
        return server.getHumanResources();
    }

    @Override
    public String addDepartment(String name, long power) throws RemoteException {
        return server.addDepartment(name, power);
    }

    @Override
    public Pair<Department, String> getDepartment(long id) throws RemoteException {
        return server.getDepartment(id);
    }

    @Override
    public List<Department> getDepartments() throws RemoteException {
        return server.getDepartments();
    }

    @Override
    public String updateDepartment(long oldId, long newId, String name, long power) throws RemoteException {
        return server.updateDepartment(oldId, newId, name, power);
    }

    @Override
    public String deleteDepartment(long id) throws RemoteException {
        return server.deleteDepartment(id);
    }

    @Override
    public String addEmployee(String name, String surname, long salary, String position, long departmentId) throws RemoteException {
        return server.addEmployee(name, surname, salary, position, departmentId);
    }

    @Override
    public Pair<Employee, String> getEmployee(long id) throws RemoteException {
        return server.getEmployee(id);
    }

    @Override
    public List<Employee> getEmployees() throws RemoteException {
        return server.getEmployees();
    }

    @Override
    public String updateEmployee(long oldId, long newId, String name, String surname, long salary, String position, long departmentId) throws RemoteException {
        return server.updateEmployee(oldId, newId, name, surname, salary, position, departmentId);
    }

    @Override
    public String deleteEmployee(long id) throws RemoteException {
        return server.deleteEmployee(id);
    }

    @Override
    public void connect() throws NotBoundException, RemoteException {
        Registry registry = LocateRegistry.getRegistry("127.0.0.1");
        server = (ServerInterface) registry.lookup("GameInstance");
    }

    @Override
    public Employee getEmployeeByName(String name) throws RemoteException {
        return server.getEmployeeByName(name);
    }

    @Override
    public Department getDepartmentByName(String name) throws RemoteException {
        return server.getDepartmentByName(name);
    }
}
