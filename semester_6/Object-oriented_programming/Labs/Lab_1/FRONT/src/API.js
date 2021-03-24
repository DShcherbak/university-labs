import React from "react";

let backUrl = 'http://localhost:8080/'

export async function getRoutes() {
    return await sendGetRequest(backUrl + 'routes');
}

export async function getRouteById(id){
    return await sendGetRequest(backUrl + 'route/' + id);
}

export async function getStops() {
    let c = await sendGetRequest(backUrl + 'stops');
    return c
}

export async function updateRoute(state){
    sendPostRequest(backUrl + 'route/' + state.number, state)
}

export async function checkAvailable(id) {
    let c = await sendGetRequest(backUrl + 'route/' + id);
    return c === undefined || c === []
}

export async function deleteRoute(id){
    
}


function sendGetRequest(requestUrl){
    // Simple POST request with a JSON body using fetch
        const requestOptions = {
        method: 'Get',
        headers: {},
       // body: JSON.stringify({ title: 'React Get Request Example' })
        };
        return fetch(requestUrl, requestOptions).then(response => response.json())
            .then((responseData) => {
                    return responseData;
            })
}

function convertStopsToInt(stops, allStops) {
    console.log("Converting...." + stops)
    console.log("Converting...." + allStops)
    let result = []
    for(let i = 0; i < stops.length; i++){
        for(let j = 0; j < allStops.length; j++){
            if(stops[i] === allStops[j]["stop_name"]){
                result.push(allStops[j]["stop_id"])
            }
        }
    }
    console.log("converted: " + result)
    return result
}

function sendPostRequest(url, state){
    // Simple POST request with a JSON body using fetch
        console.log("Trying to push a request here!");
        console.log(state.timeTable)
        let intStops = convertStopsToInt(state.stops, state.allStops)
    console.log(intStops)
    const requestOptions = {
        method: 'Post',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
            "routeId": state.number,
            "stops": intStops,
            "startTime": state.startTime,
            "endTime": state.endTime,
            "interval": state.interval,
            "type": typeToInt(state.type),
            "timetable": state.timeTable.slice(1)})
    };
    fetch(url, requestOptions).
    then(response => response.json()).then(data => console.log("POST RESPONSE " + data));
}

function typeToInt(type){
    switch (type) {
        case "Тролейбус":
            return 1;
        case "Автобус":
            return 2;
        case "Трамвай":
            return 3;
        default:
            return 1;

    }
}

async function postData(url = '', data = {}) {
    // Default options are marked with *
    const response = await fetch(url, {
        method: 'POST', // *GET, POST, PUT, DELETE, etc.
        mode: 'cors', // no-cors, *cors, same-origin
        cache: 'no-cache', // *default, no-cache, reload, force-cache, only-if-cached
        credentials: 'same-origin', // include, *same-origin, omit
        headers: {
            'Content-Type': 'application/json'
            // 'Content-Type': 'application/x-www-form-urlencoded',
        },
        redirect: 'follow', // manual, *follow, error
        referrerPolicy: 'no-referrer', // no-referrer, *client
        body: JSON.stringify(data) // body data type must match "Content-Type" header
    });
    return await response.json(); // parses JSON response into native JavaScript objects
}

postData('https://example.com/answer', { answer: 42 })
    .then((data) => {
        console.log(data); // JSON data parsed by `response.json()` call
    });


