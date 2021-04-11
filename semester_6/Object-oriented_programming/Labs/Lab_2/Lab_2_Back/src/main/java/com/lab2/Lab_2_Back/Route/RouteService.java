package com.lab2.Lab_2_Back.Route;

import com.lab2.Lab_2_Back.Stop.Stop;
import com.lab2.Lab_2_Back.Stop.StopRepository;
import org.springframework.stereotype.Component;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

@Service
public class RouteService {

    private final RouteRepository repository;

    public RouteService(RouteRepository repository){
        this.repository = repository;
    }

    public List<Route> GetRoutes(){
        return repository.findAll();
    }

    public Route GetRouteById(Long routeId){
        Optional<Route> route= repository.findById(routeId);
        if(route.isEmpty()){
            throw new IllegalStateException("No route with id = " + routeId);
        }
        return route.get();
    }

    public void addNewRoute(Route route){
        var routeById = repository.findRouteById(route.getId());
        if(routeById.isPresent()){
            throw new IllegalStateException("Route with id = " + route.getId() + " already exists");
        }
        var routeByRouteNumber = repository.findRouteByRouteNumber(route.getRouteNumber());
        if(routeByRouteNumber.isPresent()){
            throw new IllegalStateException("Route with Number = " + route.getRouteNumber() + " already exists");
        }
        repository.save(route);
    }

    public void deleteRoute(Long routeId){
        if(repository.existsById(routeId)){
            repository.deleteById(routeId);
        } else {
            throw new IllegalStateException("Stop with id = " + routeId + " doesn't exist.");
        }
    }

    public void updateRoute(Long routeId, Route newRoute){
        Route route = repository.findById(routeId).orElseThrow(() -> new IllegalStateException(
                "Route with id = " + routeId + " doesn't exist"
        ));
        Optional<Route> routeByRouteNumber = repository.findRouteByRouteNumber(newRoute.getRouteNumber());
        if(routeByRouteNumber.isPresent()) {
            throw new IllegalStateException(
                    "Route with number = " + routeId + " already exists"
            );
        }
        if(newRoute.getRouteNumber() != null){
            if(newRoute.getRouteNumber() < 0) {
                throw new IllegalStateException(
                        "Route number must be > 0"
                );
            } else if (!route.getRouteNumber().equals(newRoute.getRouteNumber())) {
                route.setRouteNumber(newRoute.getRouteNumber());
            }
        }

        if(newRoute.getStops() != null){
            route.setStops(newRoute.getStops());
        }

        try{
            route.setStartTime(newRoute.getStartTime());
        }catch(Exception ex){
            throw new IllegalStateException(
                    "Incorrect time format : " + newRoute.getStartTime()
            );
        }

        repository.save(route);

    }
}
