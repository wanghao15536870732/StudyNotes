
import 'dart:convert';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter_lake/FlutterWeather/CityData.dart';
import 'package:flutter_lake/FlutterWeather/WeatherWidget.dart';
import 'package:http/http.dart' as http;

class CityWidget extends StatefulWidget{
  @override
  State<StatefulWidget> createState() {
    // TODO: implement createState
    return CityState();
  }
}

class CityState extends State<CityWidget>{

  //列表显示
  List<CityData> cityList = new List<CityData>();

  CityState(){
    _getCityList(); //获取城市列表
  }

  void _getCityList() async{
    List<CityData> citys = await _fetchCityList();
    setState(() {
      cityList = citys;
    });
  }

  Future<List<CityData>> _fetchCityList() async{
    final response = await http.get('https://search.heweather.net/top?group=cn&key=551f547c64b24816acfed8471215cd0e');

    List<CityData> cityList = new List<CityData>();

    if(response.statusCode == 200){
      //解析数据
      Map<String,dynamic> result = json.decode(response.body);
      for(dynamic data in result['HeWeather6'][0]['basic']) {
        CityData cityData = CityData(data['location']);
        cityList.add(cityData);
      }
      return cityList;
    }else{
      return cityList;
    }
  }

  @override
  Widget build(BuildContext context) {
    return ListView.builder(
      itemCount: cityList.length,
      itemBuilder: (context,index){
        return ListTile(
          title: GestureDetector(
            child: Text(cityList[index].cityName),
            onTap: (){
              Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) => WeatherWidget(cityList[index].cityName)),
              );
            },
          ),
        );
      },
    );
  }
}
