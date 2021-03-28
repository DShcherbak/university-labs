import React from "react";
import * as API from "../../API.js"
import styles from "./Editor.module.css"
import {RouteObject} from "../../models/RouteObject"
import Checkbox from "../../components/additional-components/Checkbox";
import { Link } from 'react-router-dom'


const routeTypes = [
    'Тролейбус',
    'Автобус',
    'Трамвай',
];

class StopsEditor extends React.Component {


    componentDidMount = () => {
        this.GetStops().then((stops) => {
            let newStops = []
            stops.forEach((stop) => {
                newStops.push(<Link to={"/edit/stop?stopId=" + stop.stop_id}>
                    <li key={stop.stop_id}>Станція {stop.stop_name}</li>
                </Link>)
            })


            this.setState({
                stops : newStops,
                counted : true,
            })
        }).catch((error) => {
            console.log(error);
        });
    }

    async GetStops() {
        return await API.getStops()
    }

    constructor(props) {
        super(props);
        this.state ={
            stops: [],
            routes: []
        }
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
        //     console.log(this.state.optionalRoutes)
        //     console.log(this.selectedCheckboxes)
        //      console.log("I choose this one: ")
        //      console.log(this.state.optionalRoutes.get(this.getSubsetNumber(this.selectedCheckboxes)))
        //      let newDisplay = this.state.optionalRoutes.get(this.getSubsetNumber(this.selectedCheckboxes))
        //     console.log(newDisplay)


    makeStopList(stops){
        return (<ul>{stops.map((stop) => stop)}</ul>)
    }


    render() {
        let list = this.makeStopList(this.state.stops)
        if(this.state.counted){
            return (
                <div>
                    <Link to={"/add/stop"}>
                        <button>Додати нову зупинку</button>
                    </Link>
                    <div className={styles.container}>
                        {list}
                    </div>
                </div>
            );
        } else {
            return (
                <div>
                    <Link to={"/add/stop"}>
                        <button>Додати нову зупинку</button>
                    </Link>
                    <div className={styles.container}/>
                </div>
            );
        }

    }
}

export default StopsEditor;