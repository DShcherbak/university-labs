package com.lab2.Lab_2_Back.Employee;

import com.lab2.Lab_2_Back.Employee.Employee;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

import java.util.Optional;

@Repository
public interface EmployeeRepository extends JpaRepository<Employee, Long>{

    @Query("Select r from Employee r where r.id = ?1")
    Optional<Employee> findEmployeeById(Long id);



}
