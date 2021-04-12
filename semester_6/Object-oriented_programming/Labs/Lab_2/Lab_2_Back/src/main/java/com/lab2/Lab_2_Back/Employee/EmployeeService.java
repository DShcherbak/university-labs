package com.lab2.Lab_2_Back.Employee;

import com.lab2.Lab_2_Back.Route.RouteRepository;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class EmployeeService {

    private final RouteRepository routeRepository;
    private final EmployeeRepository repository;

    public EmployeeService(RouteRepository routeRepository, EmployeeRepository repository){
        this.routeRepository = routeRepository;
        this.repository = repository;
    }

    public List<Employee> GetEmployees(){
        return repository.findAll();
    }

    public Employee GetEmployeeById(Long employeeId){
        Optional<Employee> employee= repository.findById(employeeId);
        if(employee.isEmpty()){
            throw new IllegalStateException("No employee with id = " + employeeId);
        }
        return employee.get();
    }

    public void addNewEmployee(Employee employee){
        var employeeById = repository.findEmployeeById(employee.getId());
        if(employeeById.isPresent()){
            throw new IllegalStateException("Employee with id = " + employee.getId() + " already exists");
        }
        var routeByNumber = routeRepository.findRouteByRouteNumber(employee.getRouteId());
        if(routeByNumber.isEmpty()){
            throw new IllegalStateException("No route with number = " + employee.getRouteId());
        }
        employee.setRouteId(routeByNumber.get().getId());
        repository.save(employee);
    }

    public void deleteEmployee(Long employeeId){
        if(repository.existsById(employeeId)){
            repository.deleteById(employeeId);
        } else {
            throw new IllegalStateException("Stop with id = " + employeeId + " doesn't exist.");
        }
    }

    public void updateEmployee(Long employeeId, Employee newEmployee){
        Employee employee = repository.findById(employeeId).orElseThrow(() -> new IllegalStateException(
                "Employee with id = " + employeeId + " doesn't exist"
        ));
        if(newEmployee.getRouteId() != null && newEmployee.getRouteId() > 0){
            var rn = newEmployee.getRouteId();
            var routeByNumber = routeRepository.findRouteByRouteNumber(rn);
            if(routeByNumber.isEmpty()){
                throw new IllegalStateException("No route with number = " + employee.getRouteId());
            } else {
                employee.setRouteId(routeByNumber.get().getId());
            }
        }

        if(newEmployee.getName() != null && newEmployee.getName().length() > 0){
            employee.setName(newEmployee.getName());
        }
        if(newEmployee.getSurname() != null && newEmployee.getSurname().length() > 0){
            employee.setSurname(newEmployee.getSurname());
        }
        repository.save(employee);
    }
}
