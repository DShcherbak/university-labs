

// src/components/nav-bar.js

import React from "react";

import MainNav from "./main-nav";
import AuthNav from "./auth-nav";
import styles from "./Navbar.module.css"
import {Link} from "react-router-dom";
import * as API from "../API"
import {Email} from "./email";

const NavBar = (props) => {
    let prevButton = <button>Назад</button>
    if(props.fatherlink === ''){
        prevButton = <button className={styles.invisible}>Назад</button>
    } else {
        prevButton = <button className={styles.backButton}>Назад</button>
    }
    Email();
  return (
    <div className="nav-container mb-3">
      <nav className="navbar navbar-expand-md navbar-light bg-light">
        <div className={styles.container}>
            <Link to={props.fatherlink}>{prevButton}</Link>
            <div className={styles.logo} ><MainNav /></div>
          <AuthNav />
        </div>
      </nav>
    </div>
  );
};

const MainPageNavBar = () => {
    return (
        <div className="nav-container mb-3">
            <nav className="navbar navbar-expand-md navbar-light bg-light">
                <div className="container">
                    <div className="navbar-brand logo" />
                    <AuthNav />
                </div>
            </nav>
        </div>
    );
};

export default NavBar;


