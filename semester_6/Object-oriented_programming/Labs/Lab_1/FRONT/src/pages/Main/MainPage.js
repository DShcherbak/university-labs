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

    const goToStations = () =>{
        let path = '/stations';
        history.push(path);
    }

        return (
            <div className={styles.container}>
                <button className={styles.MainPageButton} onClick={goToRoutes}> Маршрути</button>
                <button className={styles.MainPageButton} onClick={goToTimeTables}> Розклади</button>
                <button className={styles.MainPageButton} onClick={goToStations}> Коли буде мій транспорт?</button>
                <button className={styles.MainPageButton}> Побудувати маршрут</button>
            </div>
        );

}

export default MainPage;