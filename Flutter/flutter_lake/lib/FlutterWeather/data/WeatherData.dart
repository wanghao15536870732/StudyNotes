
class WeatherData{
  final String code;  //对应天气代码
  final String cond;//天气
  final String tmp; //温度
  final String hum; //湿度
  final String wind; //风向
  final String time;  //发布时间
  final String length;  //能见度

  WeatherData({
    this.cond,
    this.tmp,
    this.hum,
    this.code,
    this.wind,
    this.time,
    this.length,
  });

  factory WeatherData.fromJson(Map<String,dynamic> json){
    return WeatherData(
      code: json['HeWeather6'][0]['now']['cond_code'],
      cond: json['HeWeather6'][0]['now']['cond_txt'],
      tmp: json['HeWeather6'][0]['now']['tmp'],
      hum: "湿度 "+json['HeWeather6'][0]['now']['hum']+"%",
      wind: json['HeWeather6'][0]['now']['wind_dir'] + json['HeWeather6'][0]['now']['wind_spd'] + "级",
      time: json['HeWeather6'][0]['update']['loc'],
      length: json['HeWeather6'][0]['now']['vis'],
    );
  }

  factory WeatherData.empty() {
    return WeatherData(
      code: "",
      cond: "",
      tmp: "",
      hum: "",
      wind: "",
      time: "",
      length: "",
    );
  }
}