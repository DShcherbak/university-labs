package com.lab2.Lab_2_Back.Stop;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.Objects;

@Entity
@Table
public class Stop {
    @Id
    @SequenceGenerator(
            name = "stops_sequence",
            sequenceName  = "stops_sequence",
            allocationSize = 1
    )
    @GeneratedValue(
            strategy = GenerationType.SEQUENCE,
            generator = "stops_sequence"
    )
    private Long id;
    private String name;

    public Stop() {
    }

    public Stop(String name) {
        this.name = name;
    }

    public Stop(Long id, String name) {
        this.id = id;
        this.name = name;
    }

    @Override
    public String toString() {
        return "Stop{" +
                "id=" + id +
                ", name='" + name + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Stop stop = (Stop) o;
        return Objects.equals(id, stop.id) && Objects.equals(name, stop.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, name);
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
}
