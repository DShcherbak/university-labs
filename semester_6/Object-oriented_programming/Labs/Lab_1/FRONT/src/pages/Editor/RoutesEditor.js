import React from "react";
import * as API from "../../API.js"
import styles from "./Editor.module.css"
import {RouteObject} from "../../models/RouteObject"
import Checkbox from "../../components/additional-components/Checkbox";
import { Link } from 'react-router-dom'
import NavBar from "../../components/nav-bar";
import Loading from "../../components/loading";
import Redirect from "react-router-dom/es/Redirect";


const routeTypes = [
    'Тролейбус',
    'Автобус',
    'Трамвай',
];

class RoutesEditor extends React.Component {

    makeSubset(subset, routes){
        let selectedRoutes = routes.filter(route => subset.has(this.getType(route["type"])))
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
                isAdmin: result["isAdmin"]
            })
        })
        this.GetRoutes().then((routes) => {
            this.setState({
                routes : routes
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
        let newDisplayRoutes = this.state.routes.filter(route => this.selectedCheckboxes.has(this.getType(route["type"])))
        this.setState({
            displayRoutes: newDisplayRoutes,
            counted: true
        }, function () {
            console.log(this.state);
        })

        //     console.log(this.state.optionalRoutes)
        //     console.log(this.selectedCheckboxes)
        //      console.log("I choose this one: ")
        //      console.log(this.state.optionalRoutes.get(this.getSubsetNumber(this.selectedCheckboxes)))
        //      let newDisplay = this.state.optionalRoutes.get(this.getSubsetNumber(this.selectedCheckboxes))
        //     console.log(newDisplay)
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

    makeStopList(stops){
        return (<ul>{stops.map((stop) => <li>{stop}</li>)}</ul>)
    }

    makeRoutesList(routes){
        return (<ul>{routes.map((route) => <Link to={"/edit/route?routeId=" + route["routeId"]}><li key={route["routeId"]}>
            <p> {this.getType(route["type"])} номер {route["routeId"]}<br/>
                Початок руху: {} <br/>
                Останній маршрут: {} <br/>
                Маршрут зупинок:
                {this.makeStopList(route["stops"])}</p></li></Link>)}</ul>);
    }


    render() {
        if(this.state === null || !this.state.adminChecked){
            return (
                <Loading/>
            );
        } else if(!this.state.isAdmin){
            return (<Redirect to={'/'}/>)
        } else {
            let list = this.makeRoutesList(this.state.displayRoutes)
            if (this.state.counted) {
                return (
                    <div>
                        <NavBar fatherlink={'/editor'}/>
                        <Link to={"/add/route"}>
                            <button>Додати новий маршрут</button>
                        </Link>
                        {this.createCheckboxes()}
                        <div className={styles.container}>
                            {list}
                        </div>
                    </div>
                );
            } else {
                return (
                    <div>
                        <NavBar fatherlink={'/editor'}/>
                        <Link to={"/add/route"}>
                            <button>Додати новий маршрут</button>
                        </Link>
                        {this.createCheckboxes()}
                        <div className={styles.container}/>
                    </div>
                );
            }
        }

    }
}

export default RoutesEditor;