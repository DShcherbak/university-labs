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
        console.log("SUKA")
        console.log(this.routeMap)
        let list = []
        let id = 0;
        this.routeMap.forEach(key => {
            list.push(<li key = {++id}>{key}</li>);
        });
        return(
            <div>I'm a route number {this.routeNumber} and I go like this:
                {<ul>{list}</ul>}
            </div>
        );
    }

}