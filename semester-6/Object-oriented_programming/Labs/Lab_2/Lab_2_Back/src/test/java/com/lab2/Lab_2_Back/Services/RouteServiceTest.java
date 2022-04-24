package com.lab2.Lab_2_Back.Services;


import com.lab2.Lab_2_Back.Route.Route;
import com.lab2.Lab_2_Back.Route.RouteRepository;
import com.lab2.Lab_2_Back.Route.RouteService;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.doReturn;


@SpringBootTest
public class RouteServiceTest {

    @Autowired
    private RouteService service;

    @MockBean
    private RouteRepository repository;

    @Test
    void testGetAll() {
        Route route = new Route();
        route.setId(87L);
        ArrayList<Route> routeList = new ArrayList<>();
        routeList.add(route);
        doReturn(routeList).when(repository).findAll();
        List<Route> returnedWidget = service.GetRoutes();
        assertEquals(returnedWidget.size(), 1);
        assertEquals(returnedWidget.get(0).getId(), 87L);
    }

    @Test
    void testById(){
        Route route = new Route();
        route.setId(77L);
        doReturn(Optional.of(route)).when(repository).findById(0L);
        Route foundRoute = service.GetRouteById(0L);
        assertEquals(route, foundRoute);
    }

    @Test
    void testUpdate() {
        Route route = new Route();
        route.setId(67L);
        route.setRouteNumber(212L);
        ArrayList<Route> routeList = new ArrayList<>();
        routeList.add(route);
        doReturn(routeList).when(repository).findAll();
        doReturn(Optional.of(route)).when(repository).findById(67L);
        Route newRoute = new Route();
        newRoute.setRouteNumber(145L);
        newRoute.setId(1L);
        newRoute.setStops(new ArrayList<Long>(){});
        newRoute.setTimetable(new ArrayList<Long>(){});
        newRoute.setStartTime(new java.sql.Timestamp(0));
        newRoute.setEndTime(new java.sql.Timestamp(0));
        newRoute.setInterval(10L);
        newRoute.setRouteType(3L);
        service.updateRoute(67L, 212L, newRoute);
        List<Route> returnedWidget = service.GetRoutes();
        assertEquals(returnedWidget.get(0).getRouteNumber(), 145L);
        assertEquals(returnedWidget.get(0).getInterval(), newRoute.getInterval());
    }

    @Test
    void testNoUpdate() {
        Route route1 = new Route();
        route1.setId(67L);
        route1.setRouteNumber(212L);
        Route route2 = new Route();
        route2.setId(68L);
        route2.setRouteNumber(145L);
        ArrayList<Route> routeList = new ArrayList<>();
        routeList.add(route1);
        routeList.add(route2);
        doReturn(routeList).when(repository).findAll();
        doReturn(Optional.of(route1)).when(repository).findById(67L);
        doReturn(Optional.of(route2)).when(repository).findRouteByRouteNumber(145L);
        Route newRoute = new Route();
        newRoute.setRouteNumber(145L);
        newRoute.setId(1L);

        try{
            service.updateRoute(67L, 212L, newRoute);
        }catch (Exception ex){
            assertEquals(ex.getMessage(),"Route with number = 145 already exists");
        }
    }

    @Test
    void testAdd() {
        Route route = new Route();
        route.setId(57L);
        route.setRouteNumber(57L);
        ArrayList<Route> routeList = new ArrayList<>();
        routeList.add(route);
        doReturn(routeList).when(repository).findAll();

        Route route1 = new Route();
        route1.setId(67L);
        route1.setRouteNumber(212L);
        Route route2 = new Route();
        route2.setId(68L);
        route2.setRouteNumber(145L);
        service.addNewRoute(route1);
        service.addNewRoute(route2);
        List<Route> returnedWidget = service.GetRoutes();
        assertEquals(returnedWidget.get(0).getId(), 57L);
    }



    @Test
    void testNoDelete() {
        Route route = new Route();
        route.setId(37L);
        ArrayList<Route> routeList = new ArrayList<>();
        routeList.add(route);
        doReturn(routeList).when(repository).findAll();
        try{
            service.deleteRoute(1L);
        }catch (Exception ex){
            assertEquals(ex.getMessage(),"Route with id = 1 doesn't exist.");
        }
    }

    @Test
    void testNoAddByNumber() {
        Route route = new Route();
        route.setId(27L);
        route.setRouteNumber(64L);
        ArrayList<Route> routeList = new ArrayList<>();
        routeList.add(route);
        doReturn(routeList).when(repository).findAll();
        doReturn(Optional.of(route)).when(repository).findRouteByRouteNumber(64L);
        Route newRoute = new Route();
        newRoute.setId(17L);
        newRoute.setRouteNumber(64L);
        //routeByNumber.get().getId()
        try{
            service.addNewRoute(newRoute);
        }catch (Exception ex){
            assertEquals(ex.getMessage(),"Route with Number = 64 already exists");
        }
    }

    @Test
    void testNoAddById() {
        Route route = new Route();
        route.setId(27L);
        route.setRouteNumber(64L);
        ArrayList<Route> routeList = new ArrayList<>();
        routeList.add(route);
        doReturn(routeList).when(repository).findAll();
        doReturn(Optional.of(route)).when(repository).findRouteByRouteNumber(64L);
        Route newRoute = new Route();
        newRoute.setId(27L);
        newRoute.setRouteNumber(63L);
        //routeByNumber.get().getId()
        try{
            service.addNewRoute(newRoute);
        }catch (Exception ex){
            assertEquals(ex.getMessage(),"Route with id = 27 already exists");
        }
    }

    @Test
    void testDelete() {
        Route route = new Route();
        route.setId(17L);
        ArrayList<Route> routeList = new ArrayList<>();
        routeList.add(route);
        doReturn(routeList).when(repository).findAll();
        doReturn(true).when(repository).existsById(1L);
        service.deleteRoute(1L);
        List<Route> returnedWidget = service.GetRoutes();
        assertEquals(returnedWidget.get(0).getId(), 17L);
    }
}
