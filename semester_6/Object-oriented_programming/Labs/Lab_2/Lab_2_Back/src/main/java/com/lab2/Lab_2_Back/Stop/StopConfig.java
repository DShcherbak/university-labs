package com.lab2.Lab_2_Back.Stop;

import org.springframework.boot.CommandLineRunner;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.List;

@Configuration
public class StopConfig {

    @Bean
    CommandLineRunner stopCommandLineRunner(StopRepository repository){
        return args -> {
            Stop[] stops = {
                    new Stop("Либідська"),
                    new Stop("Палац Україна"),
                    new Stop("Олімпійська"),
                    new Stop("Площа Льва Толстого"),
                    new Stop("Майдан Незалежності"),
                    new Stop("Поштова площа"),
                    new Stop("Контрактова площа"),
            };


            repository.saveAll(List.of(stops));
        };
    }
}
