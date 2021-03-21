import React from "react";

export class RouteObject extends React.Component{

    constructor(props) {
        super(props);
        this.routeNumber = props.routeProps["routeId"]
        this.routeMap = props.routeProps["stops"]
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
        this.routeMap.forEach(key => {
            if(prevStop !== "-"){
                list.push(<li key = {++id}>{prevStop} => {key}</li>);/* :: {value}*/
            }
            prevStop = key;
        });
        return(
            <div>I'm a route number {this.routeNumber} and I go like this:
                {<ul>{list}</ul>}
            </div>
        );
    }

}