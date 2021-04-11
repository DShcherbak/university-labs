package com.lab2.Lab_2_Back.Stop;

import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class StopService {

    private final StopRepository stopRepository;

    public StopService(StopRepository repository){
        stopRepository = repository;
    }

    public List<Stop> GetStops(){
        return stopRepository.findAll();
    }

    public void addNewStop(Stop stop) {
        var stopByName = stopRepository.findStopByName(stop.getName()) ;
        if(stopByName.isPresent()){
            throw new IllegalStateException("Stop name is already taken!");
        } else {
            stopRepository.save(stop);
        }
        System.out.println(stop);
    }

    public void deleteStop(Long stopId){
        if(stopRepository.existsById(stopId)){
            stopRepository.deleteById(stopId);
        } else {
            throw new IllegalStateException("Stop with id = " + stopId + " doesn't exist.");
        }
    }

    public void updateStop(Long stopId, String name){
        Stop stop = stopRepository.findById(stopId).orElseThrow(() -> new IllegalStateException(
                "Stop with id = " + stopId + " doesn't exist"
        ));
        if(name != null && name.length() > 0 &&
        (!stop.getName().equals(name))){
            stop.setName(name);
        }
    }
}
