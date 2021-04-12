import React from "react";
//import * as API from  "API.js"
/* We simply can use an array and loop and print each user */
import generalStyles from "../../styles/General.module.css"
import {Link} from 'react-router-dom';
import NavBar from "../../components/nav-bar";
import Loading from "../../components/loading";
import * as API from "../../services/API";
import RenderOnAuthenticated from "../../components/render-on-authentificated";

export class MainPage extends React.Component{

    constructor(props) {
        super(props);
        this.setState({
            adminChecked: false,
            isAdmin: false,
        }, function () {
            console.log("LOG0" + this.state.adminChecked + this.state.isAdmin)
        })
    }

    async isAdmin(){
        return await API.checkAdmin()
    }

    componentDidMount = () => {
        console.log("LOG4")
        this.isAdmin().then(result => {
            this.setState({
                adminChecked: true,
                isAdmin: result
            }, function () {
                if(!this.state.isAdmin)
                    console.log("Admin access denied")
            })
        })

        //console.log("LOG7" + this.state.adminChecked + this.state.isAdmin)

    }

    render() {
      /*  if (this.state === null || !this.state.adminChecked) {
            console.log("LOG")
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
           */
        let adminButton = RenderOnAuthenticated(<Link to={'/editor'}><button className={generalStyles.BigButton} > Сторінка<br/> адміністратора</button></Link>)
        return (
                <div>
                    <NavBar fatherlink={''}/>
                    <div className={generalStyles.BigButtonContainer}>
                        <Link to={'/routes'}><button className={generalStyles.BigButton}> Маршрути</button></Link>
                        <Link to={'/timetables'}><button className={generalStyles.BigButton} > Розклади</button></Link>
                        <Link to={'/employees'}><button className={generalStyles.BigButton} > Працівники</button></Link>
                        {adminButton}
                    </div>
                </div>
            );
     //   }
    }
}