package com.lab2.Lab_2_Back.Employee;

import javax.persistence.*;

@Entity
@Table
public class Employee {
    @Id
    @SequenceGenerator(
            name = "employees_sequence",
            sequenceName  = "employees_sequence",
            allocationSize = 1
    )
    @GeneratedValue(
            strategy = GenerationType.SEQUENCE,
            generator = "employees_sequence"
    )
    private Long id;
    private String name;
    private String surname;
    private Long routeNumber;

    public Employee() {
    }

    public Employee(String name, String surname, Long routeNumber) {
        this.name = name;
        this.surname = surname;
        this.routeNumber = routeNumber;
    }

    public Employee(Long id, String name, String surname, Long routeNumber) {
        this.id = id;
        this.name = name;
        this.surname = surname;
        this.routeNumber = routeNumber;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSurname() {
        return surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public Long getRouteNumber() {
        return routeNumber;
    }

    public void setRouteNumber(Long routeNumber) {
        this.routeNumber = routeNumber;
    }

    @Override
    public String toString() {
        return "Employee{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", surname='" + surname + '\'' +
                ", routeNumber=" + routeNumber +
                '}';
    }
}
