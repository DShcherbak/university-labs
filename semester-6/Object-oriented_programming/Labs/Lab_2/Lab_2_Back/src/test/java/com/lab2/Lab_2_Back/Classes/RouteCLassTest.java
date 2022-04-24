package com.lab2.Lab_2_Back.Classes;

import com.lab2.Lab_2_Back.Route.Route;
import org.junit.jupiter.api.Test;

import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Calendar;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

class RouteCLassTest {

    Long[] ids = new Long[]{1L, 2L};
    Long[] numbers = new Long[]{212L, 220L};
    List<Long> stops0 =
            new ArrayList<Long>(Arrays.asList(1L, 3L, 5L, 7L));
    List<Long> stops1 =
            new ArrayList<Long>(Arrays.asList(7L, 5L, 3L, 1L));
    List<Long> times0 =
            new ArrayList<Long>(Arrays.asList(1L, 3L, 5L));
    List<Long> times1 =
            new ArrayList<Long>(Arrays.asList(5L, 3L, 1L));
    java.sql.Timestamp[] times = new Timestamp[]{new java.sql.Timestamp((6*60+40) * 60000), new java.sql.Timestamp((23*60+30) * 60000)};
    Long[] intervals = new Long[]{1L, 2L};
    Long[] routeTypes = new Long[]{1L, 2L};




    @Test
    void testEmptyGetSet() {
        Route route = new Route();
        route.setId(ids[0]);
        route.setRouteNumber(numbers[0]);
        route.setStops(stops0);
        route.setTimetable(times0);
        route.setStartTime(times[0]);
        route.setEndTime(times[0]);
        route.setInterval(intervals[0]);
        route.setRouteType(routeTypes[0]);
        assertEquals(ids[0], route.getId());
        assertEquals(numbers[0], route.getRouteNumber());
        assertEquals(stops0, route.getStops());
        assertEquals(times0, route.getTimetable());
        assertEquals(times[0], route.getStartTime());
        assertEquals(times[0], route.getEndTime());
        assertEquals(intervals[0], route.getInterval());
        assertEquals(routeTypes[0], route.getRouteType());
        assertEquals(3L, route.getGPT());
        assertEquals(new SimpleDateFormat("HH:mm"), route.getTIME_FORMAT());
    }




    @Test
    void testToString() {
        Route route = new Route(ids[0], numbers[0], stops0, times0, times[0], times[0], intervals[0], routeTypes[0]);
        assertEquals(route.toString(), "Route{" +
                "id=" + ids[0] +
                ", routeNumber=" + numbers[0] +
                ", stops=" + stops0 +
                ", startTime=" + times[0] +
                ", endTime=" + times[0] +
                ", interval=" + intervals[0] +
                ", routeType=" + routeTypes[0] +
                ", timetable=" + times0 +
                ", TIME_FORMAT=" + new SimpleDateFormat("HH:mm") +
                '}');
    }


    @Test
    void dateTimeTest(){
        Route route = new Route(ids[0], numbers[0], stops0, times0, times[0], times[0], intervals[0], routeTypes[0]);
        Calendar cal = Calendar.getInstance();
        cal.setTime(times[0]);
        cal.add(Calendar.HOUR, route.getGPT());
        route.setLocalStartTime(times[0]);
        assertEquals(route.getStartTime(), new java.sql.Timestamp(cal.getTime().getTime()));
        route.setLocalEndTime(times[0]);
        assertEquals(route.getStartTime(), new java.sql.Timestamp(cal.getTime().getTime()));

        cal.add(Calendar.HOUR, -2*route.getGPT());
        route.setStartTime("06:40");
        route.setEndTime("23:30");
        assertEquals(route.getStartTime(), new java.sql.Timestamp(cal.getTime().getTime()));
        cal.setTime(times[1]);
        cal.add(Calendar.HOUR, -1*route.getGPT());
        assertEquals(route.getEndTime(), new java.sql.Timestamp(cal.getTime().getTime()));
    }
    

    @Test
    void testEquals() {
        Route r1 = new Route();
        r1.setId(ids[0]);
        r1.setRouteNumber(numbers[0]);
        r1.setStops(stops0);
        r1.setTimetable(times0);
        r1.setStartTime(times[0]);
        r1.setEndTime(times[0]);
        r1.setInterval(intervals[0]);
        r1.setRouteType(routeTypes[0]);

       Route r2 = new Route(ids[0], numbers[0], stops0, times0, times[0], times[0], intervals[0], routeTypes[0]);
       Route r3 = new Route(numbers[1], stops1, times1, times[1], times[1], intervals[1], routeTypes[1]);
       r3.setId(ids[1]); 

       
        assertEquals(r1, r2);
        assertNotEquals(r1, r3);
        assertNotEquals(r2, r3);
        r2.setId(ids[1]);
        r2.setRouteNumber(numbers[1]);
        r2.setStops(stops1);
        r2.setTimetable(times1);
        r2.setStartTime(times[1]);
        r2.setEndTime(times[1]);
        r2.setInterval(intervals[1]);
        r2.setRouteType(routeTypes[1]);
        assertNotEquals(r1, r2);
        assertNotEquals(r1, r3);
        assertEquals(r2, r3);

    }

    @Test
    void testHashCode() {
        Route r1 = new Route();
        r1.setId(ids[0]);
        r1.setRouteNumber(numbers[0]);
        r1.setStops(stops0);
        r1.setTimetable(times0);
        r1.setStartTime(times[0]);

        r1.setEndTime(times[0]);
        r1.setInterval(intervals[0]);
        r1.setRouteType(routeTypes[0]);

        Route r2 = new Route(ids[0], numbers[0], stops0, times0, times[0], times[0], intervals[0], routeTypes[0]);
        Route r3 = new Route(numbers[1], stops1, times1, times[1], times[1], intervals[1], routeTypes[1]);
        r3.setId(ids[1]);

        assertEquals(r1.hashCode(), r2.hashCode());
        assertNotEquals(r1.hashCode(), r3.hashCode());
        assertNotEquals(r2.hashCode(), r3.hashCode());
        r2.setId(ids[1]);
        r2.setRouteNumber(numbers[1]);
        r2.setStops(stops1);
        r2.setTimetable(times1);
        r2.setStartTime(times[1]);
        r2.setEndTime(times[1]);
        r2.setInterval(intervals[1]);
        r2.setRouteType(routeTypes[1]);
        assertNotEquals(r1.hashCode(), r2.hashCode());
        assertNotEquals(r1.hashCode(), r3.hashCode());
        assertEquals(r2.hashCode(), r3.hashCode());

    }


}
