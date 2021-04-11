package com.lab2.Lab_2_Back.StopOfRoute;

import com.lab2.Lab_2_Back.Route.Route;
import com.lab2.Lab_2_Back.Stop.Stop;

import javax.persistence.*;

@Entity
public class StopOfRoute {

    @EmbeddedId
    StopOfRouteId id;

    @ManyToOne(fetch = FetchType.LAZY)
    @MapsId("routeId")
    @JoinColumn(name = "routeId")
    Route route;

    @OneToOne
    @MapsId("stopId")
    @JoinColumn(name = "stopId")
    Stop stop;

    int numberInRoute;

    // standard constructors, getters, and setters
}
