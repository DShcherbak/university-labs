import React from "react";

export class RouteObject extends React.Component{

    constructor(props) {
        super(props);
        this.routeMap = props.route
        this.myNumber = props.number
    }
    /*
    const object = {'a': 1, 'b': 2, 'c' : 3};
for (const [key, value] of Object.entries(object)) {
  console.log(key, value);
}
     */

    render(){
        let prevStop = "-";
        let list = []
        let id = 0;
        this.routeMap.forEach((value, key) => {
            if(prevStop !== "-"){
                list.push(<li key = {++id}>{prevStop} => {key} :: {value}</li>);
            }
            prevStop = key;
        });
        return(
            <div>I'm a route number {this.myNumber} and I go like this:
                {<ul>{list}</ul>}
            </div>
        );
    }

}