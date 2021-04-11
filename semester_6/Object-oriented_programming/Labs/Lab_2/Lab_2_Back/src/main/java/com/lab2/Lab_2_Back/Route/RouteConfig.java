package com.lab2.Lab_2_Back.Route;

import org.springframework.boot.CommandLineRunner;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import com.lab2.Lab_2_Back.Route.Route;
import com.lab2.Lab_2_Back.Route.RouteRepository;

import java.util.List;
@Configuration
public class RouteConfig {

    @Bean
    CommandLineRunner routeCommandLineRunner(RouteRepository repository){
        return args -> {
            Route[] routes = {
                    new Route(1L,1L,new ArrayList<Long>(Arrays.asList(1L,2L,3L,4L,5L)), "06:40", "23:30", 10L, 1L ),
                    new Route(2L,2L,new ArrayList<Long>(Arrays.asList(5L,4L,3L,2L,1L)), "06:40", "23:30", 10L, 1L ),
                    new Route(3L,20L,new ArrayList<Long>(Arrays.asList(1L,3L,5L, 7L)), "06:55", "23:40", 15L, 2L ),
                    new Route(4L,21L,new ArrayList<Long>(Arrays.asList(7L, 5L, 3L, 1L)), "06:55", "23:40", 15L, 2L ),
            };


            repository.saveAll(List.of(routes));
        };
    }
}

