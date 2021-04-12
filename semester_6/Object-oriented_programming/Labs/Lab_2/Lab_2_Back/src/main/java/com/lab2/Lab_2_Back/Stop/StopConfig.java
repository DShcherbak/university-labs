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
                    new Stop(0L, "Либідська"),
                    new Stop(1L,"Палац Україна"),
                    new Stop(2L,"Олімпійська"),
                    new Stop(3L,"Площа Льва Толстого"),
                    new Stop(4L,"Майдан Незалежності"),
                    new Stop(5L,"Поштова площа"),
                    new Stop(6L,"Контрактова площа"),
                    new Stop(7L,"Тараса Шевченка"),
                    new Stop(8L,"Почайна"),
                    new Stop(9L,"Оболонь"),
            };
            //repository.saveAll(List.of(stops));
        };
    }
}
