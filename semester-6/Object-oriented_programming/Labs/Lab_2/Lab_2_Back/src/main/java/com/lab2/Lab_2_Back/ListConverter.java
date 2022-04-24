package com.lab2.Lab_2_Back;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import javax.persistence.AttributeConverter;
import javax.persistence.Converter;

import static java.util.Collections.*;

@Converter
public class ListConverter implements AttributeConverter<List<Long>, String> {
    private static final String SPLIT_CHAR = ";";

    @Override
    public String convertToDatabaseColumn(List<Long> longList) {
        String result = "";
        if(longList != null){
            for(Long l : longList) result = result.concat(String.valueOf(l)).concat(SPLIT_CHAR);
        }
        return result.substring(0,result.length()-1);
    }

    @Override
    public List<Long> convertToEntityAttribute(String string) {
        List<Long> result = new ArrayList<>();
        List<String> stringList = string != null ? Arrays.asList(string.split(SPLIT_CHAR)) : emptyList();
        for(String s : stringList) result.add(Long.valueOf(s));
        return result;
    }
}