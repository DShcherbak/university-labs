import React from "react";
import {Redirect} from "react-router-dom";
import * as API from "../services/API";
import { withRouter } from 'react-router-dom';
import TimeTableForm from "../components/additional-components/TimeTableForm";
import NavBar from "../components/nav-bar";
import Loading from "../components/loading";
import styles from "../styles/General.module.css"



export class EmployeeObject extends React.Component{
    constructor(props) {
        super(props);
        this.state = {
            counted: false
        }
    }


    getRouteId(url){
        let id = url.lastIndexOf('=')
        let numberStr = url.substring(id + 1)
        return parseInt(numberStr)
    }

    componentDidMount = () => {
        let number = this.getRouteId(window.location.href)
        console.log("Employee number " + number)
        this.GetEmployee(number).then((employee) => {
            if(employee === undefined){
                this.setState({
                    incorrectRoute: true,
                    counted: true
                })
            } else {
                let routeId = employee.routeId
                console.log("Route id " + routeId)
                this.GetRoute(routeId).then((route) => {
                    console.log(route)
                    if(route === undefined){
                        this.setState({
                            incorrectRoute: true,
                            counted: true
                        })
                    } else {
                        this.setState({
                            id: employee.id,
                            name: employee.name,
                            surname: employee.surname,
                            routeNumber: route.routeNumber,
                            routeType : this.GetType(route.routeType),
                            routeId : route.id,
                            counted : true
                        }, function () {
                            console.log("ST: " + this.state.startTime)
                        })
                    }
                })

            }

        }).catch((error) => {
            console.log(error);
        });

    }

    GetType(number){
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

    async GetEmployee(number) {
        return await API.getEmployee(number)
    }

    async GetRoute(id){
        return await API.getRouteById(id)
    }

    render(){

        if(this.state === undefined || this.state.counted === false){
            return <Loading/>
        }

        if(this.state.incorrectRoute){
            return (
                <div>
                    <h1>Працівника не знайдено.</h1>
                </div>
            )
        }


        return (
            <div>
                <NavBar fatherlink={'/employees'}/>
                <div className={styles.MainBodyContainer}>
                    <p>Ім'я:  {this.state.name}</p>
                    <p>Прізвище:  {this.state.surname}</p>
                    <p>Транспорт: {this.state.routeType} номер {this.state.routeNumber}</p>
                </div>

            </div>
        )


    }


}