
class WeatherData{
  String code;  //对应天气代码
  String cond;//天气
  String tmp; //温度
  String hum; //适度
  String wind; //风向

  WeatherData({this.cond,this.tmp,this.hum, this.code,this.wind});

  factory WeatherData.fromJson(Map<String,dynamic> json){
    return WeatherData(
      code: json['HeWeather6'][0]['now']['cond_code'],
      cond: json['HeWeather6'][0]['now']['cond_txt'],
      tmp: json['HeWeather6'][0]['now']['tmp']+"°",
      hum: "湿度 "+json['HeWeather6'][0]['now']['hum']+"%",
      wind: json['HeWeather6'][0]['now']['wind_dir'] + json['HeWeather6'][0]['now']['wind_spd'] + "级",
    );
  }

  factory WeatherData.empty() {
    return WeatherData(
      code: "",
      cond: "",
      tmp: "",
      hum: "",
      wind: "",
    );
  }
}