import React from "react";

let backUrl = 'http://localhost:8080/'

export async function getRoutes() {
    return await sendGetRequest(backUrl + 'routes');
}

export async function getRouteById(id){
    return await sendGetRequest(backUrl + 'route/' + id);
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

function sendPostRequest(){
    // Simple POST request with a JSON body using fetch
        console.log("Trying to push a request here!");
        const requestOptions = {
        method: 'Post',
        headers: { 'Content-Type': 'application/json' },    
        body: JSON.stringify({ title: 'React Get Request Example' })
        };
        fetch('http://localhost:8080/add', requestOptions).then(response => response.json()).then(data => console.log(data));
}


