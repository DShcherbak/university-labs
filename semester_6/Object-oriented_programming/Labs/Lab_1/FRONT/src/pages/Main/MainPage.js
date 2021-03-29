import React from "react";
//import * as API from  "API.js"
/* We simply can use an array and loop and print each user */
import styles from "./MainPage.module.css"
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
                        <div className={styles.container}>
                            <Link to={'/routes'}><button className={styles.MainPageButton}> Маршрути</button></Link>
                            <Link to={'/timetables'}><button className={styles.MainPageButton} > Розклади</button></Link>
                            <Link to={'/employees'}><button className={styles.MainPageButton} > Працівники</button></Link>
                        </div>
                    </div>)
        } else {
            return (
                <div>
                    <NavBar fatherlink={''}/>
                    <div className={styles.container}>
                        <Link to={'/routes'}><button className={styles.MainPageButton}> Маршрути</button></Link>
                        <Link to={'/timetables'}><button className={styles.MainPageButton} > Розклади</button></Link>
                        <Link to={'/employees'}><button className={styles.MainPageButton} > Працівники</button></Link>
                        <Link to={'/editor'}><button className={styles.MainPageButton} > Сторінка адміністратора</button></Link>
                    </div>
                </div>
            );
        }
    }
}