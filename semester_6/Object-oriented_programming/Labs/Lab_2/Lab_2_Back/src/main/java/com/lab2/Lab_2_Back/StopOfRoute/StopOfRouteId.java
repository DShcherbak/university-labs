package com.lab2.Lab_2_Back.StopOfRoute;

import javax.persistence.Column;
import javax.persistence.Embeddable;
import java.io.Serializable;
import java.util.Objects;

@Embeddable
class StopOfRouteId implements Serializable {

    @Column(name = "id")
    Long routeId;

    @Column(name = "id")
    Long stopId;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        StopOfRouteId that = (StopOfRouteId) o;
        return Objects.equals(routeId, that.routeId) && Objects.equals(stopId, that.stopId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(routeId, stopId);
    }

    // standard constructors, getters, and setters
    // hashcode and equals implementation
}