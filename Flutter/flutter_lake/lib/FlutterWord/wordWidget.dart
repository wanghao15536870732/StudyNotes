
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter_lake/FlutterWord/wordData.dart';
import 'package:http/http.dart' as http;

class WordWidget extends StatefulWidget {

  String Word;

  WordWidget(this.Word);




  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      title: 'Word Detail',
      theme: new ThemeData(
          primaryColor: Colors.blueAccent
      ),
      home: new Scaffold(
        appBar: new AppBar(
          title: new Text('Word Detail'),
        ),
        body: new Center(
          child: new Text(Word),
        ),
      )
    );
  }

  @override
  State<StatefulWidget> createState() {
    // TODO: implement createState
    return new WordState(this.Word);
  }
}


class WordState extends State<WordWidget>{

  String word;

  WordState(String word){
    this.word = word;

  }

  Future<WordData> _fetchWordDetail() async{
    String signStr = "347145021fc2ba71" + word + 'UUID' ;
    final respose = await http.get(
        'http://fanyi.youdao.com/openapi.do?keyfrom=zhaotranslator&key=1681711370&type=data&doctype=json&version=1.1&q='
    );
    if(respose.statusCode == 200){

    }else{

    }
  }

  @override
  Widget build(BuildContext context) {
    // TODO: implement build
    return null;
  }

}

