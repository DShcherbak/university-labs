import React from "react";
import * as API from "../../services/API.js"
import generalStyles from "../../styles/General.module.css"
import styles from "../../styles/Routes.module.css"
import {RouteObject} from "../../models/RouteObject"
import Checkbox from "../../components/additional-components/Checkbox";
import { Link } from 'react-router-dom'
import NavBar from "../../components/nav-bar";


const routeTypes = [
    'Тролейбус',
    'Автобус',
    'Трамвай',
];

class Routes extends React.Component {

    componentDidMount = () => {
        this.GetRoutes().then((routes) => {
            this.setState({
                routes : routes
            })
        }).catch((error) => {
            console.log(error);
        });
        this.GetStops().then((stops) => {
            this.setState({
                stops : stops,
                counted: true
            })
            console.log(this.state.stops)
        }).catch((error) => {
            console.log(error);
        });
    }

    async GetRoutes() {
        return await API.getRoutes()
    }

    async GetStops() {
        return await API.getStops()
    }

    constructor(props) {
        super(props);
        this.state ={
            displayRoutes: [],
            routes: []
        }
    }

    componentWillMount = () => {
        this.selectedCheckboxes = new Set();
    }

    getType(number){
        switch (number) {
            case 1:
                return "Тролейбус";
            case 2:
                return "Автобус";
            case 3:
                return "Трамвай";
            default:
                return "Тролейбус";
        }
    }

    toggleCheckbox = label => {
        if (this.selectedCheckboxes.has(label)) {
            this.selectedCheckboxes.delete(label);
        } else {
            this.selectedCheckboxes.add(label);
        }
        let newDisplayRoutes = this.state.routes.filter(route => this.selectedCheckboxes.has(this.getType(route["routeType"])))
        this.setState({
            displayRoutes: newDisplayRoutes,
        }, function () {
            console.log(this.state);
        })
    }

    createCheckbox = label => (
        <Checkbox
            label={label}
            className={generalStyles.checkbox}
            handleCheckboxChange={this.toggleCheckbox}
            key={label}
        />
    )

    createCheckboxes = () => (
        routeTypes.map(this.createCheckbox)
    )

    displayTime(timeStr){
        return timeStr.toString().substring(11,16)
    }

    getStopName(id){
        let result = "<Помилка імені>"
        if(this.state.stops === undefined || this.state.stops === null){
            return result
        }
        this.state.stops.forEach((stop) => {
            if(stop.id === id){
                result = stop.name
            }
        })
        return result
    }

    makeStopList(stops){
        return (<ul>{stops.map((stopId) => <li>{this.getStopName(stopId)}</li>)}</ul>)
    }

    makeRoutesList(routes){
        return (<ul className={styles.listOfRoutes}>{routes.map((route) => <Link to={"/timetables?routeId=" + route["id"]}><li key={route["id"]} className = {styles.listElement}>
            <div  className={styles.routeCard}>
                <div className={styles.listText}><p>{this.getType(route["routeType"])} номер {route["routeNumber"]}</p></div>
                    <div className={styles.listText}>Початок руху: {this.displayTime(route["startTime"])}</div>
                    <div className={styles.listText}>Останній маршрут: {this.displayTime(route["endTime"])}</div>
                    <div className={styles.listText}>Маршрут зупинок:<br/>
                        {this.makeStopList(route["stops"])}</div>

            </div></li></Link>)}</ul>);
    }


    render() {
        if(this.state.counted){
            let list = this.makeRoutesList(this.state.displayRoutes)
            return (
                <div className={generalStyles.MainApp}>
                    <NavBar fatherlink={'/'}/>
                    <div className={generalStyles.MainBodyContainer}>
                    {this.createCheckboxes()}
                    <div className={generalStyles.container}>
                        {list}
                    </div>
                    </div>
                </div>
            );
        } else {
            return (
                <div className={generalStyles.MainApp}>
                    <NavBar fatherlink={'/'}/>
                    <div className={generalStyles.MainBodyContainer}>
                    {this.createCheckboxes()}
                        <ul>
                            <li>Оберіть типи маршруту, які вас цікавлять</li>
                        </ul>
                    </div>
                </div>
            );
        }

    }
}

export default Routes;