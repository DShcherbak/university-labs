package com.lab2.Lab_2_Back.Route;

import com.lab2.Lab_2_Back.ListConverter;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.List;

@Entity
@Table
public class Route {
    @Id
    @SequenceGenerator(
            name = "stops_sequence",
            sequenceName  = "stops_sequence",
            allocationSize = 1
    )
    @GeneratedValue(
            strategy = GenerationType.SEQUENCE,
            generator = "stops_sequence"
    )
    private Long id;
    private Long routeNumber;
    @Convert(converter = ListConverter.class)
    private List<Long> stops = new ArrayList<>();
    private String startTime;
    private String endTime;
    private Long interval;
    private Long routeType;

    public Route() {
    }

    public Route(Long id, Long routeNumber, List<Long> stopList, String startTime, String endTime, Long interval, Long routeType) {
        this.id = id;
        this.routeNumber = routeNumber;
        this.stops = stopList;
        this.startTime = startTime;
        this.endTime = endTime;
        this.interval = interval;
        this.routeType = routeType;
    }

    public Route(Long routeNumber,  List<Long> stopList, String startTime, String endTime, Long interval, Long routeType) {
        this.routeNumber = routeNumber;
        this.stops = stopList;
        this.startTime = startTime;
        this.endTime = endTime;
        this.interval = interval;
        this.routeType = routeType;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long routeId) {
        this.id = routeId;
    }

    public Long getRouteNumber() {
        return routeNumber;
    }

    public void setRouteNumber(Long routeNumber) {
        this.routeNumber = routeNumber;
    }

    public String getStartTime() {
        return startTime;
    }

    public void setStartTime(String startTime) {
        this.startTime = startTime;
    }

    public String getEndTime() {
        return endTime;
    }

    public void setEndTime(String endTime) {
        this.endTime = endTime;
    }

    public Long getInterval() {
        return interval;
    }

    public void setInterval(Long interval) {
        this.interval = interval;
    }

    public Long getRouteType() {
        return routeType;
    }

    public void setRouteType(Long routeType) {
        this.routeType = routeType;
    }

    public List<Long> getStops() {
        return stops;
    }

    public void setStops(List<Long> stopIdList) {
        this.stops = stopIdList;
    }

    private String listToString(List<Long> list){
        String result = "[";
        for(Long l : list) result = result.concat(String.valueOf(l)).concat(",");
        return result.substring(0, result.length()-1).concat("]");
    }

    @Override
    public String toString() {
        return "Route{" +
                "id=" + id +
                ", routeNumber=" + routeNumber +
                ", stopIdList=" + listToString(stops) +
                ", startTime='" + startTime + '\'' +
                ", endTime='" + endTime + '\'' +
                ", interval=" + interval +
                ", routeType=" + routeType +
                '}';
    }
}
