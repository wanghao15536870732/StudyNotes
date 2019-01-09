
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class FlutterLake extends StatelessWidget{
  @override
  Widget build(BuildContext context) {
    final alreadyStart = true;
    Widget titleSection = new Container(
      padding: const EdgeInsets.all(32.0),
      // 控件的排列 行(Row)和列(Column)，是flutter中最常用的两个布局控件，他们只能容纳当前屏幕尺寸大小的内容
      // 如果其内部的子控件超出屏幕尺寸，不但不会自动生成滚动条，还会报错
      child: new Row( // 行
        children: [
          new Expanded(
              child: new Column( //列
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  new Container(  //如果要添加填充，边距，边框或背景色，请使用Container来设置
                    padding: const EdgeInsets.only(bottom: 8.0), //距离行的底部 8.0
                    child: new Text(
                      'Oeschinen Lake Campground',
                      style: new TextStyle(
                        fontWeight: FontWeight.bold,
                      ),
                    ),
                  ),
                  new Text(
                    'Kandersteg, Switzerland',
                    style: new TextStyle(
                      color: Colors.grey[500],
                    ),
                  )
                ],
              )
          ),
          new FavoriteWidget(),
        ],
      ),
    );


    //自定义的每个 button 的列，然后将这些 button 放在同一个行
    Column buildButtonColumn(IconData icon, String label) {
      Color color = Theme
          .of(context)
          .primaryColor;

      return new Column(
        mainAxisSize: MainAxisSize.min,
        //对齐方式
        mainAxisAlignment: MainAxisAlignment.center,
        //mainAxisAlignment表示主轴方向（水平方向）
        // CrossAxisAlignment表示副轴方向（和主轴垂直，即垂直方向

        children: [
          new Icon(icon, color: color),
          new Container( // 容器Widget，允许自己定制一些子 widget
            margin: const EdgeInsets.only(top: 8.0),
            //EdgeInsets类指定在视觉边缘，左，上，右和下方面偏移
            //图片距离上方的margin为 8.0，距离上面的图片8.0
            child: new Text(
              label, //标签
              style: new TextStyle( //设置文字的tyle
                fontSize: 12.0,
                fontWeight: FontWeight.w400,
                color: color,
              ),
            ),
          )
        ],
      );
    }

    //创建三个等距的button
    Widget buttonSection = new Container(
      child: new Row( //行
          mainAxisAlignment: MainAxisAlignment.spaceEvenly, //水平均匀等间距
          children: [
            buildButtonColumn(Icons.call, 'CALL'),
            buildButtonColumn(Icons.near_me, 'ROUTE'),
            buildButtonColumn(Icons.share, 'SHARE')
          ]
      ),
    );

    //创建一长串文字
    Widget textSection = new Container(
      padding: const EdgeInsets.all(32.0),
      child: new Text(
        '''
          Lake Oeschinen lies at the foot of the Blüemlisalp in the Bernese Alps. Situated 1,578 meters above sea level, it is one of the larger Alpine Lakes. A gondola ride from Kandersteg, followed by a half-hour walk through pastures and pine forest, leads you to the lake, which warms to 20 degrees Celsius in the summer.Activities enjoyed here include rowing, and riding the summer toboggan run.
          ''',
        softWrap: true, //自动换行
      ),
    );

    ListView lake() {
      return new ListView(
        children: [
          new Image.asset( //定义图片的高宽度
            'images/tree.jpg',
            width: 600.0,
            height: 240.0,
            fit: BoxFit.cover,
          ),
          titleSection, //标题 + 文字
          buttonSection, //三个导航键按钮
          textSection, //一段自适配的文字
          new TapboxA(),
          new ParentWidget(),
        ],
      );
    }

    return Scaffold(
      appBar: AppBar(
        title: Text('Flutter Lake'),
      ),
      body: lake(),
    );
  }
}

/**
 * FavoriteWidget类管理自己的状态，因此它重写createState()来创建状态对象。
 * 框架会在构建widget时调用createState()。
 * 在这个例子中，createState()创建_FavoriteWidgetState的实例，您将在下一步中实现该实例。
 */
class FavoriteWidget extends StatefulWidget{

  _FavoriteWidgetState createState() => new _FavoriteWidgetState();
}

//State子类，自定义State类存储可变信息 - 可以在widget的生命周期内改变逻辑和内部状态
class _FavoriteWidgetState extends State<FavoriteWidget>{

  bool _isFavorited = true;
  int _favoriteCount = 41;

  void _toggleFavorite(){
    setState(() {
      if(_isFavorited){  //如果现在已经标记为喜爱
        _favoriteCount -= 1;//那么点击后喜欢的数量 - 1
        _isFavorited = false;
      }else{
        _favoriteCount += 1;
        _isFavorited = true;
      }
    });
  }

  /**
   * 状态对象也定义了build方法。此build方法创建一个包含红色IconButton和Text的行。
   * 该widget使用IconButton（而不是Icon），
   * 因为它具有一个onPressed属性，该属性定义了处理点击的回调方法。
   * IconButton也有一个icon的属性，持有Icon。
   */
  @override
  Widget build(BuildContext context) {
    return new Row(
      mainAxisSize: MainAxisSize.min,
      children: <Widget>[
        new Container(
          padding: new EdgeInsets.all(0.0),
          child: new IconButton(
              icon: (_isFavorited
                  ? new Icon(Icons.star)
                  : new Icon(Icons.star_border)),
              color: Colors.red[500],
              onPressed: _toggleFavorite,
          ),
        ),
        new SizedBox(
          width: 18.0,
          child: new Container(
            child: new Text('$_favoriteCount'),
          ),
        )
      ],
    );
  }
}

class TapboxA extends StatefulWidget{
  _TapboxState createState() => new _TapboxState();
}

class _TapboxState extends State<TapboxA>{
  bool _active = false;

  void _handleTap(){
    setState(() {
      _active = !_active;  //点击造成活动相反
    });
  }

  @override
  Widget build(BuildContext context) {
    return new GestureDetector(
      onTap: _handleTap,
      child: new Container(
        child: new Center(
          child: new Text(
            _active ? 'Activie':'Inactive',
            style: new TextStyle(fontSize: 32.0,color: Colors.white),
          ),
        ),
        width: 200.0,
        height: 200.0,
        decoration: new BoxDecoration(
          color: _active ? Colors.lightGreen[700]:Colors.grey[600],
        ),
      ),
    );
  }
}

class ParentWidget extends StatefulWidget{
  @override
   _ParentWidgetState createState() => new _ParentWidgetState();
}

class _ParentWidgetState extends State<ParentWidget>{
  bool _active = false;


  void _handleTapboxChanged(bool newValue){
    setState(() {
      _active = newValue;
    });
  }

  @override
  Widget build(BuildContext context) {
    return new Container(
      child: new TapboxC(
        active: _active,
        onChanged: _handleTapboxChanged,
      ),
    );
  }
}

class TapboxB extends StatelessWidget {

  final bool active;
  final ValueChanged<bool> onChanged;

  TapboxB({
    Key key,
    this.active:false,
    this.onChanged
  }):super(key:key);

  void _handleTap(){
    onChanged(!active);
  }

  Widget build(BuildContext context) {
    return new GestureDetector(
      onTap: _handleTap,
      child: new Container(
        child: new Center(
          child: new Text(
            active ? 'Active' : 'Inactive',
            style: new TextStyle(fontSize: 32.0, color: Colors.white),
          ),
        ),
        width: 200.0,
        height: 200.0,
        decoration: new BoxDecoration(
          color: active ? Colors.lightGreen[700] : Colors.grey[600],
        ),
      ),
    );
  }
}

class TapboxC extends StatefulWidget{
  final bool active;
  final ValueChanged<bool> onChanged;

  TapboxC({Key key,this.active:false,this.onChanged}):super(key:key);

  _TapboxCState createState() => new _TapboxCState();
}

class _TapboxCState extends State<TapboxC> {

  bool _highlight = false;

  void _handleTapDown(TapDownDetails details){
    setState(() {
      _highlight = true;
    });
  }

  void _handleTapUp(TapUpDetails details){
    setState(() {
      _highlight = false;
    });
  }

  void _handleTapCancel(){
    setState(() {
      _highlight = false;
    });
  }

  void _handleTap(){
    widget.onChanged(!widget.active);
  }

  @override
  Widget build(BuildContext context) {
    return new GestureDetector(
      onTapDown: _handleTapDown,
      onTapUp: _handleTapUp,
      onTap: _handleTap,
      onTapCancel: _handleTapCancel,
      child: new Container(
        child: new Center(
          child: new Text(widget.active ? 'Active':'Inactive',
            style: new TextStyle(fontSize: 32.0,color: Colors.white)),
        ),
        width: 200.0,
        height: 200.0,
        decoration: new BoxDecoration(
          color:
            widget.active ? Colors.lightGreen[700] : Colors.grey[600],
          border: _highlight
            ? new Border.all(
            color: Colors.teal[700],
            width: 10.0
          ): null,
        ),
      ),
    );
  }
}