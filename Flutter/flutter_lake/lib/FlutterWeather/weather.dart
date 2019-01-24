
import 'dart:convert';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter_lake/FlutterWeather/CityWidget.dart';
import 'package:flutter_lake/FlutterWeather/WeatherData.dart';
import 'package:flutter_lake/FlutterWeather/WeatherWidget.dart';

void main(){
  setCustomErrorPage();
  runApp(Weather());
}

void setCustomErrorPage(){
  ErrorWidget.builder = (FlutterErrorDetails flutterErrorDetails){
    print(flutterErrorDetails.toString());
    return Center(
      child: Text("Flutter 走神了"),
    );
  };
}


class Weather extends StatelessWidget{

  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      title: 'Flutter Weather',
      theme: new ThemeData(
        primarySwatch: Colors.blue
      ),
      home: Scaffold(
        appBar: new AppBar(
          title: new Text('Select City'),
        ),
        body: CityWidget(),
      )
    );
  }
}
