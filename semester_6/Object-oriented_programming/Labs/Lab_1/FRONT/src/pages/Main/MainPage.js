import React from "react";
//import * as API from  "API.js"
/* We simply can use an array and loop and print each user */
import styles from "./MainPage.module.css"
import { useHistory } from 'react-router-dom';



function MainPage(){
    const history = useHistory();

    const goToRoutes = () =>{
        let path = '/routes';
        history.push(path);
    }

    const goToTimeTables = () =>{
        let path = '/timetables';
        history.push(path);
    }

    const goToEdit = () =>{
        let path = '/editor';
        history.push(path);
    }

        return (
            <div className={styles.container}>
                <button className={styles.MainPageButton} onClick={goToRoutes}> Маршрути</button>
                <button className={styles.MainPageButton} onClick={goToTimeTables}> Розклади</button>
                <button className={styles.MainPageButton} onClick={goToEdit}> Сторінка адміністратора </button>
            </div>
        );

}

export default MainPage;