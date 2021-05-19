package connection.client;

import objects.entity.Department;
import objects.entity.Employee;
import objects.entity.HumanResources;
import org.javatuples.Pair;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.List;

public class SocketClient implements iClient{

    ObjectOutputStream out = null;
    ObjectInputStream in = null;

    public SocketClient(ObjectInputStream in, ObjectOutputStream out){
        this.in = in;
        this.out = out;
    }

    @Override
    public void connect() throws NotBoundException, RemoteException {
        read();
    }

    @Override
    public boolean read() throws RemoteException {
        //Parameter p = Parameter.createFromConsole();
        try{
            out.writeObject("/read");
            out.flush();
            var result = in.readBoolean();
            return result;
        }catch (Exception ex){
            System.out.println("Couldn't send socket request: " + ex.getMessage());
            return false;
        }
    }

    @Override
    public boolean save() throws RemoteException {
        try{
            out.writeObject("/save");
            out.flush();
            var result = in.readBoolean();
            return result;
        }catch (Exception ex){
            System.out.println("Couldn't send socket request: " + ex.getMessage());
            return false;
        }
    }

    @Override
    public HumanResources getHumanResources() throws RemoteException {
        try{
            out.writeObject("/humanResources");
            out.flush();
            var result = (HumanResources) in.readObject();
            return result;
        }catch (Exception ex){
            System.out.println("Couldn't send socket request: " + ex.getMessage());
            return null;
        }
    }

    @Override
    public String addDepartment(String name, long power) throws RemoteException {
        try{
            out.writeObject("/department/add");
            out.writeObject(name);
            out.writeLong(power);
            out.flush();
            var result = (String) in.readObject();
            return result;
        }catch (Exception ex){
            System.out.println("Couldn't send socket request: " + ex.getMessage());
            return null;
        }
    }

    @Override
    public Pair<Department, String> getDepartment(long id) throws RemoteException {
        try{
            out.writeObject("/department/get");
            out.writeLong(id);
            out.flush();
            var result = (Pair<Department, String>) in.readObject();
            return result;
        }catch (Exception ex){
            System.out.println("Couldn't send socket request: " + ex.getMessage());
            return null;
        }
    }

    @Override
    public List<Department> getDepartments() throws RemoteException {
        try{
            out.writeObject("/department/all");
            out.flush();
            var result = (List<Department>) in.readObject();
            return result;
        }catch (Exception ex){
            System.out.println("Couldn't send socket request: " + ex.getMessage());
            return null;
        }
    }

    @Override
    public String updateDepartment(long oldId, long newId, String name, long power) throws RemoteException {
        try{
            out.writeObject("/department/update");
            out.writeLong(oldId);
            out.writeLong(newId);
            out.writeObject(name);
            out.writeLong(power);
            out.flush();
            var result = (String) in.readObject();
            return result;
        }catch (Exception ex){
            System.out.println("Couldn't send socket request: " + ex.getMessage());
            return null;
        }
    }

    @Override
    public String deleteDepartment(long id) throws RemoteException {
        try{
            out.writeObject("/department/delete");
            out.writeLong(id);
            out.flush();
            var result = (String) in.readObject();
            return result;
        }catch (Exception ex){
            System.out.println("Couldn't send socket request: " + ex.getMessage());
            return null;
        }
    }

    @Override
    public String addEmployee(String name, String surname, long salary, String position, long departmentId) throws RemoteException {
        try{
            out.writeObject("/employee/add");
            out.writeObject(name);
            out.writeObject(surname);
            out.writeLong(salary);
            out.writeObject(position);
            out.writeLong(departmentId);
            out.flush();
            var result = (String) in.readObject();
            return result;
        }catch (Exception ex){
            System.out.println("Couldn't send socket request: " + ex.getMessage());
            return null;
        }
    }

    @Override
    public Pair<Employee, String> getEmployee(long id) throws RemoteException {
        try{
            out.writeObject("/employee/get");
            out.writeLong(id);
            out.flush();
            var result = (Pair<Employee, String>) in.readObject();
            return result;
        }catch (Exception ex){
            System.out.println("Couldn't send socket request: " + ex.getMessage());
            return null;
        }
    }

    @Override
    public List<Employee> getEmployees() throws RemoteException {
        try{
            out.writeObject("/employee/all");
            out.flush();
            var result = (List<Employee>) in.readObject();
            return result;
        }catch (Exception ex){
            System.out.println("Couldn't send socket request: " + ex.getMessage());
            return null;
        }
    }

    @Override
    public String updateEmployee(long oldId, long newId, String name, String surname, long salary, String position, long departmentId) throws RemoteException {
        try{
            out.writeObject("/employee/update");
            out.writeLong(oldId);
            out.writeLong(newId);
            out.writeObject(name);
            out.writeObject(surname);
            out.writeLong(salary);
            out.writeObject(position);
            out.writeLong(departmentId);
            out.flush();
            var result = (String) in.readObject();
            return result;
        }catch (Exception ex){
            System.out.println("Couldn't send socket request: " + ex.getMessage());
            return null;
        }
    }

    @Override
    public String deleteEmployee(long id) throws RemoteException {
        try{
            out.writeObject("/employee/delete");
            out.writeLong(id);
            out.flush();
            var result = (String) in.readObject();
            return result;
        }catch (Exception ex){
            System.out.println("Couldn't send socket request: " + ex.getMessage());
            return null;
        }
    }

    @Override
    public Employee getEmployeeByName(String name) throws RemoteException {
        try{
            out.writeObject("/employee/getByName");
            out.writeObject(name);
            out.flush();
            var result = (Employee) in.readObject();
            return result;
        }catch (Exception ex){
            System.out.println("Couldn't send socket request: " + ex.getMessage());
            return null;
        }
    }

    @Override
    public Department getDepartmentByName(String name) throws RemoteException {
        try{
            out.writeObject("/department/getByName");
            out.writeObject(name);
            out.flush();
            var result = (Department) in.readObject();
            return result;
        }catch (Exception ex){
            System.out.println("Couldn't send socket request: " + ex.getMessage());
            return null;
        }
    }
}
