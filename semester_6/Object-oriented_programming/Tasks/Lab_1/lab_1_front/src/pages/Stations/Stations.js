import React from "react";
//import * as API from  "API.js"
/* We simply can use an array and loop and print each user */
import styles from "./Stations.module.css"



class Stations extends React.Component {

    render() {
        return (
            <div className={styles.container}>
                <button className={styles.MainPageButton}> Маршрут 1</button>
                <button className={styles.MainPageButton}> Маршрут 2</button>
                <button className={styles.MainPageButton}> Маршрут 3</button>
                <button className={styles.MainPageButton}> Маршрут 4</button>
            </div>


        );
    }
}

export default Stations;