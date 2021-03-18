import React from "react";
//import * as API from  "API.js"
/* We simply can use an array and loop and print each user */
import styles from "./Routes.module.css"
import * as obj1 from "../../models/RouteObject"
import {RouteObject} from "../../models/RouteObject";

class RoutesList extends React.Component {
    constructor(props) {
        super(props);
    }
    render() {
        const listItems = this.props.routes.map((number) => <li><RouteObject route = {number} number = {145}/></li>);
        return (
            <ul>{listItems}</ul>
        );

    }
}

class Routes extends React.Component {

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
            <div className={styles.container}>
                <RoutesList routes = {this.routes}/>
            </div>


        );
    }
}

export default Routes;