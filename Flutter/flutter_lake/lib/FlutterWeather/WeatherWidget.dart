

import 'dart:convert';

import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter_lake/FlutterWeather/DressingData.dart';
import 'package:flutter_lake/FlutterWeather/WeatherData.dart';
import 'package:http/http.dart' as http;

class WeatherWidget extends StatefulWidget{

  String cityName;

  WeatherWidget(this.cityName);

  @override
  State<StatefulWidget> createState() {
    // TODO: implement createState
    return new WeatherState(this.cityName);
  }
}
class WeatherState extends State<WeatherWidget>{

  String cityName;

  WeatherData weather = WeatherData.empty();
  DressingData weatherLife = DressingData.empty();

  WeatherState(String cityName){
    this.cityName = cityName;
    _getWeather();
  }

  void _getWeather() async{
    WeatherData data = await _fetchWeather();
    DressingData dataLife = await _fetchWeatherLife();
    setState((){
      weather = data;
      weatherLife = dataLife;
    });
  }

  Future<WeatherData> _fetchWeather() async{
    final response = await http.get(
        'https://free-api.heweather.com/s6/weather/now?location='+
            cityName +
            '&key=551f547c64b24816acfed8471215cd0e'
    );
    if(response.statusCode == 200){
      return WeatherData.fromJson(json.decode(response.body));
    }else{
      return WeatherData.empty();
    }
  }

  Future<DressingData> _fetchWeatherLife() async{
    final response = await http.get(
      'https://free-api.heweather.net/s6/weather/lifestyle?parameters&location=' +
          cityName +
          '&key=551f547c64b24816acfed8471215cd0e'
    );
    if(response.statusCode == 200){
      return DressingData.fromJson(json.decode(response.body));
    }else{
      return DressingData.empty();
    }
  }

  @override
  Widget build(BuildContext context) {
    return new Scaffold(
        appBar: new AppBar(
          title: new Text('Flutter Weather'),
        ),
        body: new Stack(
          fit: StackFit.expand,
          children: <Widget>[
            new Image.asset("images/weather_bg.jpg",fit: BoxFit.fill),
            new Column(
              mainAxisAlignment: MainAxisAlignment.start, //垂直布局
              crossAxisAlignment: CrossAxisAlignment.center,  //水平布局
              children: <Widget>[
                new Container(
                  width: double.infinity,
                  margin: EdgeInsets.only(top: 45.0),
                  child: new Text(
                    this.cityName +  'images/'+ weather?.code + '.png',
                    textAlign: TextAlign.center,
                    style: new TextStyle(
                      color: Colors.white,
                      fontSize: 30.0,
                    ),
                  ),
                ),
                new Container(
                  width: double.infinity,
                  margin: EdgeInsets.only(top: 60.0),
                  child: new Column(
                    children: <Widget>[
                      new Image.asset( //定义图片的高宽度
                        'images/'+ weather?.code + '.png',
                        width: 100.0,
                        height: 100.0,
                        fit: BoxFit.fill,
                      ),
                      new Text(
                        weather?.tmp,
                        style: new TextStyle(
                            color: Colors.white,
                            fontSize: 80.0
                        ),
                      ),
                      new Text(
                        weather?.cond,
                        style: new TextStyle(
                          color: Colors.white,
                          fontSize: 45.0,
                        ),
                      ),
                      new Text(
                        weather?.hum,
                        style: new TextStyle(
                          color: Colors.white,
                          fontSize: 30.0,
                        ),
                      ),
                      new Text(
                        weatherLife?.weatherDet,
                        style: new TextStyle(
                          color: Colors.white,
                          fontSize: 15.0,
                        ),
                      ),
                      new Text(
                        weatherLife?.weatherSug,
                        style: new TextStyle(
                          color: Colors.white,
                          fontSize: 15.0,
                        ),
                      ),
                      new Text(
                        weatherLife?.weatherFlu,
                        style: new TextStyle(
                          color: Colors.white,
                          fontSize: 15.0,
                        ),
                      ),
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