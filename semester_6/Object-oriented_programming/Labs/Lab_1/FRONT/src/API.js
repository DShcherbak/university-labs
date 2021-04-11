import * as PureAPI from "./PureAPI";
let backUrl = 'http://localhost:8080/api/'

//USER

export async function checkAdmin(){
    return true //await sendGetRequest(backUrl + 'admin')
}

export function setUser(email){
    return PureAPI.sendPostRequest(backUrl + 'admin', JSON.stringify("email:" + email))
}


//ROUTES

export async function getRoutes() {
    return await PureAPI.sendCoolGetRequest(backUrl + 'routes')
}

export async function getRouteById(id){
    return await PureAPI.sendCoolGetRequest(backUrl + 'routes/' + id);
}

export async function createRoute(state) {
    return await PureAPI.sendPostRequest(backUrl + 'routes/' + state.oldId, routeToJson(state))
}

export async function updateRoute(state){
    return await sendUpdateRequest(backUrl + 'routes/' + state.oldId, routeToJson(state))
}

export async function checkAvailableRoute(id) {
    let c = await PureAPI.sendGetRequest(backUrl + 'route/' + id);
    return (!c) || (Object.keys(c).length === 0)
}

export async function deleteRoute(id, state){
    return await PureAPI.sendPostRequest(backUrl + 'delete/route/' + id,  routeToJson(state))
}

function convertStopsToInt(stops, allStops) {
    let result = []
    for(let i = 0; i < stops.length; i++){
        for(let j = 0; j < allStops.length; j++){
            if(stops[i] === allStops[j]["stop_name"]){
                result.push(allStops[j]["stop_id"])
            }
        }
    }
    return result
}


//STOPS

export async function getStops() {
    return await PureAPI.sendGetRequest(backUrl + 'stops')
}


export async function updateStop(state){
    return await PureAPI.sendPostRequest(backUrl + 'stop/' + state.oldId, stopToJson(state))
}

export async function deleteStop(id, state){
    return await PureAPI.sendPostRequest(backUrl + 'delete/stop/' + id, stopToJson(state))
}

function stopToJson(state) {
    let json = JSON.stringify({
        "stop_id": state.id,
        "stop_name": state.name
    })
    console.log("SEND POST: " + json)
    return json
}


//EMPLOYEES

export async function getEmployees() {
    return await PureAPI.sendGetRequest(backUrl + 'employee/all')
}

export async function getEmployee(id) {
    console.log("req is coming")
    return await PureAPI.sendGetRequest(backUrl + 'employee/' + id)
}

export async function updateEmployee(state){
    return await PureAPI.sendPostRequest(backUrl + 'employee/' + state.oldId, employeeToJson(state))
}

export async function deleteEmployee(id, state){
    return await PureAPI.sendPostRequest(backUrl + 'delete/employee/' + id, employeeToJson(state))
}

function employeeToJson(state) {
    let json = JSON.stringify({
        "id": state.id,
        "name": state.name,
        "surname": state.surname,
        "route_number": state.route_number
    })
    console.log("SEND POST: " + json)
    return json
}


//REQUESTS






function convertTimeTable(timeTable){
    let result = []
    for(let i = 0; i < timeTable.length; i++){
        result.push(parseInt(timeTable[i]))
    }
    return result
}

function routeToJson(state) {
    let intStops = convertStopsToInt(state.stops, state.allStops)
    let intTimeTable = convertTimeTable(state.timeTable.slice(1))
    return JSON.stringify({
        "routeId": state.number,
        "stops": intStops,
        "startTime": state.startTime,
        "endTime": state.endTime,
        "interval": state.interval,
        "type": typeToInt(state.type),
        "timetable": intTimeTable})
}





function sendUpdateRequest(url, body){
    // Simple POST request with a JSON body using fetch

    const requestOptions = {
        method: 'Put',
        headers: { 'Content-Type': 'application/json' },
        body: body
    };
    return fetch(url, requestOptions).then(response => response.json())
        .then((responseData) => {
            return responseData;
        })
}

function sendDeleteRequest(url, body){

    const requestOptions = {
        method: 'Delete',
        headers: { 'Content-Type': 'application/json' },
        body: body
    };
    return fetch(url, requestOptions).then(response => response.json())
        .then((responseData) => {
            return responseData;
        })
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