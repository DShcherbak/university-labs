package com.company;

public class ArrayHolder {
    public int[] arr;

    public ArrayHolder(int[] arr){
        this.arr = arr;
    }

    public String ToString(){
        StringBuilder builder = new StringBuilder("{");
        for (int j : arr) {
            builder.append(j).append(", ");
        }
        return builder.substring(0, builder.length() - 2) + "}";
    }
}
