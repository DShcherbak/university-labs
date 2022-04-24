package com.lab2.Lab_2_Back.Stop;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

import java.util.Optional;

@Repository
public interface StopRepository extends JpaRepository<Stop, Long> {

    @Query("Select s from Stop s where s.name = ?1")
    Optional<Stop> findStopByName(String name);

}
