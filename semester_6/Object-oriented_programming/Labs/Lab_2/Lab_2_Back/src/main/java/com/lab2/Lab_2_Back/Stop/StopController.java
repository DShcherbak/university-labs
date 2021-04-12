package com.lab2.Lab_2_Back.Stop;

import com.lab2.Lab_2_Back.Route.Route;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@CrossOrigin(origins = "http://localhost:3000")
@RequestMapping(path = "api/stops")
public class StopController {

    private final StopService stopService;

    @Autowired
    public StopController(StopService stopService){
        this.stopService = stopService;
    }

    @GetMapping
    public List<Stop> GetStops(){
        return stopService.GetStops();
    }

    @GetMapping(path="{stopId}")
    public Stop GetStop(@PathVariable("stopId") Long stopId){
        return stopService.GetStopById(stopId);
    }

    @PostMapping
    public void registerNewStop(@RequestBody Stop stop){
        stopService.addNewStop(stop);
    }

    @DeleteMapping(path="{stopId}")
    public void deleteStop(@PathVariable("stopId") Long stopId){
        stopService.deleteStop(stopId);
    }

    @PutMapping(path={"{stopId}"})
    public void updateStop(
            @PathVariable("stopId") Long stopId,
            @RequestBody Stop stop){
        stopService.updateStop(stopId, stop);
    }
}
