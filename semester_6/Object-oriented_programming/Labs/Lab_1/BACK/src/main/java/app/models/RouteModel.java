package app.models;

public class RouteModel {
    int routeId;
    public Object[] stops;
    String startTime;
    String endTime;
    int interval;
    int type;

    public RouteModel(int _id, Object[] _stops, String _startTime, String _endTime, int _interval, int _type){
        routeId = _id;
        stops = _stops;
        startTime = _startTime;
        endTime = _endTime;
        interval = _interval;
        type = _type;
    }
}
