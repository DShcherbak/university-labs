import React from "react";
//import * as API from  "API.js"
/* We simply can use an array and loop and print each user */
import styles from "./TimeTables.module.css"
import {TimeTableObject} from "../../models/TimeTableObject";
import { Redirect } from 'react-router-dom'

export class GeneralTimeTables extends React.Component{
    constructor(props) {
        super(props);
        let id = this.getRouteId(window.location.href)
        this.state = {
            routeId : id
        }
    }

    getRouteId(url){
        let id = url.lastIndexOf('=')
        let numberStr = url.substring(id + 1)
        let number = parseInt(numberStr)
        return number
    }

    render() {
        return (
            <div>
                <TimeTableObject routeId = {this.state.routeId}/>
            </div>


        );
    }
}

class TimeTables extends React.Component {

    GetRoutes(){
        //TODO: USE API
        return [new Map([["Station 1", 0], ["Station 2", 3], ["Station 4", 4]]),
            new Map([["Station 1", 0], ["Station 4", 9], ["Station 9", 13]]),
            new Map([["Station 1", 0], ["Station 5", 3], ["Station 7", 4]])]
    }

    constructor(props) {
        super(props);
        this.state = {
            routeId : props.routeId
        }
    }

    render() {
        return (
            <div>
                <Redirect to={"/timetables"}/>
                <TimeTableObject routeId = {this.state.routeId}/>
            </div>


        );
    }
}

//export default TimeTables;