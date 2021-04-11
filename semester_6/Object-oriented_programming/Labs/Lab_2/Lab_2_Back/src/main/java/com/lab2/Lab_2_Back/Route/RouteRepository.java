package com.lab2.Lab_2_Back.Route;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

import java.util.Optional;

@Repository
public interface RouteRepository extends JpaRepository<Route, Long>{

    @Query("Select r from Route r where r.id = ?1")
    Optional<Route> findRouteById(Long id);

    @Query("Select r from Route r where r.routeNumber = ?1")
    Optional<Route> findRouteByRouteNumber(Long routeNumber);


}
