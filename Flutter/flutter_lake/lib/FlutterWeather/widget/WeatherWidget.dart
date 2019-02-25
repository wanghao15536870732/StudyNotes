
import 'dart:convert';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter_lake/FlutterWeather/data/DressingData.dart';
import 'package:flutter_lake/FlutterWeather/data/WeatherData.dart';
import 'package:flutter_lake/FlutterWeather/data/OneData.dart';
import 'package:flutter_lake/FlutterWeather/data/WeekData.dart';
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
  //主要的天气
  WeatherData weather = WeatherData.empty();
  //天气指数
  DressingData weatherLife = DressingData.empty();

  //未来7天的天气
  WeekData weekData = WeekData.empty();

  WeatherState(String cityName){
    this.cityName = cityName;
    _getWeather();
  }

  void _getWeather() async{
    WeatherData data = await _fetchWeather();
    DressingData dataLife = await _fetchWeatherLife();
//    WeekData dataWeek = await _fetchWeekWeather();
    setState((){
      weather = data;
      weatherLife = dataLife;
//      weekData = dataWeek;
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

  Future<WeekData> _fetchWeekWeather() async{
    final response = await http.get(
      'https://free-api.heweather.net/s6/weather/forecast?parameters&location=' +
          cityName +
          '&key=551f547c64b24816acfed8471215cd0e'
    );

    if(response.statusCode == 200){
      WeekData weekData = WeekData.empty();
      for(int i = 0;i < 3;i++){
        OneData oneData = OneData.empty();
        oneData = OneData.fromJson(json.decode(response.body) + '[\'HeWeather6\'][0][\'daily_forecast\'][' + i + ']');
        weekData.OneData.add(oneData);
      }
      return weekData;
    }else{
      return WeekData.empty();
    }
  }

//
//  Widget buildFutureItem(String data,String weatherImg,String weather,String temp,String windair,String windsc){
//    return Container(
//      height: 160.0,
//      width: 115.0,
//      child: Column(
//        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
//        children: <Widget>[
//          Text(
//            data,
//            style: TextStyle(
//              fontSize: 20.0,
//              color: Color(0xFF333333),
//            ),
//          ),
//          Image.asset(
//            weatherImg,
//            width: 40.0,
//            height: 40.0,
//            fit: BoxFit.fill,
//          ),
//          Text(
//            weather,
//            style: TextStyle(
//              fontSize: 18.0,
//            ),
//          ),
//          Text(
//            temp,
//            style: TextStyle(
//              fontSize: 18.0,
//            ),
//          ),
//          Text(
//            windair,
//            style: TextStyle(
//              fontSize: 18.0,
//            ),
//          ),
//          Text(
//            windsc,
//            style: TextStyle(
//              fontSize: 14.0,
//              color: Colors.white,
//            ),
//          ),
//        ],
//      ),
//    );
//  }

  @override
  Widget build(BuildContext context) {

    //OneData oneData = weekData.OneData[0];

    Widget heaferSection = Container(
      margin: const EdgeInsets.all(20.0),
      child: Row(
        children: <Widget>[
          Image.asset(
            'images/'+ weather?.code + '.png',
            width: 100.0,
            height: 100.0,
            fit: BoxFit.cover,
          ),
          Expanded(
            child: Column(
              children: <Widget>[
                new Text(
                  this.cityName,
                  style: new TextStyle(
                    fontSize: 24.0,
                      color: Color(0xFF707070)
                  ),
                ),

                new Text(
                    weather?.cond,
                  style: new TextStyle(
                    fontSize: 18.0, color: Color(0xFF707070)
                  ),
                )
              ],
            ),
          ),
          Container(
            width: 80.0,
            height: 80.0,
          )
        ],
      ),
    );

    Widget tempSection = Center(
      child: Stack(
        children: <Widget>[
          Align(
            alignment: FractionalOffset(0.5, 0.5),
            child: new Text(
              weather.tmp,
              style: new TextStyle(
                fontSize: 120.0,
                fontFamily: 'AdobeClean',
              ),
            ),
          ),
          Align(
            alignment: FractionalOffset(0.7, 0.0),
            child: new Text(
              '℃',
              style: new TextStyle(
                fontSize: 30.0,
                color: Color(0xFF707070)
              ),
            ),
          )
        ],
      ),
    );

    Widget detailSection = Container(
      child: Center(
        child: new Text(
          weather.time + ' 发布',
          style: new TextStyle(
            fontSize: 16.0,
          ),
        ),
      ),
    );

    Row buildWeatherItem(String icon,String text){
      return Row(
        children: <Widget>[
          Image.asset(
            icon,
            width: 30.0,
            height: 30.0,
            fit: BoxFit.cover,
          ),
          new Text(
              text,
            style: new TextStyle(
              fontSize: 16.0
            ),
          ),
        ],
      );
    }

    Widget itemSection = Container(
      margin: EdgeInsets.only(top: 15.0),
      child: Row(
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        children: <Widget>[
          buildWeatherItem('images/weather_wind.png',weather.wind),
          buildWeatherItem('images/weather_hum.png',weather.hum),
          buildWeatherItem('images/weather_visual.png',weather.length + '公里'),
        ],
      ),
    );

    Widget bottomSection = Column(
      children: <Widget>[
        itemSection,
        Divider(
          height: 1.0,
          color: Colors.black,
        )
      ],
    );


    Widget middleSection = Container(
      child: Column(
        children: <Widget>[
          tempSection,
          detailSection
        ],
      ),
    );

    Row buildDressItem(String icon,String text){
      return Row(
        children: <Widget>[
          Image.asset(
            icon,
            width: 40.0,
            height: 40.0,
            fit: BoxFit.cover,
          ),
          new Text(
              text,
            softWrap: true,
            maxLines: 2,
            style: new TextStyle(
              fontSize: 16.0,
              color: Color(0xFF333333)
            ),
          )
        ],
      );
    }


    Widget dressSection = Container(
      margin: EdgeInsets.only(top: 15.0),
      child: new Column(
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        children: <Widget>[
          buildDressItem('images/weatherComf.png', weatherLife?.weatherComf),
          buildDressItem('images/weatherDrsg.png', weatherLife.weatherDrsg),
          buildDressItem('images/weatherComf.png', weatherLife.weatherDet),
          buildDressItem('images/weatherSug.png', weatherLife.weatherSug),
          buildDressItem('images/weatherFlu.png', weatherLife.weatherFlu),
          buildDressItem('images/weatherSpo.png', weatherLife.weatherSpo),
          buildDressItem('images/weatherTra.png', weatherLife.weatherTra),
          buildDressItem('images/weatherUv.png', weatherLife.weatherUv),
          buildDressItem('images/weatherCw.png', weatherLife.weatherCw),
          buildDressItem('images/weatherAir.png', weatherLife.weatherAir),
        ],
      ),
    );

    return new Scaffold(
        appBar: new AppBar(
          title: new Text('Flutter Weather'),
        ),
        body: new Stack(
          fit: StackFit.expand,
          children: <Widget>[
//            new Image.asset("images/weather_bg.jpg",fit: BoxFit.fill),
            new Column(
              mainAxisAlignment: MainAxisAlignment.start, //垂直布局
              crossAxisAlignment: CrossAxisAlignment.center,  //水平布局
              children: <Widget>[
                new Container(
                  width: double.infinity,
                  margin: EdgeInsets.only(top: 10.0),
                  child: new Column(
                    children: <Widget>[
                      heaferSection,
                      middleSection,
                      bottomSection,
                      dressSection,
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



