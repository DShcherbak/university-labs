import React from "react";

export class TimeTableObject extends React.Component{
    constructor(props) {
        super(props);
        this.number = 145;
        this.startTime = 60*5 + 40;
        this.endTime = 24*60 + 20;
        this.interval = 10
        this.stops = new Map([["Station 1", 0], ["Station 2", 7], ["Station 4", 7]]);
    }

    getCurrentTime(){
        let timeStr = new Date().toLocaleString().split(",")[1]
        let result = parseInt(timeStr.split(':')[0]) * 60 + parseInt(timeStr.split(':')[1])
        let pm = timeStr.split(" ")[2]
        console.log("PM: " + pm)
        if(pm === "PM"){
            result += (12 * 60);
        }
        return result.toString()
    }

    toNormalTime(value){
        let hours = (Math.floor(value/60) % 24)
        return(Math.floor(hours/10)).toString() +
                ((hours) % 10).toString() +
                ":" +
                (Math.floor((value % 60)/10)).toString() +
                ((value % 60) % 10).toString();

    }

    toTimePeriod(value){
        if(value < 60){
            return value.toString() + " minutes.";
        } else {
            let hours = Math.floor(value/60).toString();
            value %= 60;
            return hours + "hours and " + value.toString() + " minutes.";
        }
    }

    countTimeToStops(){
        let timeToStops = new Map();

        let currentTime = this.getCurrentTime()
        let currentBus = this.endTime;

        console.log("DEBUG:");
        console.log("CurrentTime:" + currentTime);
        while(currentBus - this.interval > currentTime) currentBus-=this.interval;

        console.log("Current stops:" + this.stops);
        console.log("Current total:" + this.totalTime);

        while(currentBus + this.totalTime > currentTime){
            console.log("Current Bus:" + currentBus);
            let a = 0;
            for (let [key, value] of  this.stops.entries()) {
                a += value;
                console.log("Current stop:" + key + " new time: " + (currentBus + a - currentTime).toString());
                if(currentBus + a - currentTime  >= 0){
                    timeToStops.set(key, currentBus + a - currentTime);
                }

            }
            currentBus -= this.interval;
        }

        console.log("Size " + timeToStops.size)
        for (let [key, value] of  timeToStops.entries()) {
            console.log("Result: " + key + " :: " + value);
        }
        return timeToStops;
    }

    listTime(timeToStops){
        let list = []
        timeToStops.forEach((value, key) => list.push(<li>{key} | {value}</li>));
        return (
            <ul>{list}</ul>
        );
    }


    render(){
        this.totalTime = 0;

        this.stops.forEach((value, key) => this.totalTime += value);
        let currentTime = this.getCurrentTime();
        let timeToStops = this.countTimeToStops();
        let listStopTimes = this.listTime(timeToStops)
        return (
            <div>
                <p>Current time is {this.toNormalTime(currentTime)}</p>

                <p>Route number: {this.number}</p>
                <p>First departure at: {this.toNormalTime(this.startTime)}</p>
                <p>Last departure at: {this.toNormalTime(this.endTime)}</p>
                <p>Time between departures: {this.toTimePeriod(this.interval)}</p>
                <div>Next bus should appear in: <br/>{listStopTimes}</div>
            </div>
        )


    }


}