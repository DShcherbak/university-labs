package com.lab2.Lab_2_Back.Route;

import com.lab2.Lab_2_Back.ListConverter;

import javax.persistence.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;
import java.util.Objects;

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
    @Convert(converter = ListConverter.class)
    private List<Long> timetable = new ArrayList<>();

    @Transient
    private final SimpleDateFormat TIME_FORMAT = new SimpleDateFormat("HH:mm");

    public int getGPT() {
        return GPT;
    }

    @Transient
    private final int GPT = 3;

    private java.sql.Timestamp parseTimestamp(String timestamp) {
        try {
            return new java.sql.Timestamp(TIME_FORMAT.parse(timestamp).getTime());
        } catch (ParseException e) {
            throw new IllegalStateException(e);
        }
    }

    public Route() {
    }

    public Route(Long id, Long routeNumber, List<Long> stopList, List<Long> timetable, java.sql.Timestamp startTime, java.sql.Timestamp endTime, Long interval, Long routeType) {
        this.id = id;
        this.routeNumber = routeNumber;
        this.stops = stopList;
        this.timetable = timetable;
        this.startTime = startTime;
        this.endTime = endTime;
        this.interval = interval;
        this.routeType = routeType;
    }

    public Route(Long routeNumber,  List<Long> stopList, List<Long> timetable, java.sql.Timestamp startTime, java.sql.Timestamp endTime, Long interval, Long routeType) {
        this.routeNumber = routeNumber;
        this.stops = stopList;
        this.timetable = timetable;
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

    public void setLocalStartTime(java.sql.Timestamp startTime) {
        Calendar cal = Calendar.getInstance();
        cal.setTime(startTime);
        cal.add(Calendar.HOUR, GPT);
        setStartTime(new java.sql.Timestamp(cal.getTime().getTime()));
    }

    public void setStartTime(java.sql.Timestamp startTime){
        this.startTime = startTime;
    }

    public void setStartTime(String startTime) {
        this.startTime = parseTimestamp(startTime);
    }

    public java.sql.Timestamp getEndTime() {
        return endTime;
    }

    public void setLocalEndTime(java.sql.Timestamp endTime) {
        Calendar cal = Calendar.getInstance();
        cal.setTime(endTime);
        cal.add(Calendar.HOUR, GPT);
        setEndTime(new java.sql.Timestamp(cal.getTime().getTime()));
    }

    public void setEndTime(java.sql.Timestamp endTime){
        this.endTime = endTime;
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
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Route route = (Route) o;
        return id.equals(route.id) && routeNumber.equals(route.routeNumber) && stops.equals(route.stops) && startTime.equals(route.startTime) && endTime.equals(route.endTime) && interval.equals(route.interval) && routeType.equals(route.routeType) && timetable.equals(route.timetable) && TIME_FORMAT.equals(route.TIME_FORMAT);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, routeNumber, stops, startTime, endTime, interval, routeType, timetable, TIME_FORMAT);
    }

    public List<Long> getTimetable() {
        return timetable;
    }

    public void setTimetable(List<Long> timetable) {
        this.timetable = timetable;
    }

    public SimpleDateFormat getTIME_FORMAT() {
        return TIME_FORMAT;
    }

    @Override
    public String toString() {
        return "Route{" +
                "id=" + id +
                ", routeNumber=" + routeNumber +
                ", stops=" + stops +
                ", startTime=" + startTime +
                ", endTime=" + endTime +
                ", interval=" + interval +
                ", routeType=" + routeType +
                ", timetable=" + timetable +
                ", TIME_FORMAT=" + TIME_FORMAT +
                '}';
    }
}
