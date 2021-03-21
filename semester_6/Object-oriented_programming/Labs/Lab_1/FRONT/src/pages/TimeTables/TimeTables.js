import React from "react";
//import * as API from  "API.js"
/* We simply can use an array and loop and print each user */
import styles from "./TimeTables.module.css"
import {TimeTableObject} from "../../models/TimeTableObject";


class TimeTables extends React.Component {

    GetRoutes(){
        //TODO: USE API
        return [new Map([["Station 1", 0], ["Station 2", 3], ["Station 4", 4]]),
            new Map([["Station 1", 0], ["Station 4", 9], ["Station 9", 13]]),
            new Map([["Station 1", 0], ["Station 5", 3], ["Station 7", 4]])]
    }

    constructor(props) {
        super(props);
        this.routes = this.GetRoutes();
    }



    render() {
        return (
            <div>
                <TimeTableObject/>
            </div>


        );
    }
}

export default TimeTables;