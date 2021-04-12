package com.lab2.Lab_2_Back.Classes;

import com.lab2.Lab_2_Back.Employee.Employee;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

class EmployeeCLassTest {

    @Test
    void testEmptyGetSet() {
        Employee employee = new Employee();
        Long longTestValue = 55L;
        String testName = "Test name";
        String testSurname = "Test surname";
        Long routeId = 1L;
        employee.setId(longTestValue);
        employee.setName(testName);
        employee.setSurname(testSurname);
        employee.setRouteId(routeId);
        assertEquals(longTestValue, employee.getId());
        assertEquals(testName, employee.getName());
        assertEquals(testSurname, employee.getSurname());
        assertEquals(routeId, employee.getRouteId());
    }

    @Test
    void testToString() {
        Long longTestValue = 55L;
        String testName = "Test name";
        String testSurname = "Test surname";
        Long routeId = 1L;
        Employee employee = new Employee(longTestValue, testName, testSurname, routeId);
        assertEquals(longTestValue, employee.getId());
        assertEquals(testName, employee.getName());
        assertEquals(testSurname, employee.getSurname());
        assertEquals(routeId, employee.getRouteId());
        assertEquals(employee.toString(), "Employee{" +
                "id=" + longTestValue +
                ", name='" + testName + '\'' +
                ", surname='" + testSurname + '\'' +
                ", routeId=" + routeId  +
                '}');
    }

    @Test
    void testEquals() {
        Long[] ids = new Long[]{1L, 1L, 3L};
        String[] names = new String[]{"name1", "name1",  "name3"};
        String[] surnames = new String[]{"surname1", "surname1",  "surname3"};
        Long[] routeIds = new Long[]{1000L, 1000L, 30L};

        Employee e1 = new Employee();
        e1.setId(ids[0]);
        e1.setName(names[0]);
        e1.setSurname(surnames[0]);
        e1.setRouteId(routeIds[0]);

        Employee e2 = new Employee(names[1], surnames[1], routeIds[1]);
        e2.setId(ids[1]);

        Employee e3 = new Employee(ids[2], names[2], surnames[2], routeIds[2]);
        assertEquals(e1, e2);
        assertNotEquals(e1, e3);
        assertNotEquals(e2, e3);
        e2.setId(ids[2]);
        e2.setName(names[2]);
        e2.setSurname(surnames[2]);
        e2.setRouteId(routeIds[2]);
        assertNotEquals(e1, e2);
        assertNotEquals(e1, e3);
        assertEquals(e2, e3);

    }

    @Test
    void testHashCode() {
        Long[] ids = new Long[]{1L, 1L, 3L};
        String[] names = new String[]{"name1", "name1",  "name3"};
        String[] surnames = new String[]{"surname1", "surname1",  "surname3"};
        Long[] routeIds = new Long[]{1000L, 1000L, 30L};

        Employee e1 = new Employee();
        e1.setId(ids[0]);
        e1.setName(names[0]);
        e1.setSurname(surnames[0]);
        e1.setRouteId(routeIds[0]);

        Employee e2 = new Employee(names[1], surnames[1], routeIds[1]);
        e2.setId(ids[1]);

        Employee e3 = new Employee(ids[2], names[2], surnames[2], routeIds[2]);

        assertEquals(e1.hashCode(), e2.hashCode());
        assertNotEquals(e1.hashCode(), e3.hashCode());
        assertNotEquals(e2.hashCode(), e3.hashCode());
        e2.setId(ids[2]);
        e2.setName(names[2]);
        e2.setSurname(surnames[2]);
        e2.setRouteId(routeIds[2]);
        assertNotEquals(e1.hashCode(), e2.hashCode());
        assertNotEquals(e1.hashCode(), e3.hashCode());
        assertEquals(e2.hashCode(), e3.hashCode());

    }
}
