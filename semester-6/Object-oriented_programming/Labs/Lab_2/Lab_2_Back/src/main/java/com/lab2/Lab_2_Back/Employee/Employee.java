package com.lab2.Lab_2_Back.Employee;

import javax.persistence.*;
import java.util.Objects;

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
    private Long routeId;

    public Employee() {
    }

    public Employee(String name, String surname, Long routeId) {
        this.name = name;
        this.surname = surname;
        this.routeId = routeId;
    }

    public Employee(Long id, String name, String surname, Long routeId) {
        this.id = id;
        this.name = name;
        this.surname = surname;
        this.routeId = routeId;
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

    public Long getRouteId() {
        return routeId;
    }

    public void setRouteId(Long routeNumber) {
        this.routeId = routeNumber;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Employee employee = (Employee) o;
        return Objects.equals(id, employee.id) && Objects.equals(name, employee.name) && Objects.equals(surname, employee.surname) && Objects.equals(routeId, employee.routeId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, name, surname, routeId);
    }

    @Override
    public String toString() {
        return "Employee{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", surname='" + surname + '\'' +
                ", routeId=" + routeId +
                '}';
    }
}
