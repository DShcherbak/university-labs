package objects.DOM;

import objects.entity.Department;
import objects.entity.Employee;
import objects.entity.HumanResources;
import org.javatuples.Pair;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

import objects.DAO.iDAO;

public class XmlParser implements iDAO {
    protected ArrayList<Department> departments;
    protected ArrayList<Employee> employees;

    public XmlParser(){
        departments = new ArrayList<>();
        employees = new ArrayList<>();
    }

    @Override
    public boolean read() {
        try{
            departments = new ArrayList<>();
            employees = new ArrayList<>();
            loadFromFile("humanResources.xml");
        }catch (Exception ex){
            System.out.println("Error while loading from xml-file: " + ex.getMessage());
            return false;
        }
        return true;
    }

    @Override
    public boolean save() {
        try{
            saveToFile("humanResources.xml");
        }catch (Exception ex){
            System.out.println("Error while saving to xml-file: " + ex.getMessage());
            return false;
        }
        return true;
    }

    @Override
    public HumanResources getHumanResources() {
        HumanResources hr = new HumanResources();
        hr.departments = (ArrayList<String>) departments.stream()
                .map(Department::getName).collect(Collectors.toList());
        for(var department : departments){
            hr.employees.put(department.getName(), new ArrayList<>());
            for(var employee : department.getEmployees()){
                hr.employees.get(department.getName()).add(employee.getFullName());
            }
        }
        return hr;
    }

    @Override
    public String addDepartment(String name, long power) {
        long id;
        try{
            id = getNextDepartmentId();
            addDepartmentInternal(id, name, power);
        }catch (Exception ex){
            return "Couldn't add new department: " + ex.getMessage();
        }
        return String.valueOf(id);
    }

    @Override
    public Pair<Department, String> getDepartment(long id){
        Department department;
        try{
            department = getDepartmentInternal(id);
        }catch (Exception ex){
            return new Pair<>(null, "Couldn't get department " + ex.getMessage());
        }
        return new Pair<>(department, "OK");
    }


    @Override
    public List<Department> getDepartments() {
        return departments;
    }

    @Override
    public String updateDepartment(long oldId, long newId, String name, long power) {
        try{
            updateDepartmentInternal(oldId, newId, name, power);
        }catch (Exception ex){
            return "Couldn't update " + ex.getMessage();
        }
        return "OK";
    }


    @Override
    public String deleteDepartment(long departmentId){
        try{
            deleteDepartmentInternal(departmentId);
        }catch (Exception ex){
            return "Error while trying to delete department: " + ex.getMessage();
        }
        return "OK";
    }

    @Override
    public String addEmployee(String name, String surname, long salary, String position, long departmentId) {
        long id;
        try{
            id = getNextEmployeeId();
            addEmployeeInternal(id, name, surname, salary, position, departmentId);
        }catch (Exception ex){
            return "Couldn't add new department: " + ex.getMessage();
        }
        return String.valueOf(id);
    }

    @Override
    public Pair<Employee, String> getEmployee(long id){
        Employee employee;
        try{
            employee = getEmployeeInternal(id);
        }catch (Exception ex){
            return new Pair<>(null, "Couldn't get department " + ex.getMessage());
        }
        return new Pair<>(employee, "OK");
    }

    @Override
    public List<Employee> getEmployees() {
        return employees;
    }

    @Override
    public String updateEmployee(long oldId, long newId, String name, String surname, long salary, String position, long departmentId) {
        try{
            updateEmployeeInternal(oldId, newId, name, surname, salary, position, departmentId);
        }catch (Exception ex){
            return "Couldn't update " + ex.getMessage();
        }
        return "OK";
    }

    @Override
    public String deleteEmployee(long employeeId){
        try{
            deleteEmployeeInternal(employeeId);
        }catch (Exception ex){
            return "Error while trying to delete employee: " + ex.getMessage();
        }
        return "OK";
    }

    @Override
    public Department getDepartmentByName(String name) {
        var department = departments.stream()
                .filter(department1 -> department1.getName().equals(name)).findFirst();
        if(department.isEmpty())
            return null;
        else
            return department.get();
    }

    @Override
    public Employee getEmployeeByName(String name) {
        var employee = employees.stream()
                .filter(employee1 -> employee1.getFullName().equals(name)).findFirst();
        if(employee.isEmpty())
            return null;
        else
            return employee.get();
    }

    public void saveToFile(String filename) throws TransformerException, ParserConfigurationException {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        factory.setValidating(true);
        DocumentBuilder builder = factory.newDocumentBuilder();

        var doc = builder.newDocument();
        Element root = doc.createElement("HumanResources");
        doc.appendChild(root);

        for (Department department : departments) {
            Element departmentElem = doc.createElement("Department");
            departmentElem.setAttribute("id", String.valueOf(department.getId()));
            departmentElem.setAttribute("name", department.getName());
            departmentElem.setAttribute("power", String.valueOf(department.getPower()));
            root.appendChild(departmentElem);

            for (Employee employee : department.getEmployees()) {
                Element employeeElem = doc.createElement("Employee");
                employeeElem.setAttribute("id", String.valueOf(employee.getId()));
                employeeElem.setAttribute("name", employee.getName());
                employeeElem.setAttribute("surname", employee.getSurname());
                employeeElem.setAttribute("salary", String.valueOf(employee.getSalary()));
                employeeElem.setAttribute("position", employee.getPosition());
                employeeElem.setAttribute("departmentId", String.valueOf(employee.getDepartmentId()));
                departmentElem.appendChild(employeeElem);
            }
        }
        Source domSource = new DOMSource(doc);
        Result fileResult = new StreamResult(new File(filename));
        TransformerFactory transformerFactory = TransformerFactory.newInstance();
        Transformer transformer = transformerFactory.newTransformer();
        transformer.setOutputProperty(OutputKeys.ENCODING, "UTF-8");
        transformer.transform(domSource, fileResult);
    }

    public void loadFromFile(String filename) throws Exception
    {
        DocumentBuilderFactory dbf = null;
        DocumentBuilder documentBuilder = null;

        dbf = DocumentBuilderFactory.newInstance();
        //dbf.setValidating(true);
        documentBuilder = dbf.newDocumentBuilder();
        documentBuilder.setErrorHandler(new SimpleErrorHandler());
        Document document = documentBuilder.parse(filename);

        Element root = document.getDocumentElement();
        if (root.getTagName().equals("HumanResources"))
        {
            NodeList departmentsNodeList = root.getElementsByTagName("Department");
            for (int i = 0; i < departmentsNodeList.getLength(); i++)
            {
                Element departmentElement = (Element)departmentsNodeList.item(i);
                long id = Long.parseLong(departmentElement.getAttribute("id"));
                String departmentName = departmentElement.getAttribute("name");
                long power = Long.parseLong(departmentElement.getAttribute("power"));
                Department department = new Department(id, departmentName, power, new ArrayList<>());
                departments.add(department);
                NodeList employeesNodeList = departmentElement.getElementsByTagName("Employee");
                for (int j = 0; j < employeesNodeList.getLength(); j++)
                {
                    Element employeeElement = (Element)employeesNodeList.item(j);
                    long employeeId = Long.parseLong(employeeElement.getAttribute("id"));
                    String name = employeeElement.getAttribute("name");
                    String surname = employeeElement.getAttribute("surname");
                    long salary = Long.parseLong(employeeElement.getAttribute("salary"));
                    String position = employeeElement.getAttribute("position");
                    long departmentId = Long.parseLong(employeeElement.getAttribute("departmentId"));
                    Employee employee = new Employee(employeeId, name, surname, salary, position, departmentId);
                    employees.add(employee);
                    department.addEmployee(employee);
                }
            }
        } else {
            throw new Exception("Couldn't parse XML file root");
        }
    }


    public void addDepartmentInternal(long id, String name, long power)
    {
        ArrayList<Employee> employees = new ArrayList<Employee>();
        addDepartmentInternal(id,name,power,employees);
    }

    public void addDepartmentInternal(long id, String name, long power, ArrayList<Employee> employees)
    {
        for(var department : departments){
            if(department.getId() == id){
                return;
            }
        }
        departments.add(new Department(id, name, power, employees));
    }

    public Department getDepartmentInternal(long id) throws Exception
    {
        var department = departments.stream()
                .filter(department1 -> department1.getId() == id).findFirst();
        if(department.isEmpty())
            throw new Exception("No department with id " + id);
        else
            return department.get();
    }

    public long getNextDepartmentId(){
        long maxId = -1;
        for(var department : departments){
            if(department.getId() >= maxId){
                maxId = department.getId() + 1;
            }
        }
        return maxId;
    }

    public void updateDepartmentInternal(long oldId, long newId, String name, long power) throws Exception{
        var oldDepartment = departments.stream()
                .filter(department1 -> department1.getId() == oldId).findFirst();
        var newIdDepartment = departments.stream()
                .filter(department1 -> department1.getId() == newId).findFirst();
        if(oldDepartment.isEmpty())
            throw new Exception("No department with id " + oldId);
        if(oldId != newId) {
            if(newIdDepartment.isPresent())
                throw new Exception("Department with id " + newId + " already exists");
        }
        var department = oldDepartment.get();
        department.setId(newId);
        department.setName(name);
        department.setPower(power);
    }

    public void deleteDepartmentInternal(long departmentId) throws Exception
    {
        employees.removeIf(employee -> employee.getDepartmentId() == departmentId);
        if(!departments.removeIf(department -> department.getId() == departmentId)){
            throw new Exception("No department with id : " + departmentId + " found");
        }
    }

    public Department getDepartmentInd(int index) throws Exception
    {
        if(index > departments.size()){
            throw new Exception("Index out of departments array bounds");
        }
        return departments.get(index);
    }


    public int countDepartments()
    {
        return departments.size();
    }

    public void addEmployeeInternal(long id, String name, String surname, long salary, String position, long departmentId) throws Exception
    {
        var department = departments.stream()
                .filter(department1 -> department1.getId() == departmentId).findFirst();
        var employee = employees.stream()
                .filter(employee1 -> employee1.getId() == id).findFirst();
        if(department.isEmpty()){
            throw new Exception("No department with id " + departmentId);
        }
        if(employee.isPresent()){
            throw new Exception("Employee with id = " + id + " already exists");
        }
        var newEmployee = new Employee(id, name,surname,salary,position,departmentId);
        department.get().addEmployee(newEmployee);
        employees.add(newEmployee);
    }

    public long getNextEmployeeId(){
        long maxId = -1;
        for(var employee : employees){
            if(employee.getId() >= maxId){
                maxId = employee.getId() + 1;
            }
        }
        return maxId;
    }


    public Employee getEmployeeInternal(long id) throws Exception
    {
        var employee = employees.stream()
                .filter(employee1 -> employee1.getId() == id).findFirst();
        if(employee.isEmpty())
            throw new Exception("No employee with id = " + id);
        else
            return employee.get();
    }

    public void updateEmployeeInternal(long oldId, long newId, String name, String surname, long salary, String position, long departmentId) throws Exception {

        var oldEmployee = employees.stream()
                .filter(employee1 -> employee1.getId() == oldId).findFirst();

        var newEmployee = employees.stream()
                .filter(employee1 -> employee1.getId() == newId).findFirst();
        if(oldEmployee.isEmpty())
            throw new Exception("No employee with id " + oldId);
        if(oldId != newId) {
            if(newEmployee.isPresent())
                throw new Exception("Employee with id " + newId + " already exists");
        }
        var employee = oldEmployee.get();
        employee.setId(newId);
        employee.setName(name);
        employee.setSurname(surname);
        employee.setSalary(salary);
        employee.setPosition(position);
        employee.setDepartmentId(departmentId);
    }

    public void deleteEmployeeInternal(long employeeId) throws Exception
    {
        var optionalEmployee = employees.stream()
                .filter(employee1 -> employee1.getId() == employeeId).findFirst();
        if(optionalEmployee.isEmpty())
            throw new Exception("No employee with id " + employeeId + " found");
        else{
            var employee = optionalEmployee.get();
            departments.get((int) employee.getDepartmentId()).deleteEmployee(employee);
            employees.remove(employee);
        }
    }

    public Employee getEmployeeInd(int index) throws Exception
    {
        if(index > employees.size()){
            throw new Exception("Index out of employees array bounds");
        }
        return employees.get(index);
    }

    public int countEmployees()
    {
        return employees.size();
    }

}
