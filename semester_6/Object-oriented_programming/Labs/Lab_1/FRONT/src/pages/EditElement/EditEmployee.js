import React from "react";
import {Redirect} from "react-router-dom";
import * as API from "../../services/API";
import NavBar from "../../components/nav-bar";
import Loading from "../../components/loading";
import styles from "../../styles/General.module.css";
import UserService from "../../services/UserService";

export class EditEmployee extends React.Component{

    componentDidMount = () => {}

    render() {
        if(!UserService.isAdmin()){
            return (<Redirect to={'/'}/>)
        } else {
            return <EditEmployeeInternal/>
        }
    }
}

export class EditEmployeeInternal extends React.Component{
    constructor(props) {
        super(props);
        let id = this.getEmployeeId(window.location.href)
        this.state = {
            id: id,
            name: ""
        }
        this.handleInputChange = this.handleInputChange.bind(this);
        this.resetForm = this.resetForm.bind(this);
        this.deleteElement = this.deleteElement.bind(this);
        this.confirmedDelete = this.confirmedDelete.bind(this);
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

    getEmployeeId(url){
        let id = url.lastIndexOf('=')
        let numberStr = url.substring(id + 1)
        return parseInt(numberStr)
    }

    resetValues(employee){
        console.log(employee)
        this.setState({
            id : employee.id,
            name: employee.name,
            surname: employee.surname,
            route_number: employee.routeId,
            incorrectRoute : false,
            returnToEditor: false,
            confirmDelete : false,
        }, function () {
            console.log("ST: " + this.state.id)
        })
    }

    componentDidMount = () => {
        this.resetForm()
    }

    async GetEmployee() {
        return (await API.getEmployee(this.state.id))
    }

    async GetRoute(id) {
        return (await API.getRouteById(id))
    }

    resetForm(){
        this.GetEmployee().then((employee) => {
            if(employee === undefined){
                this.setState({
                    incorrectRoute: true
                })
            } else {
                this.GetRoute(employee.routeId).then((route => {
                    if(route === undefined){
                        this.setState({
                            incorrectRoute: true
                        })
                    } else {
                        employee.routeId = route.routeNumber
                        this.resetValues(employee)
                    }
                }))
            }
        }).catch((error) => {
            console.log(error);
        });

    }

    deleteElement(){
        this.setState({
            confirmDelete : true
        })
    };

    async confirmedDelete(){
        this.setState({
            returnToEditor : true
        })
        API.deleteEmployee(this.state.id)
    };

    async saveChanges() {
        let result = await API.updateEmployee(this.state)
        if(result === undefined){
            alert("Введений номер маршруту є недійсним!")
            return false
        }
        return true
    }

    async saveAndContinue(){
        await this.saveChanges()
    }

    async saveAndExit(){
        if(await this.saveChanges()){
            this.setState(
                {returnToEditor : true}
            )
        }
    }

    render(){
        if(!UserService.isAdmin()){
            alert("You have no admin rights!")
            return (<Redirect to={'/'}/>)
        }
        if(this.state.returnToEditor){
            return (
                <Redirect to={'/edit/employees'}/>
            )
        }
        if(this.state.confirmDelete){
            return (
                <div>
                    <NavBar fatherlink={'/edit/employees'}/>
                    <form>
                        <label>{"Підтвердження видалення працівника \"" + this.state.name + " " + this.state.surname +  "\""}</label><br/>
                        <input type="button" onClick={this.resetForm} value="Скасувати видалення"/>
                        <input type="button" onClick={this.confirmedDelete} value="Видалити елемент"/>
                    </form>
                </div>
            )
        }
        if(this.state.incorrectRoute){
            return (
                <div>
                    <NavBar fatherlink={'/edit/employees'}/>
                    <h1>Працівника не знайдено.</h1>
                </div>
            )
        }

        return (
            <div>
                <NavBar fatherlink={'/edit/employees'}/>
                <div className={styles.MainFormContainer}>
                    <form className={styles.editForm}>
                        <label><b>{"Редагування працівника"}</b></label><br/>
                        <label>Ім'я: </label><input type="text" className={styles.wideFromInput} value={this.state.name} name="name" onChange={this.handleInputChange}/><br/>
                        <label>Прізвище: </label><input type="text" className={styles.wideFromInput} value={this.state.surname} name="surname" onChange={this.handleInputChange}/><br/>
                        <label>Номер маршруту: </label><input type="number" className={styles.wideFromInput} value={this.state.route_number} name="route_number" onChange={this.handleInputChange}/><br/>

                        <input type="button" onClick={this.resetForm} value="Скасувати зміни"/>
                        <input type="button" onClick={this.deleteElement} value="Видалити елемент"/>
                        <input type="button" onClick={this.saveAndContinue} value="Зберегти та продовжити"/>
                        <input type="button" onClick={this.saveAndExit} value="Зберегти та вийти"/>
                    </form>
                </div>
            </div>

        )


    }


}