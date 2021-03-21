import React from "react";
import * as API from "../../API.js"
/* We simply can use an array and loop and print each user */
import styles from "./Routes.module.css"
import {RouteObject} from "../../models/RouteObject"


class Routes extends React.Component {

    componentDidMount = () => {
        this.GetRoutes().then((routes) => {
            console.log("Sending to render: ")
            console.log(routes)
            // When all results have arrived, put them into the component's state
            this.routes = routes
            console.log(this.routes)
            this.setState({
                routes: routes
            });

        }).catch((error) => {
            console.log(error);
        });
    }

    async GetRoutes() {

        //TODO: USE API
        return await API.getRoutes()
        /*[new Map([["Station 1", 0], ["Station 2", 3], ["Station 4", 4]]),
            new Map([["Station 1", 0], ["Station 4", 9], ["Station 9", 13]]),
            new Map([["Station 1", 0], ["Station 5", 3], ["Station 7", 4]])]*/
    }

    constructor(props) {
        super(props);
        this.routes = []
    }

    render() {
        let listItems = this.routes.map((number) => <li><RouteObject routeProps = {number}/></li>);
        return (
            <div className={styles.container}>
                <ul>{listItems}</ul>
            </div>


        );
    }
}

export default Routes;