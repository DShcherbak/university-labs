import React from "react";
import * as API from "../../API.js"
import styles from "./Routes.module.css"
import {RouteObject} from "../../models/RouteObject"


class Routes extends React.Component {

    componentDidMount = () => {
        this.GetRoutes().then((routes) => {
            this.setState({
                routes: routes
            })
        }).catch((error) => {
            console.log(error);
        });
    }

    async GetRoutes() {
        return await API.getRoutes()
    }

    constructor(props) {
        super(props);
        this.state ={
            routes: []
        }
    }

    render() {
        let listItems = this.state.routes.map((route) => <li><RouteObject routeProps = {route}/></li>);
        return (
            <div className={styles.container}>
                <ul>{listItems}</ul>
            </div>
        );
    }
}

export default Routes;