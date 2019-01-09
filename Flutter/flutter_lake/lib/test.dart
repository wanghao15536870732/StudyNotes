import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:english_words/english_words.dart';

class SampleApp extends StatelessWidget{
  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      title: 'Sample App',
      theme: new ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: new Center(
        child: new SampleApppage()
      ),
    );
  }
}

class SampleApppage extends StatefulWidget{

  SampleApppage({Key key}) : super(key:key);

  _SampleAppPageState createState() => _SampleAppPageState();
}

class _SampleAppPageState extends State<SampleApppage>{

  String textToShow = "I like you but only me";
  
  void _updatetext(){
    setState(() {
      textToShow = 'Please do not let me go.';
    });
  }

  @override
  Widget build(BuildContext context) {
    // TODO: implement build
    return new Scaffold(
      appBar: new AppBar(
        title: new Text('Sample App'),
      ),
      body: new ListView(
        children: <Widget>[
          new Container(
                child: new Text(textToShow),
                margin: EdgeInsets.all(18.0),
              ),
              FlatButton(
                child: Text('打开一个新的route.'),
                textColor: Colors.blue,
                onPressed: (){
                  //导航到新路由
                  Navigator.push(context,
            //MaterialPageRoute继承自PageRoute类，PageRoute类是一个抽象类，
            // 表示占有整个屏幕空间的一个模态路由页面，它还定义了路由构建及切换时过渡动画的相关接口及属性。
              // MaterialPageRoute 是Material组件库的一个Widget，它可以针对不同平台
             // 实现与平台页面切换动画风格一致的路由切换动画
                      new MaterialPageRoute(builder: (context){
                        return new NewRoute();
                      }));
                },
              ),
          new RandomWordsWidget(),
          new SwitchAndCheckBoxTestRoute(),
        ],
      ),
      floatingActionButton: new FloatingActionButton(
          onPressed: _updatetext,
        tooltip: 'Update Text',
        child: new Icon(Icons.update),
      ),
    );
  }
}
class RandomWordsWidget extends StatelessWidget{
  @override
  Widget build(BuildContext context) {
    final wordPair = new WordPair.random();
    return Padding(
      padding: const EdgeInsets.all(8.0),
      child: new Text(wordPair.asPascalCase.toString(),
        textScaleFactor: 1.5,
      ),
    );
  }
}


class NewRoute extends StatelessWidget{
  @override
  Widget build(BuildContext context) {
    // TODO: implement build
    return Scaffold(
      appBar: AppBar(
        title: Text('输入以及表单'),
      ),
      body: new ListView(
          children: <Widget>[
            new Text('This is a new route.'),
            new EditText(),
          ],
        ),
    );
  }
}

//单选框跟复选框
class SwitchAndCheckBoxTestRoute extends StatefulWidget{
  @override
  _SwitchAndCheckBoxTestRouteState createState() => new _SwitchAndCheckBoxTestRouteState();
}

class _SwitchAndCheckBoxTestRouteState extends State<SwitchAndCheckBoxTestRoute>{
  bool _switchSelected = true; //维护复选框开关状态
  bool _checkboxSelected = true;//维护单选框开关状态
  @override
  Widget build(BuildContext context) {
    return Column(
      children: <Widget>[
        Switch(
          value: _switchSelected,
          onChanged: (value){
            setState(() {
              _switchSelected = value;
            });
          },
        ),
        Checkbox(
          value: _checkboxSelected,
          activeColor: Colors.blue,
          onChanged: (value){
            setState(() {
              _checkboxSelected = value;
            });
          },
        ),
      ],
    );
  }
}

class EditText extends StatelessWidget{
  @override
  Widget build(BuildContext context) {
    // TODO: implement build
    return Column(
      children: <Widget>[
        TextField(
          autofocus: true,
          decoration: InputDecoration(
            labelText: '用户名',
            hintText: '用户名或邮箱',
            prefixIcon: Icon(Icons.person)
          ),
        ),
        TextField(
          decoration: InputDecoration(
            labelText: '密码',
            hintText: '您的登陆密码',
            prefixIcon: Icon(Icons.lock)
          ),
          obscureText: true,
        )
      ],
    );
  }
}