
class WeekData{
  List OneData;

  WeekData({
    this.OneData
  });

  factory WeekData.fromJson(Map<List,dynamic> json){
    return WeekData(
      OneData: json['HeWeather6'][0]['daily_forecast'],
    );
  }

  factory WeekData.empty(){
    return WeekData(
      OneData: [],
    );
  }
}