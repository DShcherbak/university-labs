package com.lab2.Lab_2_Back.Route;

import com.lab2.Lab_2_Back.ListConverter;

import javax.persistence.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
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
    private java.sql.Timestamp startTime;
    private java.sql.Timestamp endTime;
    private Long interval;
    private Long routeType;

    @Transient
    private final SimpleDateFormat TIME_FORMAT = new SimpleDateFormat("HH:mm");

    private java.sql.Timestamp parseTimestamp(String timestamp) {
        try {
            return new java.sql.Timestamp(TIME_FORMAT.parse(timestamp).getTime());
        } catch (ParseException e) {
            throw new IllegalStateException(e);
        }
    }

    public Route() {
    }

    public Route(Long id, Long routeNumber, List<Long> stopList, java.sql.Timestamp startTime, java.sql.Timestamp endTime, Long interval, Long routeType) {
        this.id = id;
        this.routeNumber = routeNumber;
        this.stops = stopList;
        this.startTime = startTime;
        this.endTime = endTime;
        this.interval = interval;
        this.routeType = routeType;
    }

    public Route(Long routeNumber,  List<Long> stopList, java.sql.Timestamp startTime, java.sql.Timestamp endTime, Long interval, Long routeType) {
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

    public java.sql.Timestamp getStartTime() {
        return startTime;
    }

    public void setStartTime(java.sql.Timestamp startTime) {
        Calendar cal = Calendar.getInstance();
        cal.setTime(startTime);
        cal.add(Calendar.HOUR, 3);
        this.startTime = new java.sql.Timestamp(cal.getTime().getTime());
    }

    public void setStartTime(String startTime) {
        this.startTime = parseTimestamp(startTime);
    }

    public java.sql.Timestamp getEndTime() {
        return endTime;
    }

    public void setEndTime(java.sql.Timestamp endTime) {
        Calendar cal = Calendar.getInstance();
        cal.setTime(endTime);
        cal.add(Calendar.HOUR, 3);
        this.startTime = new java.sql.Timestamp(cal.getTime().getTime());
    }

    public void setEndTime(String endTime) {
        this.endTime = parseTimestamp(endTime);
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
