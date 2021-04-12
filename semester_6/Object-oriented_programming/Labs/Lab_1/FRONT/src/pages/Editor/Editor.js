import React from "react";
//import * as API from  "API.js"
/* We simply can use an array and loop and print each user */
import styles from "../../styles/General.module.css"
import {Link} from 'react-router-dom';
import NavBar from "../../components/nav-bar";
import * as API from "../../services/API";
import Loading from "../../components/loading";
import Redirect from "react-router-dom/es/Redirect";
import Keycloak from 'keycloak-js';
import UserService from "../../services/UserService";


export class Editor extends React.Component{

    constructor() {
        super();
        this.setState({
            adminChecked : false,
            isAdmin: false,
            keycloak: null, authenticated: false
        })
    }
    componentDidMount() {
            this.setState({
                adminChecked : true,
                isAdmin: false
            })
    }

    render(){
        if(UserService.isAdmin()){
            return(
                <div>
                    <NavBar fatherlink = {'/'}/>
                    <div className={styles.BigButtonContainer}>
                        <Link to={'/edit/routes'}><button className={styles.BigButton} >Редагувати <br/> маршрути</button></Link>
                        <Link to={'/edit/stops'}><button className={styles.BigButton} >Редагувати <br/> зупинки</button></Link>
                        <Link to={'/edit/employees'}><button className={styles.BigButton} >Редагувати <br/> працівників</button></Link>
                    </div>
                </div>
            );
        } else {
            return (<Redirect to={'/'}/>)
        }
    }
}
/*
export function Editor(){
    const history = useHistory();

    const goToRoutes = () =>{
        let path = '/edit/routes';
        history.push(path);
    }

    const goToTimeTables = () =>{
        let path = '/edit/stops';
        history.push(path);
    }



}*/