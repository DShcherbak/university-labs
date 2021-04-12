import React from "react";
import * as API from "../../services/API.js"
import {RouteObject} from "../../models/RouteObject"
import Checkbox from "../../components/additional-components/Checkbox";
import { Link } from 'react-router-dom'
import NavBar from "../../components/nav-bar";
import Loading from "../../components/loading";
import Redirect from "react-router-dom/es/Redirect";
import styles from "../../styles/Routes.module.css"
import general from "../../styles/General.module.css"
import UserService from "../../services/UserService";


const routeTypes = [
    'Тролейбус',
    'Автобус',
    'Трамвай',
];

class RoutesEditor extends React.Component {

    makeSubset(subset, routes){
        let selectedRoutes = routes.filter(route => subset.has(this.getType(route["routeType"])))
        // console.log("SUBSET: " + selectedRoutes)
        let list = selectedRoutes.map(route => <li><RouteObject routeProps = {route}/></li>);
        return list
    }

    async isAdmin(){
        return await API.checkAdmin()
    }

    componentDidMount = () => {
        this.isAdmin().then(result => {
            this.setState({
                adminChecked : true,
                isAdmin: result
            })
        })
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
                counted : true
            })
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
            routes: [],
            verifiedAdmin: false,

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

    getSubsetNumber(subset){
        let number = 0
        if(subset.has("Тролейбус"))
            number += 1
        if(subset.has("Автобус"))
            number += 2
        if(subset.has("Трамвай"))
            number += 4
        return number;
    }

    toggleCheckbox = label => {
        if (this.selectedCheckboxes.has(label)) {
            this.selectedCheckboxes.delete(label);
        } else {
            this.selectedCheckboxes.add(label);
        }
        let newDisplayRoutes = this.state.routes.filter(route => this.selectedCheckboxes.has(this.getType(route["routeType"])))
        this.setState({
            displayRoutes: newDisplayRoutes
        }, function () {
            console.log(this.state);
        })
    }

    createCheckbox = label => (
        <Checkbox
            label={label}
            handleCheckboxChange={this.toggleCheckbox}
            key={label}
        />
    )

    createCheckboxes = () => (
        routeTypes.map(this.createCheckbox)
    )

    displayTime(timeStr){
        if(timeStr === undefined || timeStr === null){
            return '--:--'
        }
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
        if(stops === undefined){
            return (<ul/>)
        }
        return (<ul>{stops.map((stop) => <li>{this.getStopName(stop)}</li>)}</ul>)
    }

    makeRoutesList(routes){
        return (<ul className={styles.listOfRoutes}>{routes.map((route) => <Link to={"/edit/route?routeId=" + route["id"]}><li key={route["id"]} className = {styles.listElement}>
            <div  className={styles.routeCard}>
                <div className={styles.listText}><p>{this.getType(route["routeType"])} номер {route["routeNumber"]}</p></div>
                <div className={styles.listText}>Початок руху: {this.displayTime(route["startTime"])}</div>
                <div className={styles.listText}>Останній маршрут: {this.displayTime(route["endTime"])}</div>

                <div className={styles.listText}>Маршрут зупинок:<br/>
                    {this.makeStopList(route["stops"])}</div>

            </div></li></Link>)}</ul>);
    }


    render() {
        if(!UserService.isAdmin()){
            alert("You have no admin rights!")
            return (<Redirect to={'/'}/>)
        } else {
            if (this.state.counted) {
                let list = this.makeRoutesList(this.state.displayRoutes)
                return (
                    <div>
                        <NavBar fatherlink={'/editor'}/>
                        <div className={general.MainBodyContainer}>
                            <Link to={"/add/route"}>
                                <button>Додати новий маршрут</button>
                            </Link>
                            {this.createCheckboxes()}
                            <div className={styles.container}>
                                {list}
                            </div>
                        </div>
                    </div>
                );
            } else {
                return (
                    <div>
                        <NavBar fatherlink={'/editor'}/>
                        <div className={general.MainBodyContainer}>
                            <Link to={"/add/route"}>
                                <button>Додати новий маршрут</button>
                            </Link>
                            {this.createCheckboxes()}
                            <div className={styles.container}/>
                        </div>
                    </div>
                );
            }
        }

    }
}

export default RoutesEditor;