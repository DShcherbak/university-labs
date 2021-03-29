import React from "react";
//import * as API from  "API.js"
/* We simply can use an array and loop and print each user */
import generalStyles from "../../styles/General.module.css"
import {Link} from 'react-router-dom';
import NavBar from "../../components/nav-bar";
import Loading from "../../components/loading";
import * as API from "../../API";

export class MainPage extends React.Component{

    constructor(props) {
        super(props);
        this.state ={
            adminChecked: false,
            isAdmin: false,
        }
    }

    async isAdmin(){
        return await API.checkAdmin()
    }

    componentDidMount = () => {
        this.isAdmin().then(result => {
            this.setState({
                adminChecked: true,
                isAdmin: result["isAdmin"]
            })
        })
    }

    render() {
        if (this.state === null || !this.state.adminChecked) {
            return (
                <Loading/>
            );
        } else if (!this.state.isAdmin) {
            return (<div>
                        <NavBar fatherlink={''}/>
                        <div className={generalStyles.BigButtonContainer}>
                            <Link to={'/routes'}><button className={generalStyles.BigButton}> Маршрути</button></Link>
                            <Link to={'/timetables'}><button className={generalStyles.BigButton} > Розклади</button></Link>
                            <Link to={'/employees'}><button className={generalStyles.BigButton} > Працівники</button></Link>
                        </div>
                    </div>)
        } else {
            return (
                <div>
                    <NavBar fatherlink={''}/>
                    <div className={generalStyles.BigButtonContainer}>
                        <Link to={'/routes'}><button className={generalStyles.BigButton}> Маршрути</button></Link>
                        <Link to={'/timetables'}><button className={generalStyles.BigButton} > Розклади</button></Link>
                        <Link to={'/employees'}><button className={generalStyles.BigButton} > Працівники</button></Link>
                        <Link to={'/editor'}><button className={generalStyles.BigButton} > Сторінка<br/> адміністратора</button></Link>
                    </div>
                </div>
            );
        }
    }
}