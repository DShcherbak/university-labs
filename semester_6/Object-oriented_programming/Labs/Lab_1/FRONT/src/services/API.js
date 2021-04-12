import * as PureAPI from "./PureAPI";

let backUrl = 'http://localhost:8080/api/'


//ROUTES

export async function getRoutes() {
    return await PureAPI.sendGetRequest(backUrl + 'routes')
}

export async function getRouteById(id){
    return await PureAPI.sendGetRequest(backUrl + 'routes/' + id);
}

export async function createRoute(state) {
    return await PureAPI.sendPostRequest(backUrl + 'routes', routeToJson(state))
}

export async function updateRoute(state){
    return await PureAPI.sendPutRequest(backUrl + 'routes/' + state.id + '/' + state.oldNumber, routeToJson(state))
}

export async function checkAvailableRoute(id) {
    let c = await PureAPI.sendGetRequest(backUrl + 'route/' + id);
    return (!c) || (Object.keys(c).length === 0)
}

export async function deleteRoute(id){
    return await PureAPI.sendDeleteRequest(backUrl + 'routes/' + id)
}

function routeToJson(state) {
    let intTimeTable = convertTimeTable(state.timeTable.slice(1))
    console.log("Sending: " + state.startTime)
    return JSON.stringify({
        "id" : state.id,
        "routeNumber": state.number,
        "stops": state.stops,
        "startTime": state.startTime,
        "endTime": state.endTime,
        "interval": state.interval,
        "routeType": typeToInt(state.type),
        "timetable": intTimeTable})
}

function convertTimeTable(timeTable){
    let result = []
    for(let i = 0; i < timeTable.length; i++){
        result.push(parseInt(timeTable[i]))
    }
    return result
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








//STOPS

export async function getStops() {
    return await PureAPI.sendGetRequest(backUrl + 'stops')
}

export async function getStop(id){
    return await PureAPI.sendGetRequest(backUrl + 'stops/' + id);
}

export async function createStop(state) {
    return await PureAPI.sendPostRequest(backUrl + 'stops', stopToJson(state))
}

export async function updateStop(id, state){
    return await PureAPI.sendPutRequest(backUrl + 'stops/' + id, stopToJson(state))
}

export async function deleteStop(id){
    return await PureAPI.sendDeleteRequest(backUrl + 'stops/' + id)
}

function stopToJson(state) {
    return JSON.stringify({
        "id": state.id,
        "name": state.name
    })
}







//EMPLOYEES

export async function getEmployees() {
    return await PureAPI.sendGetRequest(backUrl + 'employees')
}

export async function getEmployee(id) {
    return await PureAPI.sendGetRequest(backUrl + 'employees/' + id)
}

export function createEmployee(state){
    return PureAPI.sendPostRequest(backUrl + 'employees', employeeToJson(state))
}

export async function updateEmployee(state){
    return await PureAPI.sendPutRequest(backUrl + 'employees/' + state.id, employeeToJson(state))
}

export function deleteEmployee(id){
    return PureAPI.sendDeleteRequest(backUrl + 'employees/' + id)
}

function employeeToJson(state) {
    return JSON.stringify({
        "id": state.id,
        "name": state.name,
        "surname": state.surname,
        "routeId": state.route_number
    })
}

