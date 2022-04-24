package com.lab2.Lab_2_Back.Route;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@CrossOrigin(origins = "http://localhost:3000")
@RequestMapping(path = "api/routes")
public class RouteController {

    private final RouteService routeService;

    @Autowired
    public RouteController(RouteService routeService){
        this.routeService = routeService;
    }

    @GetMapping
    public List<Route> GetRoutes(){
        return routeService.GetRoutes();
    }

    @GetMapping(path="{routeId}")
    public Route GetRouteById(@PathVariable("routeId") Long routeId){
        return routeService.GetRouteById(routeId);
    }

    @PostMapping
    public void registerNewRoute(@RequestBody Route route, @RequestHeader("Authorization") String authString){
        routeService.addNewRoute(route);
    }

    @DeleteMapping(path="{routeId}")
    public void deleteRoute(@PathVariable("routeId") Long routeId){
        routeService.deleteRoute(routeId);
    }

    @PutMapping(path="{routeId}/{oldNumber}")
    public void updateRoute(
            @PathVariable("routeId") Long routeId,
            @PathVariable("oldNumber") Long oldNumber,
            @RequestBody Route route){
        routeService.updateRoute(routeId, oldNumber, route);
    }
}
