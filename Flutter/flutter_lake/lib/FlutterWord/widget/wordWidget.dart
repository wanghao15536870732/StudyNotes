
import 'dart:convert';

import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter_lake/FlutterWord/data/wordData.dart';
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

  WordData wordData = WordData.empty();

  WordState(String word){
    this.word = word;
    _getWordDetail();
  }


  void _getWordDetail() async{
    WordData data = await _fetchWordDetail();
    setState(() {
      wordData = data;
    });
  }

  Future<WordData> _fetchWordDetail() async{
    final respose = await http.get(
        'http://fanyi.youdao.com/openapi.do?keyfrom=zhaotranslator&key=1681711370&type=data&doctype=json&version=1.1&q='
            + word
    );
    if(respose.statusCode == 200){
      return WordData.fromJson(json.decode(respose.body));
    }else{
      return WordData.empty();
    }
  }

  @override
  Widget build(BuildContext context) {


    var content = setData(wordData, word);
    new Padding(
        padding: const EdgeInsets.only(
          top: 10.0,
          left: 10.0,
          right: 10.0,
          bottom: 10.0,
        ),
      child: new Scrollbar(
          child: content,
      ),
    );

    // TODO: implement build
    return new Scaffold(
      appBar: new AppBar(
        title: new Text('Flutter Translation'),
      ),
      body: content
    );
  }

  @override
  void initState() {
    // TODO: implement initState
    super.initState();
  }

  setData(WordData data,String word){
    var translationMsg = new Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      mainAxisSize: MainAxisSize.min,
      children: <Widget>[
        new Divider(),
        new Text(
          '翻译结果：' + data.transRes,
          textAlign: TextAlign.left,
          style: new TextStyle(
            fontWeight: FontWeight.bold,fontSize: 18.0
          ),
        ),
        new Divider(),
        new Text('普通发声：' + data.phonetic),
        new Text('美式发音：' + data.us),
        new Text('英式发音：' + data.uk),
        new Divider(),
        new Text(
          '翻译解析：' + data.transExp,
          style: new TextStyle(
            fontSize: 14.0,
            color: Colors.redAccent,
          ),
        ),
        new Divider(),
        new Text('网络翻译：' + data.webs),
        new Divider(),
      ],
    );

    return new Padding(
        padding: const EdgeInsets.only(
          top: 10.0,
          left: 10.0,
          right: 10.0,
          bottom: 10.0,
        ),
      child: new Scrollbar(
          child: new Column(
            children: <Widget>[
              new Text(
                  word,
                style: new TextStyle(
                  fontSize: 20.0
                ),
              ),
              translationMsg,
            ],
          )
      ),
    );
  }

}

