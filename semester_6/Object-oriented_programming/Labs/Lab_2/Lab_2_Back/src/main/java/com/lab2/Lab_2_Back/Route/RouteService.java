package com.lab2.Lab_2_Back.Route;


import org.springframework.stereotype.Service;

import java.util.Comparator;
import java.util.List;
import java.util.Optional;

@Service
public class RouteService {

    private final RouteRepository repository;

    public RouteService(RouteRepository repository){
        this.repository = repository;
    }

    public List<Route> GetRoutes(){
        var list = repository.findAll();
        list.sort(new Comparator<Route>() {
            @Override
            public int compare(Route o1, Route o2) {
                return o1.getRouteNumber() > o2.getRouteNumber() ? 1 : -1;
            }
        });
        return list;
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
        if(routeById.isPresent()) {
            throw new IllegalStateException("Route with id = " + route.getId() + " already exists");
        }
        var routeByRouteNumber = repository.findRouteByRouteNumber(route.getRouteNumber());
        if(routeByRouteNumber.isPresent()){
            throw new IllegalStateException("Route with Number = " + route.getRouteNumber() + " already exists");
        }
        route.setLocalStartTime(route.getStartTime()); //Sets to local time (GPT + 3)
        route.setLocalEndTime(route.getEndTime()); //Sets to local time (GPT + 3)
        repository.save(route);
    }

    public void deleteRoute(Long routeId){
        if(repository.existsById(routeId)){
            repository.deleteById(routeId);
        } else {
            throw new IllegalStateException("Stop with id = " + routeId + " doesn't exist.");
        }
    }

    public void updateRoute(Long routeId, Long oldNumber, Route newRoute){
        Route route = repository.findById(routeId).orElseThrow(() -> new IllegalStateException(
                "Route with id = " + routeId + " doesn't exist"
        ));
        if(!oldNumber.equals(newRoute.getRouteNumber())){
            Optional<Route> routeByRouteNumber = repository.findRouteByRouteNumber(newRoute.getRouteNumber());
            if(routeByRouteNumber.isPresent()) {
                throw new IllegalStateException(
                        "Route with number = " + routeId + " already exists"
                );
            }
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

        if(newRoute.getTimetable() != null){
            route.setTimetable(newRoute.getTimetable());
        }

        try{
            route.setLocalStartTime(newRoute.getStartTime());
        }catch(Exception ex){
            throw new IllegalStateException(
                    "Incorrect time format : " + newRoute.getStartTime()
            );
        }

        try{
            route.setLocalEndTime(newRoute.getEndTime());
        }catch(Exception ex){
            throw new IllegalStateException(
                    "Incorrect time format : " + newRoute.getEndTime()
            );
        }

        if(newRoute.getInterval() < 0){
            throw new IllegalStateException(
                    "Interval sholud be positive " + newRoute.getInterval()
            );
        } else {
            route.setInterval(newRoute.getInterval());
        }

        if(newRoute.getRouteType() < 0){
            throw new IllegalStateException(
                    "Route type sholud be positive " + newRoute.getRouteType()
            );
        } else {
            route.setRouteType(newRoute.getRouteType());
        }

        repository.save(route);
    }
}
