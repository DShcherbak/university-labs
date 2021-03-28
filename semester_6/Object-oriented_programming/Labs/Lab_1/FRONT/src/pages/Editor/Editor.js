import React from "react";
//import * as API from  "API.js"
/* We simply can use an array and loop and print each user */
import styles from "./Editor.module.css"
import { useHistory } from 'react-router-dom';

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

    return (
        <div className={styles.container}>
            <button className={styles.MainPageButton} onClick={goToRoutes}>Редагувати маршрути</button>
            <button className={styles.MainPageButton} onClick={goToTimeTables}>Редагувати зупинки</button>
        </div>
    );

}