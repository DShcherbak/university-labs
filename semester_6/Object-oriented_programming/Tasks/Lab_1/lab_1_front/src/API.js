import React, { Component } from "react";

export function sendGetRequest(){
    // Simple POST request with a JSON body using fetch
        const requestOptions = {
        method: 'Get',
        headers: {},
       // body: JSON.stringify({ title: 'React Get Request Example' })
        };
        fetch('http://localhost:8080/add', requestOptions).then(response => response.json())
            .then(data => console.log("Name is : " + data.Name));
}



export function sendPostRequest(){
    // Simple POST request with a JSON body using fetch
        console.log("Trying to push a request here!");
        const requestOptions = {
        method: 'Get',
        headers: { 'Content-Type': 'application/json' },    
        body: JSON.stringify({ title: 'React Get Request Example' })
        };
        fetch('http://localhost:8080/add', requestOptions).then(response => response.json()).then(data => console.log(data));
}


