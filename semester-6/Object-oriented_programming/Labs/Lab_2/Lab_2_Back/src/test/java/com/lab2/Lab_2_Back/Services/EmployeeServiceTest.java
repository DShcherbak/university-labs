package com.lab2.Lab_2_Back.Services;


import com.lab2.Lab_2_Back.Employee.Employee;
import com.lab2.Lab_2_Back.Employee.EmployeeRepository;
import com.lab2.Lab_2_Back.Employee.EmployeeService;
import com.lab2.Lab_2_Back.Route.Route;
import com.lab2.Lab_2_Back.Route.RouteRepository;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.doReturn;


@SpringBootTest
public class EmployeeServiceTest {

    @Autowired
    private EmployeeService service;

    @MockBean
    private EmployeeRepository repository;

    @MockBean
    private RouteRepository routeRepository;

    @Test
    void testGetAll() {
        Employee employee = new Employee(0L, "Денис", "Щербак", 3L);
        ArrayList<Employee> employeeList = new ArrayList<>();
        employeeList.add(employee);
        doReturn(employeeList).when(repository).findAll();
        List<Employee> returnedWidget = service.GetEmployees();
        assertEquals(returnedWidget.size(), 1);
    }

    @Test
    void testById(){
        Employee employee = new Employee(0L, "Денис", "Щербак", 3L);
        doReturn(Optional.of(employee)).when(repository).findById(0L);
        Employee foundEmployee = service.GetEmployeeById(0L);
        assertEquals(employee, foundEmployee);
    }

    @Test
    void testUpdate() {
        Employee employee = new Employee(1L, "Денис", "Щербак", 3L);
        ArrayList<Employee> employeeList = new ArrayList<>();
        employeeList.add(employee);
        doReturn(employeeList).when(repository).findAll();
        doReturn(Optional.of(employee)).when(repository).findById(1L);
        Route route = new Route();
        route.setId(3L);
        doReturn(Optional.of(route)).when(routeRepository).findRouteByRouteNumber(3L);
        service.updateEmployee(1L, new Employee(1L, "Денис-Олексій", "Щербак", 3L));
        List<Employee> returnedWidget = service.GetEmployees();
        assertEquals(returnedWidget.get(0).getName(), "Денис-Олексій");
    }

    @Test
    void testAdd() {
        Employee employee = new Employee(0L, "Денис", "Щербак", 3L);
        ArrayList<Employee> employeeList = new ArrayList<>();
        employeeList.add(employee);
        doReturn(employeeList).when(repository).findAll();
        Route route = new Route();
        route.setId(3L);
        doReturn(Optional.of(route)).when(routeRepository).findRouteByRouteNumber(3L);
        //routeByNumber.get().getId()
        service.addNewEmployee(new Employee(1L, "Денис", "Щербак", 3L));
        service.addNewEmployee(new Employee(1L, "Денис-Іван", "Щербак", 3L));
        List<Employee> returnedWidget = service.GetEmployees();
        assertEquals(returnedWidget.get(0).getName(), "Денис");
    }

    @Test
    void testNoUpdate() {
        Employee employee = new Employee(0L, "Денис", "Щербак", 3L);
        ArrayList<Employee> employeeList = new ArrayList<>();
        employeeList.add(employee);
        doReturn(employeeList).when(repository).findAll();

        //routeByNumber.get().getId()
        try{
            service.updateEmployee(1L, new Employee(1L, "Денис", "Щербак", 3L));
        }catch (Exception ex){
            assertEquals(ex.getMessage(),"Employee with id = 1 doesn't exist");
        }
    }

    @Test
    void testNoDelete() {
        Employee employee = new Employee(0L, "Денис", "Щербак", 3L);
        ArrayList<Employee> employeeList = new ArrayList<>();
        employeeList.add(employee);
        doReturn(employeeList).when(repository).findAll();

        try{
            service.deleteEmployee(1L);
        }catch (Exception ex){
            assertEquals(ex.getMessage(),"Employee with id = 1 doesn't exist.");
        }
    }

    @Test
    void testNoAdd() {
        Employee employee = new Employee(0L, "Денис", "Щербак", 3L);
        ArrayList<Employee> employeeList = new ArrayList<>();
        employeeList.add(employee);
        doReturn(employeeList).when(repository).findAll();

        //routeByNumber.get().getId()
        try{
            service.addNewEmployee(new Employee(1L, "Денис", "Щербак", 3L));
        }catch (Exception ex){
            assertEquals(ex.getMessage(),"No route with number = 3");
        }
    }

    @Test
    void testDelete() {
        Employee employee = new Employee(1L, "Денис", "Щербак", 3L);
        ArrayList<Employee> employeeList = new ArrayList<>();
        employeeList.add(employee);
        doReturn(employeeList).when(repository).findAll();
        doReturn(true).when(repository).existsById(1L);
        service.deleteEmployee(1L);
        List<Employee> returnedWidget = service.GetEmployees();
        assertEquals(returnedWidget.size(), 1);
    }
}
