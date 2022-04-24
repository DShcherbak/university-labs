package com.lab2.Lab_2_Back.Services;

import com.lab2.Lab_2_Back.Stop.Stop;
import com.lab2.Lab_2_Back.Stop.StopRepository;
import com.lab2.Lab_2_Back.Stop.StopService;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.doReturn;

@SpringBootTest
public class StopServiceTest {

    @Autowired
    private StopService service;


    @MockBean
    private StopRepository repository;

    @Test
    void testGetAll() {
        Stop stop = new Stop(0L, "Либідська");
        ArrayList<Stop> stopList = new ArrayList<>();
        stopList.add(stop);
        doReturn(stopList).when(repository).findAll();
        List<Stop> returnedWidget = service.GetStops();
        assertEquals(returnedWidget.size(), 1);
    }

    @Test
    void testById(){
        Stop stop = new Stop(0L, "Либідська");
        doReturn(Optional.of(stop)).when(repository).findById(0L);
        Stop foundStop = service.GetStopById(0L);
        assertEquals(stop, foundStop);
    }

    @Test
    void testUpdate() {
        Stop stop = new Stop(1L, "Либідська");
        ArrayList<Stop> stopList = new ArrayList<>();
        stopList.add(stop);
        doReturn(stopList).when(repository).findAll();
        doReturn(Optional.of(stop)).when(repository).findById(1L);
        service.updateStop(1L, new Stop(1L, "Либідська-2"));
        List<Stop> returnedWidget = service.GetStops();

        assertEquals(returnedWidget.get(0).getName(), "Либідська-2");
    }

    @Test
    void testAdd() {
        Stop stop = new Stop(1L, "Либідська-2");
        ArrayList<Stop> stopList = new ArrayList<>();
        stopList.add(stop);
        doReturn(stopList).when(repository).findAll();
        service.addNewStop(new Stop(1L, "Либідська-2"));
        service.addNewStop(new Stop(1L, "Либідська-3"));
        List<Stop> returnedWidget = service.GetStops();
        assertEquals(returnedWidget.get(0).getName(), "Либідська-2");
    }

    @Test
    void testDelete() {
        Stop stop = new Stop(1L, "Либідська-2");
        ArrayList<Stop> stopList = new ArrayList<>();
        stopList.add(stop);
        doReturn(stopList).when(repository).findAll();
        doReturn(true).when(repository).existsById(1L);
        service.deleteStop(1L);
        List<Stop> returnedWidget = service.GetStops();
        assertEquals(returnedWidget.size(), 1);
    }



}
