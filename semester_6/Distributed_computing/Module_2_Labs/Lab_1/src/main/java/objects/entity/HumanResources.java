package objects.entity;

import objects.DOM.HumanResourcesOffice;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;

public class HumanResources implements Serializable {
    public ArrayList<String> departments;
    public HashMap<String, ArrayList<String>> employees;

    public HumanResources(){
        departments = new ArrayList<>();
        employees = new HashMap<>();
    }
}
