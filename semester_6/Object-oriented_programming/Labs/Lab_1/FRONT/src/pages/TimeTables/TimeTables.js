import React from "react";
//import * as API from  "API.js"
/* We simply can use an array and loop and print each user */
import {TimeTableObject} from "../../models/TimeTableObject";
import {Redirect} from 'react-router-dom'
import NavBar from "../../components/nav-bar";

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
        return parseInt(numberStr)
    }

    render() {
        return (
            <div>
                <NavBar fatherlink={'/'}/>
                <TimeTableObject routeId = {this.state.routeId}/>
            </div>


        );
    }
}
