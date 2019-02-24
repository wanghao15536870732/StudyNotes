
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

  void _getCityList() async{  //async关键字声明该函数内部有代码需要延迟执行
    List<CityData> citys = await _fetchCityList();  //await关键字声明运算为延迟执行，然后return运算结果
    setState(() {
      cityList = citys;
    });
  }

  /*
  Future就是event，很多Flutter内置的组件比如Http（http请求控件）的get函数、
  RefreshIndicator（下拉手势刷新控件）的onRefresh函数都是event。
  每一个被await标记的句柄也是一个event，每创建一个Future就会把这个Future扔进event queue中排队等候安检
  * */

  Future<List<CityData>> _fetchCityList() async{  //有await标记的运算，其结果值都是一个Future对象，
    final response = await http.get('https://search.heweather.net/top?group=cn&number=50&key=551f547c64b24816acfed8471215cd0e');

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
            onTap: (){  //List的Item
              Navigator.push( //相当于Android里面得Intent
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
