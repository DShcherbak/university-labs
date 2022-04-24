package connection.server;

import objects.DAO.iDAO;
import objects.DOM.XmlParser;
import connection.common.ServerInterface;
import objects.JDBC.JDBC;
import objects.entity.Department;
import objects.entity.Employee;
import objects.entity.HumanResources;
import org.javatuples.Pair;

import java.rmi.RemoteException;
import java.util.List;

public class RmiServerObject implements ServerInterface {
    iDAO dao;
    iDAO JDBC;
    iDAO XML;

    public RmiServerObject(){
        JDBC = new JDBC();
        XML = new XmlParser();
        dao = JDBC;

    }

    @Override
    public boolean read() {
        return dao.read();
    }

    @Override
    public boolean save() {
        return dao.save();
    }

    @Override
    public HumanResources getHumanResources(){
        return dao.getHumanResources();
    }

    @Override
    public String addDepartment(String name, long power) {
        return dao.addDepartment(name, power);
    }

    @Override
    public Pair<Department, String> getDepartment(long id) {
        return dao.getDepartment(id);
    }

    @Override
    public List<Department> getDepartments() {
        return dao.getDepartments();
    }

    @Override
    public String updateDepartment(long oldId, long newId, String name, long power) {
        return dao.updateDepartment(oldId, newId, name, power);
    }

    @Override
    public String deleteDepartment(long id) {
        return dao.deleteDepartment(id);
    }

    @Override
    public String addEmployee(String name, String surname, long salary, String position, long departmentId) {
        return dao.addEmployee(name, surname, salary, position, departmentId);
    }

    @Override
    public Pair<Employee, String> getEmployee(long id) {
        return dao.getEmployee(id);
    }

    @Override
    public List<Employee> getEmployees() {
        return dao.getEmployees();
    }

    @Override
    public String updateEmployee(long oldId, long newId, String name, String surname, long salary, String position, long departmentId) {
        return dao.updateEmployee(oldId, newId, name, surname, salary, position, departmentId);
    }

    @Override
    public String deleteEmployee(long id) {
        return dao.deleteEmployee(id);
    }

    @Override
    public Employee getEmployeeByName(String name) throws RemoteException {
        return dao.getEmployeeByName(name);
    }

    @Override
    public Department getDepartmentByName(String name) throws RemoteException {
        return dao.getDepartmentByName(name);
    }

    @Override
    public void switchToJDBC() throws RemoteException {
        dao = JDBC;
        dao.read();
    }

    @Override
    public void switchToXML() throws RemoteException {
        dao = XML;
        dao.read();
    }
}
