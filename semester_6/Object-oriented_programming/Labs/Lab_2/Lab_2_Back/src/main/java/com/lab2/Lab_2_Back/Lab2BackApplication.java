package com.lab2.Lab_2_Back;

import com.lab2.Lab_2_Back.Route.Route;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@SpringBootApplication
public class Lab2BackApplication {

	public static void main(String[] args) {
		SpringApplication.run(Lab2BackApplication.class, args);
	}

}
