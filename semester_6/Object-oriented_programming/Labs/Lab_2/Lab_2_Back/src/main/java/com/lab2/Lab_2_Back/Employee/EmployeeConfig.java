package com.lab2.Lab_2_Back.Employee;

import org.springframework.boot.CommandLineRunner;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.List;

@Configuration
public class EmployeeConfig {

    @Bean
    CommandLineRunner employeeCommandLineRunner(EmployeeRepository repository){
        return args -> {
            Employee[] employee = {
                    new Employee("Денис", "Щербак", 1L),
                    new Employee("Іван", "Рамик", 2L),
                    new Employee("Василина", "Борисюк", 3L)};
            repository.saveAll(List.of(employee));
        };
    }
}

