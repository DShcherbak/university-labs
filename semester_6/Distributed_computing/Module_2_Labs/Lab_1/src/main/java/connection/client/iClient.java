package connection.client;

import connection.common.ServerInterface;
import objects.entity.Department;
import objects.entity.Employee;
import objects.entity.HumanResources;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;

public interface iClient extends ServerInterface{
    void connect() throws NotBoundException, RemoteException;

    Employee getEmployeeByName(String name) throws RemoteException;
    Department getDepartmentByName(String name) throws RemoteException;
}
