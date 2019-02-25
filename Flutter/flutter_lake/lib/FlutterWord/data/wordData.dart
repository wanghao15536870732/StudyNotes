
class WordData{
  final String transRes;  //翻译结果
  final String transExp;  //翻译解释
  final String webs;
  final String phonetic;  //普通发音
  final String us;  //美式发音
  final String uk;  //英式发音

  WordData({
    this.transExp,
    this.transRes,
    this.webs,
    this.phonetic,
    this.us,
    this.uk
  });

  factory WordData.fromJson(Map<String,dynamic> json){
    return fromMap(json);
  }

  /*
   *  {
   *  "translation":["苹果"],
   *  "basic":
   *  {
   *  "us-phonetic":"'æpl",
   *  "phonetic":"'æp(ə)l",
   *  "uk-phonetic":"'æp(ə)l",
   *  "explains":["n. 苹果，苹果树，苹果似的东西；[美俚]炸弹，手榴弹，（棒球的）球；[美俚]人，家伙。"]
   *  },
   *  "query":"apple","
   *  errorCode":0,
   *  "web":[
   *  {"value":["苹果","苹果","苹果公司"],"key":"Apple"},
   *  {"value":["苹果商店","苹果零售店","苹果商店"],"key":"Apple Store"},
   *  {"value":["苹果绿","苹果绿色","果绿"],
   *  "key":"Apple green"}]
   *  }
   */

  static WordData fromMap(Map map){
    List translations  = map['translation'];  //
    List explains = map['basic']['explains'];
    List webs = map['web'];
    List values;
    var phonetic = map['basic']['phonetic'];
    var us = map['basic']['us-phonetic'];
    var uk = map['basic']['uk-phonetic'];

    var result = '';
    //"translation": ["苹果","树上的苹果"]，
    for(int i = 0;i < translations.length;i++){
      if(i == 0){
        result = result + translations[i];
      }else{
        result = result + ',' + translations[i];
      }
    }

    var exp = '';
    for(int i = 0;i < explains.length;i++){
      if(i == 0){
        exp = exp + explains[i];
      }else{
        exp = exp + ',' + explains[i];
      }
    }

    var we = '';
    for(int i = 0;i < webs.length;i ++){
      values = webs[i]['value'];
      var val = '';
      for(int j = 0;j < values.length;j++){
        if(j == 0){
          val = val + values[j];
        }else{
          val = val + ',' + values[j];
        }
      }
      if(i == 0){
        we = we + webs[i]['key'] + ':' + val;
      }else{
        we = we + ' ' + webs[i]['key'] + ':' + val;
      }
    }

    return new WordData(
      transRes: result,
      transExp: exp,
      webs: we,
      phonetic:phonetic,
      us: us,
      uk: uk,
    );
  }



  factory WordData.empty(){
    return WordData(
      transRes: "",
      transExp: "",
      webs: "",
      phonetic: "",
      us: "",
      uk: "",
    );
  }
}