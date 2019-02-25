
class OneData{
  String code;  //对应天气代码
  String data;   //日期‘
  String weather;  //天气
  String ltempture;  //最低温度
  String htempture;  //最高温度
  String winddir; //风向
  String windsc; //风速

  OneData({
    this.code,
    this.data,
    this.weather,
    this.ltempture,
    this.htempture,
    this.winddir,
    this.windsc
  });

  /**
   * {"
   * cond_code_d":"101",
   * "cond_code_n":"104",
   * "cond_txt_d":"多云",
   * "cond_txt_n":"阴",
   * "date":"2019-02-25",
   * "hum":"44",
   * "mr":"00:00",
   * "ms":"10:43",
   * "pcpn":"0.0",
   * "pop":"6",
   * "pres":"911",
   * "sr":"07:05",
   * "ss":"18:20",
   * "tmp_max":"9",
   * "tmp_min":"-2",
   * "uv_index":"0",
   * "vis":"24",
   * "wind_deg":"157",
   * "wind_dir":"东南风",
   * "wind_sc":"1-2",
   * "wind_spd":"9"}
   */

  factory OneData.fromJson(Map<String,dynamic> json){

    return OneData(
      code: json['cond_code_d'],
      data: json['date'],
      weather: json['cond_txt_d'],
      ltempture: json['tmp_min'],
      htempture: json['tmp_max'],
      winddir: json['wind_dir'],
      windsc: json['1-2'],
    );
  }

  factory OneData.empty(){
    return OneData(
      code: "",
      data: "",
      weather: "",
      ltempture: "",
      htempture: "",
      winddir: "",
      windsc: "",
    );
  }
}