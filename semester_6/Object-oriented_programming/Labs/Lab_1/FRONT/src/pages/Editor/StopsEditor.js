import React from "react";
import * as API from "../../services/API.js"
import {RouteObject} from "../../models/RouteObject"
import Checkbox from "../../components/additional-components/Checkbox";
import { Link } from 'react-router-dom'
import NavBar from "../../components/nav-bar";
import Loading from "../../components/loading";
import Redirect from "react-router-dom/es/Redirect";
import styles from "../../styles/General.module.css"
import UserService from "../../services/UserService";

const routeTypes = [
    'Тролейбус',
    'Автобус',
    'Трамвай',
];

class StopsEditor extends React.Component {

    async isAdmin(){
        return await API.checkAdmin()
    }

    componentDidMount = () => {

        this.GetStops().then((stops) => {
            let newStops = []
            stops.forEach((stop) => {
                newStops.push(<Link to={"/edit/stop?stopId=" + stop.id}>
                    <li key={stop.id}>Станція {stop.name}</li>
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

    makeStopList(stops){
        return (<ul>{stops.map((stop) => stop)}</ul>)
    }


    render() {
        if(!UserService.isAdmin()){
            alert("You have no admin rights!")
            return (<Redirect to={'/'}/>)
        } else {
            let list = this.makeStopList(this.state.stops)
            if (this.state.counted) {
                return (
                    <div>
                        <NavBar fatherlink={'/editor'}/>
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
                        <NavBar fatherlink={'/editor'}/>
                        <Link to={"/add/stop"}>
                            <button>Додати нову зупинку</button>
                        </Link>
                        <div className={styles.container}/>
                    </div>
                );
            }
        }
    }
}

export default StopsEditor;