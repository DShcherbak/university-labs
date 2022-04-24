package objects.JDBC;

import objects.DAO.iDAO;
import objects.entity.Department;
import objects.entity.Employee;
import objects.entity.HumanResources;
import org.javatuples.Pair;

import javax.sql.rowset.CachedRowSet;
import javax.sql.rowset.RowSetFactory;
import javax.sql.rowset.RowSetProvider;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class JDBC implements iDAO {
    @Override
    public boolean read() {
        return true;
    }

    @Override
    public boolean save() {
        return true;
    }

    @Override
    public HumanResources getHumanResources() {
        var departments = getDepartments();
        return new HumanResources(departments);
    }

    @Override
    public String addDepartment(String name, long power) {
        String query = "insert into Department (name, power) "
                + "values ('" + name + "', " + power + ")";
        updateQuery(query);
        return "OK";
    }

    @Override
    public Pair<Department, String> getDepartment(long id) {
        Department result = null;
        try{
            CachedRowSet rs = selectQuery("select * from Department where id = " + id);
            while (rs.next()) {
                result = Department.parseDepartment(rs);
            }
            CachedRowSet rs1 = selectQuery("select * from Employee where departmentId = " + id);
            while (rs1.next()) {
                result.addEmployee(Employee.parseEmployee(rs1));
            }
        } catch (SQLException e) {
            System.out.println("Couldn't parse route: " + e.getMessage());
            return new Pair(null, "Couldn't parse route: " + e.getMessage());
        }
        return new Pair(result, "OK");
    }

    @Override
    public List<Department> getDepartments() {
        ArrayList<Department> result = new ArrayList<>();
        try{
            CachedRowSet rs = selectQuery("select * from Department");
            while (rs.next()) {
                var department = Department.parseDepartment(rs);
                result.add(department);
            }
            for (var department : result){
                CachedRowSet rs1 = selectQuery("select * from Employee where departmentId = " + department.getId());
                while (rs1.next()) {
                    department.addEmployee(Employee.parseEmployee(rs1));
                }
            }
        } catch (SQLException e) {
            System.out.println("Couldn't parse route: " + e.getMessage());
            return null;
        }
        return result;

    }

    @Override
    public String updateDepartment(long oldId, long newId, String name, long power) {
        if(oldId == newId){
            String query = "update Department set ";
            query += "name = '" + name + "', ";
            query += "power = " + power;
            query += " where id = " +  oldId;
            updateQuery(query);
            return "OK";
        } else {
            var result = getDepartment(newId);
            if(!result.getValue1().equals("OK")){
                String query = "update Department set ";
                query += "id = " + newId + ", ";
                query += "name = '" + name + "', ";
                query += "power = " + power;
                query += " where id = " +  oldId;
                updateQuery(query);
                return "OK";
            } else {
                return "Department with id = " + newId + " already exists.";
            }
        }
    }

    @Override
    public String deleteDepartment(long id) {
        var maybeDepartment = getDepartment(id);
        if(!maybeDepartment.getValue1().equals("OK")){
            return "No department with id = " + id;
        } else {
            var department = maybeDepartment.getValue0();
            for(var employee : department.getEmployees()){
                deleteEmployee(employee.getId());
            }
            String query = "delete from Department where id = " + id;
            updateQuery(query);
            return "OK";
        }

    }

    @Override
    public String addEmployee(String name, String surname, long salary, String position, long departmentId) {
        String query = "insert into Employee (name, surname, salary, position, departmentId) "
                + "values ('" + name + "', '" + surname + "', " + salary + ", '" + position + "', " + departmentId + ")";
        updateQuery(query);
        return "OK";
    }

    @Override
    public Pair<Employee, String> getEmployee(long id) {
        Employee result = null;
        try{
            CachedRowSet rs = selectQuery("select * from Employee where id = " + id);
            while (rs.next()) {
                result = Employee.parseEmployee(rs);
            }
        } catch (SQLException e) {
            System.out.println("Couldn't parse route: " + e.getMessage());
            return new Pair(null, "Couldn't parse route: " + e.getMessage());
        }
        return new Pair(result, "OK");
    }

    @Override
    public List<Employee> getEmployees() {
        ArrayList<Employee> result = new ArrayList<>();
        try{
            CachedRowSet rs = selectQuery("select * from Employee");
            while (rs.next()) {
                var employee = Employee.parseEmployee(rs);
                result.add(employee);
            }
        } catch (SQLException e) {
            System.out.println("Couldn't parse route: " + e.getMessage());
            return null;
        }
        return result;
    }

    @Override
    public String updateEmployee(long oldId, long newId, String name, String surname, long salary, String position, long departmentId) {
        if(oldId == newId){
            String query = "update Employee set ";
            query += "name = '" + name + "', ";
            query += "surname = '" + surname + "', ";
            query += "salary = " + salary + ", ";
            query += "position = '" + position + "', ";
            query += "departmentId = " + departmentId;
            query += " where id = " +  oldId;
            updateQuery(query);
            return "OK";
        } else {
            var result = getEmployee(newId);
            if(!result.getValue1().equals("OK")){
                String query = "update Department set ";
                query += "id = " + newId + ", ";
                query += "name = '" + name + "', ";
                query += "surname = '" + surname + "', ";
                query += "salary = " + salary + ", ";
                query += "position = '" + position + "', ";
                query += "departmentId = " + departmentId;
                query += " where id = " +  oldId;
                updateQuery(query);
                return "OK";
            } else {
                return "Employee with id = " + newId + " already exists.";
            }
        }
    }

    @Override
    public String deleteEmployee(long id) {
        String query = "delete from Employee where id = " + id;
        updateQuery(query);
        return "OK";
    }

    @Override
    public Department getDepartmentByName(String name) {
        ArrayList<Department> departments = (ArrayList<Department>) getDepartments();
        var department = departments.stream()
                .filter(department1 -> department1.getName().equals(name)).findFirst();
        if(department.isEmpty())
            return null;
        else
            return department.get();
    }

    @Override
    public Employee getEmployeeByName(String name) {
        ArrayList<Employee> employees = (ArrayList<Employee>) getEmployees();
        var employee = employees.stream()
                .filter(employee1 -> employee1.getFullName().equals(name)).findFirst();
        if(employee.isEmpty())
            return null;
        else
            return employee.get();

    }

    private CachedRowSet selectQuery(String query){
        try{
            RowSetFactory rowSetFactory = RowSetProvider.newFactory();
            CachedRowSet cachedRowSet = rowSetFactory.createCachedRowSet();
            try{
                Connection conn = ConnectionPool.getConnectionPool().getConnection();
                try (Statement stmt = conn.createStatement()) {
                    ResultSet rs = stmt.executeQuery(query);
                    cachedRowSet.populate(rs);
                } catch (SQLException e) {
                    e.printStackTrace();
                }
                ConnectionPool.getConnectionPool().releaseConnection(conn);
            }
            catch (Exception ex){
                ex.printStackTrace();
            }
            return cachedRowSet;
        }catch (SQLException throwable) {
            System.out.println("Couldn't create rowSetFactory.");
            throwable.printStackTrace();
        }
        return null;
    }

    private void updateQuery(String query) {
        try{
            Connection conn = ConnectionPool.getConnectionPool().getConnection();
            try (Statement stmt = conn.createStatement()) {
                stmt.executeUpdate(query);
            } catch (SQLException e) {
                e.printStackTrace();
            }
            ConnectionPool.getConnectionPool().releaseConnection(conn);
        }catch (Exception ex){
            ex.printStackTrace();
        }
    }
}
