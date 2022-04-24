package com.lab2.Lab_2_Back.Stop;

import com.lab2.Lab_2_Back.Route.Route;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class StopService {

    private final StopRepository repository;

    public StopService(StopRepository repository){
        this.repository = repository;
    }

    public List<Stop> GetStops(){
        return repository.findAll();
    }

    public Stop GetStopById(Long stopId){
        Optional<Stop> stop= repository.findById(stopId);
        if(stop.isEmpty()){
            throw new IllegalStateException("No route with id = " + stopId);
        }
        return stop.get();
    }

    public void addNewStop(Stop stop) {
        var stopByName = repository.findStopByName(stop.getName()) ;
        if(stopByName.isPresent()){
            throw new IllegalStateException("Stop name is already taken!");
        } else {
            repository.save(stop);
        }
        System.out.println(stop);
    }

    public void deleteStop(Long stopId){
        if(repository.existsById(stopId)){
            repository.deleteById(stopId);
        } else {
            throw new IllegalStateException("Stop with id = " + stopId + " doesn't exist.");
        }
    }

    public void updateStop(Long stopId, Stop newStop){
        Stop stop = repository.findById(stopId).orElseThrow(() -> new IllegalStateException(
                "Stop with id = " + stopId + " doesn't exist"
        ));
        String name = newStop.getName();
        if(name != null && name.length() > 0 &&
        (!stop.getName().equals(name))){
            stop.setName(name);
        }
        repository.save(stop);
    }
}
