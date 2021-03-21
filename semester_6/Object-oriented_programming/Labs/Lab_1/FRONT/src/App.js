import React, { Component } from "react";
//Import all needed Component for this tutorial
import {
    BrowserRouter as Router,
    Route,
    Switch,
    Link,
    Redirect
} from "react-router-dom";

//Pages
import MainPage from "./pages/Main/MainPage.js";
import Routes from "./pages/Routes/Routes.js";
import {GeneralTimeTables} from "./pages/TimeTables/TimeTables";
import Stations from "./pages/Stations/Stations.js";
import { useAuth0 } from "@auth0/auth0-react";

import { NavBar, Footer, Loading } from "./components";
import Editor from "./pages/Editor/Editor";

//import "./app.css";

const App = () => {
    const { isLoading } = useAuth0();

    if (isLoading) {
        return <Loading />;
    }

    return (
        <div id="app" className="d-flex flex-column h-100">
            <div className="container flex-grow-1">
                <Switch>
                    <Route exact path="/" component={MainPage} />
                    <Route exact path="/routes" component={Routes} />
                    <Route path="/timetables" component={GeneralTimeTables} />
                    <Route exact path="/editor" component={Editor} />
                </Switch>
            </div>
            <Footer />
        </div>
    );
};

export default App;

///< index.jsx will be automatically imported
//And render that route with the MainPage component for the root path /
/*
class App extends Component {
    render() {
        return (
            <Router>

            </Router>
        );
    }
}

export default App;*/