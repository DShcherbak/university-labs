package com.lab2.Lab_2_Back.Classes;

import com.lab2.Lab_2_Back.Stop.Stop;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

class StopCLassTest {

    @Test
    void testEmptyGetSet() {
        Stop stop = new Stop();
        Long longTestValue = 55L;
        String StringTestValue = "Test name";
        stop.setId(longTestValue);
        stop.setName(StringTestValue);
        assertEquals(longTestValue, stop.getId());
        assertEquals(StringTestValue, stop.getName());
    }

    @Test
    void testToString() {
        Long longTestValue = 55L;
        String StringTestValue = "Test name";
        Stop stop = new Stop(longTestValue, StringTestValue);
        assertEquals(longTestValue, stop.getId());
        assertEquals(StringTestValue, stop.getName());
        assertEquals(stop.toString(), "Stop{" +
                "id=" + longTestValue +
                ", name='" + StringTestValue + '\'' +
                '}');
    }

    @Test
    void testEquals() {
        Long longTestValue1 = 55L;
        String StringTestValue1 = "Test name";
        Long longTestValue2 = 0L;
        String StringTestValue2 = "Not test name";

        Stop s1 = new Stop();
        s1.setId(longTestValue1);
        s1.setName(StringTestValue1);

        Stop s2 = new Stop(StringTestValue1);
        s2.setId(longTestValue1);

        Stop s3 = new Stop(longTestValue2, StringTestValue2);
        assertEquals(s1, s2);
        assertNotEquals(s1, s3);
        assertNotEquals(s2, s3);
        s2.setId(longTestValue2);
        s2.setName(StringTestValue2);
        assertNotEquals(s1, s2);
        assertNotEquals(s1, s3);
        assertEquals(s2, s3);

    }

    @Test
    void testHashCode() {
        Long longTestValue1 = 55L;
        String StringTestValue1 = "Test name";
        Long longTestValue2 = 0L;
        String StringTestValue2 = "Not test name";

        Stop s1 = new Stop();
        s1.setId(longTestValue1);
        s1.setName(StringTestValue1);

        Stop s2 = new Stop(StringTestValue1);
        s2.setId(longTestValue1);

        Stop s3 = new Stop(longTestValue2, StringTestValue2);
        assertEquals(s1.hashCode(), s2.hashCode());
        assertNotEquals(s1.hashCode(), s3.hashCode());
        assertNotEquals(s2.hashCode(), s3.hashCode());
        s2.setId(longTestValue2);
        s2.setName(StringTestValue2);
        assertNotEquals(s1.hashCode(), s2.hashCode());
        assertNotEquals(s1.hashCode(), s3.hashCode());
        assertEquals(s2.hashCode(), s3.hashCode());

    }
}
