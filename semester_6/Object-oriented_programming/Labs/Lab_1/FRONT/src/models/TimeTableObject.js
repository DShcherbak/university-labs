import React from "react";
import {Redirect} from "react-router-dom";
import * as API from "../services/API";
import { withRouter } from 'react-router-dom';
import TimeTableForm from "../components/additional-components/TimeTableForm";
import NavBar from "../components/nav-bar";
import styles from "../styles/General.module.css";



export class TimeTableObject extends React.Component{
    constructor(props) {
        super(props);
        this.state = {
            number : props.routeId,
            startTime : "06:40",
            endTime : "00:20",
            interval : 10,
            stops : new Map()
        }
    }

    getCurrentTime() {
        let timeStr = new Date().toLocaleString().split(",")[1]
        let result = parseInt(timeStr.split(':')[0]) * 60 + parseInt(timeStr.split(':')[1])
        let pm = timeStr.split(" ")[2]
        if(pm === "PM"){
            result += (12 * 60);
        }
        return result.toString()
    }

    toNormalTime(value){
        let hours = (Math.floor(value/60) % 24)
        return(Math.floor(hours/10)).toString() +
            ((hours) % 10).toString() +
            ":" +
            (Math.floor((value % 60)/10)).toString() +
            ((value % 60) % 10).toString();

    }

    toTimePeriod(value){
        if(value < 60){
            return value.toString() + " хвилин.";
        } else {
            let hours = Math.floor(value/60).toString();
            value %= 60;
            return hours + " годин " + value.toString() + " хвилин.";
        }
    }

    timeToInt(timeStr){
        return parseInt(timeStr.split(':')[0]) * 60 + parseInt(timeStr.split(':')[1])
    }

    countTimeToStops(){
        let timeToStops = new Map();

        let currentTime = this.getCurrentTime()
        let currentBus = this.timeToInt(this.state.endTime);
        while(currentBus - this.state.interval > currentTime) currentBus-=this.state.interval;

        while(currentBus + this.totalTime > currentTime){
            let a = 0;
            for (let [key, value] of  this.state.stops.entries()) {
                a += value;
                if(currentBus + a - currentTime  >= 0){
                    timeToStops.set(key, currentBus + a - currentTime);
                }

            }
            currentBus -= this.state.interval;
        }

        return timeToStops;
    }

    listTime(timeToStops){
        let list = []
        timeToStops.forEach((value, key) => list.push(<tr><td>{key}</td><td>{value}</td></tr>));
        return (
            <table>{list}</table>
        );
    }

    getStopName(id){
        let result = "<Помилка імені>"
        if(this.state.stops === undefined){
            return result
        } else {
            this.state.stops.forEach((stop) => {
                if(stop.id === id)
                    result = stop.name
            })
            return result
        }
    }

    componentDidMount = () => {
        this.GetStops().then((stops) => {
            this.setState({
                stops: stops
            })
        })
        this.GetTimeTable().then((route) => {
        if(route === undefined){
            this.setState({
                incorrectRoute : true
            })
        } else {
            let newStops = new Map()
            let stopIds = route.stops
            let tt = route.timetable
            newStops.set(this.getStopName(stopIds[0]), 0)
            for(let i = 0; i < tt.length; i++){
                newStops.set(this.getStopName(stopIds[i+1]), tt[i])
            }
            this.setState({
                id: route.id,
                number : route.routeNumber,
                startTime : route.startTime,
                endTime : route.endTime,
                interval : route.interval,
                stops : newStops,
                incorrectRoute : false
            }, function () {
                console.log("ST: " + this.state.startTime)
            })
        }
        }).catch((error) => {
            console.log(error);
        });
    }

    async GetTimeTable() {
        return await API.getRouteById(this.state.number)
    }

    async GetStops() {
        return await API.getStops()
    }

    displayTime(timeStr){
        if(timeStr === undefined || timeStr === null){
            return '--:--'
        }
        return timeStr.toString().substring(11,16)
    }

    AddButton(){
        return (
            <div>
                <TimeTableForm currentId = {this.state.number}/>
            </div>
        )
    }

    render(){

        if(this.state.incorrectRoute){
            return (
                <div className={styles.MainBodyContainer}>
                    {this.AddButton()}
                    <h1>Маршуруту з номером {this.state.number} не знайдено.</h1>
                </div>
            )
        }
        this.totalTime = 0;
        this.state.stops.forEach((value, key) => this.totalTime += value);
        let currentTime = this.getCurrentTime();
        let timeToStops = this.countTimeToStops();
        let listStopTimes = this.listTime(timeToStops)
        if(this.state === undefined || this.state.number === undefined || isNaN(this.state.number)){
            return  <div className={styles.MainBodyContainer}>
                    <Redirect to={"/timetables"}/>
                    {this.AddButton()}
                    <p>Поточний час: {this.toNormalTime(currentTime)}</p>
                </div>
        } else {
            return (
                <div className={styles.MainBodyContainer}>
                    <Redirect to={"/timetables"}/>
                    {this.AddButton()}
                    <p>Поточний час: {this.toNormalTime(currentTime)}</p>
                    <p>Номер маршруту: {this.state.number}</p>
                    <p>Перший рейс: {this.displayTime(this.state.startTime)}</p>
                    <p>Останній рейс: {this.displayTime(this.state.endTime)}</p>
                    <p>Інтервал: {this.toTimePeriod(this.state.interval)}</p>
                    <div>Очікуйте наступний транспорт в такий час: <br/>{listStopTimes}</div>
                </div>
            )
        }




    }


}