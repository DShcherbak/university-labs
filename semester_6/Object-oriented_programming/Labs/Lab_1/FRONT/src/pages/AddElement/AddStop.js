import React from "react";
import {Link, Redirect} from "react-router-dom";
import * as API from "../../API";
import { confirmAlert } from 'react-confirm-alert'; // Import
import TimeTableForm from "../../components/additional-components/TimeTableForm";


export class AddStop extends React.Component{
    constructor(props) {
        super(props);
        this.state = {
            name: "Безіменна",
            oldId : 0,
            number: 0,
            startTime: "06:00",
            endTime: "23:30",
            interval: 10,
            type: 'Тролейбус',
            timeTable : [],
            stops: [],
        }
        this.handleInputChange = this.handleInputChange.bind(this);
        this.addStop = this.addStop.bind(this);
        this.removeStop = this.removeStop.bind(this);
        this.saveAndContinue = this.saveAndContinue.bind(this);
        this.saveAndExit = this.saveAndExit.bind(this);
    }

    handleInputChange(event) {
        const target = event.target;
        const value = target.type === 'checkbox' ? target.checked : target.value;
        const name = target.name;
        this.setState({
            [name]: value
        });
    }



    componentDidMount = () => {

        this.GetStops().then((stops) => {
            this.setState({
                allStops: stops
            }, function () {
                console.log("ST: " + this.state.startTime)
            })

        }).catch((error) => {
            console.log(error);
        });
    }


    async GetStops() {
        return await API.getStops()
    }

    async saveChanges() {
        let newNumber = this.mex()
        this.setState({
            oldId : 0,
            id : newNumber
        })
        let isAvailable = this.isNameAvailable(this.state.name)
        if (isAvailable) {
            let newStop = await API.updateStop(this.state)
            this.state.name = newStop[newNumber].stop_name
        } else {
            alert("Зупинка з назвою " + this.state.name + " вже існує!")
        }
    }

    reload(){

    }

    addStop(){
        let newStop = this.state.allStops[0].stop_name
        let oldStops = this.state.stops.concat(newStop)
        let newTimetable = this.state.timeTable.concat([5.0])
        this.setState({
            stops:oldStops,
            timeTable:newTimetable
        })
    }

    removeStop(){
        let oldStops = this.state.stops
        if(oldStops.length > 0){
            oldStops.pop()
            let newTimetable = this.state.timeTable
            newTimetable.pop()
            this.setState({
                stops:oldStops,
                timeTable:newTimetable
            })
        }
    }

    async saveAndContinue() {
        await this.saveChanges()
        this.reload()
    }

    async saveAndExit(){
        await this.saveChanges()
        this.setState(
            {returnToEditor : true}
        )

    }

    render(){
        if(this.state.returnToEditor){
            return (
                <Redirect to={'/edit/stops'}/>
            )
        }
        return (
            <div>
                <Link to={"/edit/stops"}>
                    <button>Назад</button>
                </Link>

                <form>
                    <label>{"Реєстрація нової зупинки"}</label><br/>
                    <label>Вигадайте унікальне ім'я для нової зупинки: </label><input type="text" value={this.state.name} name="number" onChange={this.handleInputChange}/><br/>

                    <input type="button" onClick={this.saveAndContinue} value="Зберегти та додати наступний"/>
                    <input type="button" onClick={this.saveAndExit} value="Зберегти та вийти"/>
                </form>
            </div>

        )


    }


}