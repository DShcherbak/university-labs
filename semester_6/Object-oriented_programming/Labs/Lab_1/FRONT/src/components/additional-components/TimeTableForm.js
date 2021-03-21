import React, { Component } from 'react';
import { Redirect } from 'react-router-dom'
import { withRouter } from 'react-router-dom'; // <--- import `withRouter`. We will use this in the bottom of our file.

class TimeTableForm extends Component {

    constructor(props) {
        super(props);
        if(props.currentId === undefined)
            props.currentId = 1
        this.state = {
            newRouteId: props.currentId
        }
        this.handleChange = this.handleChange.bind(this);
        this.handleSubmit = this.handleSubmit.bind(this);
    }

    handleChange(event) {
        this.setState({newRouteId: event.target.value});
    }

    handleSubmit (e) {
        return <Redirect to='/routes'/> // <--- The page you want to redirect your user to.
        //this.props.history.push('/routes'); // <--- The page you want to redirect your user to.
    }

    render() {
        return (
            <div>
                <form onSubmit={this.handleSubmit}>
                    <label>Номер маршруту: </label> <input type = "number" value = {this.state.newRouteId} onChange={this.handleChange} name="newRouteId"/>
                    <button type="submit">Submit</button>
                </form>
            </div>
        );
    }
}

export default withRouter(TimeTableForm); // <--- make sure to wrap your component with `withRouter()`