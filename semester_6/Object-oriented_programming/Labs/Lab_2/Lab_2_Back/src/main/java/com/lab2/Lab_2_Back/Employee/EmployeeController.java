package com.lab2.Lab_2_Back.Employee;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@CrossOrigin(origins = "http://localhost:3000")
@RequestMapping(path = "api/employees")
public class EmployeeController {

    private final EmployeeService service;

    @Autowired
    public EmployeeController(EmployeeService service){
        this.service = service;
    }

    @GetMapping
    public List<Employee> GetEmployees(){
        return service.GetEmployees();
    }

    @GetMapping(path="{employeeId}")
    public Employee GetEmployeeById(@PathVariable("employeeId") Long employeeId){
        return service.GetEmployeeById(employeeId);
    }

    @PostMapping
    public void registerNewEmployee(@RequestBody Employee employee){
        service.addNewEmployee(employee);
    }

    @DeleteMapping(path="{employeeId}")
    public void deleteEmployee(@PathVariable("employeeId") Long employeeId){
        service.deleteEmployee(employeeId);
    }

    @PutMapping(path="{employeeId}")
    public void updateEmployee(
            @PathVariable("employeeId") Long employeeId,
            @RequestBody Employee employee){
        service.updateEmployee(employeeId, employee);
    }
}
