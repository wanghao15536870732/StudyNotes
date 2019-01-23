
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class Weather extends StatelessWidget{
  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      title: 'Flutter Weather',
      theme: new ThemeData(
        primarySwatch: Colors.pink
      ),
      home: new Center(
        child: new WeatherPage(),
      ),
    );
  }
}

class WeatherPage extends StatefulWidget{
  WeatherPage({Key key}):super(key:key);

  _WeatherPage createState() => _WeatherPage();
}

class _WeatherPage extends State<WeatherPage>{
  @override
  Widget build(BuildContext context) {
    return new Scaffold(
      appBar: new AppBar(
        title: new Text('Flutter Weather'),
      ),
      body: new Stack(
        fit: StackFit.expand,
        children: <Widget>[
          new Image.asset("images/weather_bg.jpg",fit: BoxFit.fitHeight),
          new Column(
            mainAxisAlignment: MainAxisAlignment.start, //垂直布局
            crossAxisAlignment: CrossAxisAlignment.center,  //水平布局
            children: <Widget>[
              new Container(
                width: double.infinity,
                margin: EdgeInsets.only(top: 40.0),
                child: new Text(
                  "邢台市",
                  textAlign: TextAlign.center,
                  style: new TextStyle(
                    color: Colors.white,
                    fontSize: 30.0,
                  ),
                ),
              ),
              new Container(
                width: double.infinity,
                margin: EdgeInsets.only(top: 100.0),
                child: new Column(
                  children: <Widget>[
                    new Text(
                      "20 °",
                      style: new TextStyle(
                        color: Colors.white,
                        fontSize: 80.0
                      ),
                    ),
                    new Text(
                      "晴",
                      style: new TextStyle(
                        color: Colors.white,
                        fontSize: 45.0,
                      ),
                    ),
                    new Text(
                      "湿度  80%",
                      style: new TextStyle(
                        color: Colors.white,
                        fontSize: 30.0,
                      ),
                    )
                  ],
                ),
              )
            ],
          )
        ],
      )
    );
  }
}