# Flutter 中的布局

## 基础

+ 变量以下划线"_"开头，在Dart语言中会强制其变成私有的

```dart
final _suggestions = <WordPair>[];
```

+ asPascalCase 驼峰样式，字符串里卖弄的每个单词的首字母都会大写

```dart
Widget _buildRow(WordPair pair){

    //添加 alreadySaced 来检查确保单词对还没有添加到收藏夹中
    final alreadySaved = _saved.contains(pair);
    return new ListTile(
    title: new Text(
        pair.asPascalCase,  //照样还是驼峰央视
        style: _biggerFont,   //上面定义过的字体大小
    ),
    //添加一个心形 ❤ 形图标到 ListTiles以启用收藏功能。接下来，你就可以给心形 ❤图标添加交互能力了。
    trailing: new Icon(
        alreadySaved ? Icons.favorite : Icons.favorite_border,
        color: alreadySaved ? Colors.red : null,
    ),
    onTap: (){  //心形图案的点击事件
        setState(() {  //当图标被点击时，函数调用setState()会为State对象触发build()方法，从而导致对UI的更新
        if(alreadySaved){  //如果单词条目已经添加到收藏夹中
            _saved.remove(pair);  //再次点击它将其从收藏夹中删除
        }else{  //否则
            _saved.add(pair);  //添加到收藏夹当中
        }
        });
    },
    );
}
```

### GridView

使用GridView将widget放置为二维列表。 GridView提供了两个预制list，或者您可以构建自定义网格。当GridView检测到其内容太长而不适合渲染框时，它会自动滚动。

GridView 概览:

+ 在网格中放置widget
+ 检测列内容超过渲染框时自动提供滚动
+ 构建您自己的自定义grid，或使用一下提供的grid之一:
+ GridView.count 允许您指定列数
+ GridView.extent 允许您指定项的最大像素宽度

![Girdview](https://upload-images.jianshu.io/upload_images/9140378-4f9dbcb2cb43bbe0.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/240)

```dart
    List<Container> _buildGridTileList(int count){
      return new List<Container>.generate(
        count,
          (int index) =>
          new Container(child: new Image.asset('images/pic${index + 1}.jpg')));
    }

    Widget buildGrid(){
      //网格布局
      return new GridView.extent(
        maxCrossAxisExtent: 150.0,  //横轴的最大列宽度
        padding:const EdgeInsets.all(4.0),
        mainAxisSpacing: 8.0,  //每个子项沿主轴的逻辑像素数,相当于每一列之间的宽度
        crossAxisSpacing: 8.0,  //沿着横轴的每个子节点之间的逻辑像素数，相当于每一行之间的宽度
        children: _buildGridTileList(20),
      );
    }

    return new MaterialApp(
      title: "Flutter Lake",
      theme: new ThemeData(
        primarySwatch: Colors.blue,
      ),
      //Scaffold是 Material Components库中的一个widget，它提供了一个默认banner，背景颜色，
      // 并且具有添加drawer，snack bar和底部sheet的API
      home:new Scaffold(
        appBar: new AppBar(
          title: new Text('Flutter Lake'),
        ),
        body: new Center(
          child: buildGrid(),
        ),
      ),
    );
```

### ListView

ListView是一个类似列的widget，它的内容对于其渲染框太长时会自动提供滚动。

ListView 摘要:

+ 用于组织盒子中列表的特殊Column
+ 可以水平或垂直放置
+ 检测它的内容超过显示框时提供滚动
+ 比Column配置少，但更易于使用并支持滚动

![ListView](https://upload-images.jianshu.io/upload_images/9140378-05e7595ca0f6020a.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/340)

```dart
//一个ListView
List<Widget> list = <Widget>[
    new ListTile(  //ListView中的每一条
    title: new Text('CineArts at the Empire',
        style: new TextStyle(fontWeight: FontWeight.w500,fontSize: 20.0)),
    subtitle: new Text('85 W Portal'),  //小标题
    leading: new Icon(
        Icons.theaters,
        color: Colors.blue[500],
      ),
    ),
    new ListTile(
    title: new Text('The Castro Theater',
        style: new TextStyle(fontWeight: FontWeight.w500,fontSize: 20.0)),
    subtitle: new Text('429 Castro St'),
    leading: new Icon(
        Icons.theaters,
        color: Colors.blue[500],
      ),
    ),
];
return new MaterialApp(
    title: "Flutter Lake",
    theme: new ThemeData(
      primarySwatch: Colors.blue,
    ),
    //Scaffold是 Material Components库中的一个widget，它提供了一个默认banner，背景颜色，
    // 并且具有添加drawer，snack bar和底部sheet的API
    home:new Scaffold(
    appBar: new AppBar(
        title: new Text('Flutter Lake'),
    ),
    body: new Center(
        child: new ListView(
          children: list,
        )
        //buildGrid(),
    ),
  ),
);
```

### Stack

使用Stack来组织需要重叠的widget。widget可以完全或部分重叠底部widget。

Stack summary:

+ 用于与另一个widget重叠的widget
+ 子列表中的第一个widget是base widget; 随后的子widget被覆盖在基础widget的顶部
+ Stack的内容不能滚动
+ 您可以选择剪切超过渲染框的子项
+ Stack使用alignment属性和调整文本偏移。

![Stack.jpg](https://upload-images.jianshu.io/upload_images/9140378-647b9c5fce9c23ad.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/340)

```dart
var stack = new Stack(
    alignment: const Alignment(0.6, 0.6),
    children: <Widget>[
    new CircleAvatar(  //类似于Android中的Cirecal
        // View
        backgroundImage: new AssetImage('images/pic1.jpg'),
        radius: 100.0,
    ),
    new Container(
        decoration: new BoxDecoration(
        color: Colors.black45,
        ),
        child: new Text(
        'Mia B',
        style: new TextStyle(
            fontSize: 20.0,
            fontWeight: FontWeight.bold,
            color: Colors.white,
          ),
        ),
      )
    ],
);



return new MaterialApp(
    title: "Flutter Lake",
    theme: new ThemeData(
    primarySwatch: Colors.blue,
    ),
    //Scaffold是 Material Components库中的一个widget，它提供了一个默认banner，背景颜色，
    // 并且具有添加drawer，snack bar和底部sheet的API
    home:new Scaffold(
    appBar: new AppBar(
        title: new Text('Flutter Lake'),
    ),
    body: new Center(
        child: new ListView(
        children: [
            stack
        ],
        ) //buildGrid(),
    ),
    ),
);
```

### Card

Material Components 库中的Card包含相关内容块，可以由大多数类型的widget构成，但通常与ListTile一起使用。Card有一个孩子， 但它可以是支持多个孩子的列，行，列表，网格或其他小部件。默认情况下，Card将其大小缩小为0像素。您可以使用SizedBox来限制Card的大小。

在Flutter中，Card具有圆角和阴影，这使它有一个3D效果。更改Card的eelevation属性允许您控制投影效果。 例如，将elevation设置为24.0，将会使Card从视觉上抬离表面并使阴影变得更加分散。 有关支持的elevation值的列表，请参见Material guidelines中的Elevation and Shadows。 如果指定不支持的值将会完全禁用投影 。

Card 摘要:

+ 实现了一个 Material Design card
+ 接受单个孩子，但该孩子可以是Row，Column或其他包含子级列表的widget
+ 显示圆角和阴影
+ Card内容不能滚动
+ Material Components 库的一个widget

![Card](https://upload-images.jianshu.io/upload_images/9140378-7230d8acf6a75840.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/340)

```dart
//Card
var card = new SizedBox(
    height: 210.0,
    child: new Card(
    child: new Column(
        children: <Widget>[
        new ListTile(
            title: new Text('1625 main Street',
              style: new TextStyle(fontWeight: FontWeight.w500)),
            subtitle: new Text('My City, CA 99984'),
            leading: new Icon(
              Icons.restaurant_menu,
              color: Colors.blue[500],
            ),
        ),
        new Divider(), //中间的黑条横线
        new ListTile(
            title: new Text('(408) 5555-1212',
              style: new TextStyle(fontWeight: FontWeight.w500)),
            leading: new Icon(
              Icons.contact_phone,
              color: Colors.blue[500],
            ),
        ),
        new ListTile(
            title: new Text('costa@example.com'),
            leading: new Icon(  //在标题的前面有一个图片
              Icons.contact_mail,
              color: Colors.blue[500],
            ),
          )
        ],
      ),
    ),
);


return new MaterialApp(
    title: "Flutter Lake",
    theme: new ThemeData(
    primarySwatch: Colors.blue,
    ),
    //Scaffold是 Material Components库中的一个widget，它提供了一个默认banner，背景颜色，
    // 并且具有添加drawer，snack bar和底部sheet的API
    home:new Scaffold(
    appBar: new AppBar(
        title: new Text('Flutter Lake'),
    ),
    body: new Center(
        child: new ListView(
        children: [
            stack,
            card
        ],
        ) //buildGrid(),
    ),
    ),
);
}
```

### ListTile

ListTile是Material Components库中的一个专门的行级widget，用于创建包含最多3行文本和可选的行前和行尾图标的行。ListTile在Card或ListView中最常用，但也可以在别处使用。

ListTile 摘要:

+ 包含最多3行文本和可选图标的专用行
+ 比起Row不易配置，但更易于使用
+ Material Components 库里的widget

`ListTile 示例:`

## Wight

+ 这个相当于一个控件
+ 即使应用程序本身也是一个 widget.
+ 创建一个widget并将其添加到布局widget中是很简单的.
+ 要在设备上显示widget，请将布局widget添加到 app widget中。
+ 使用Scaffold是最容易的，它是 Material Components库中的一个widget，它提供了一个+ 默认banner，背景颜色，并且具有添加drawer，snack bar和底部sheet的API。
+ 如果您愿意，可以构建仅使用标准widget库中的widget来构建您的应用程序

例如，创建一个Text widget:

```dart
new Text('Hello World', style: new TextStyle(fontSize: 32.0))
```

创建一个 Image widget:

```dart
new Image.asset('images/myPic.jpg', fit: BoxFit.cover)
```

创建一个 Icon widget:

```dart
new Icon(Icons.star, color: Colors.red[500])
```

## Row & Coclumn

+ 控件的排列 行(Row)和列(Column)，是flutter中最常用的两个布局控件，他们只能容纳当前屏幕尺寸大小的内容，如果其内部的子控件超出屏幕尺寸，不但不会自动生成滚动条，还会报错

```dart
    new Column(...);
    new Roe(...);
```

## Container

这个相当于一个囊括者，可以为其子属性设置各种属性

+ 如果要添加填充，边距，边框或背景色，请使用Container来设置

```dart
new Container(  
  padding: const EdgeInsets.only(bottom: 8.0), 
  child: new Text(
    'Oeschinen Lake Campground',
    style: new TextStyle(  //定义其Text的style
      fontWeight: FontWeight.bold,
    ),
  ),
),
```

## Scaffold

Scaffold是 Material Components库中的一个widget，它提供了一个默认banner，背景颜色，并且具有添加drawer，snack bar和底部sheet的API

+ 选择一个widget来保存该对象。
+ ainAxisAlignment表示主轴方向（水平方向)
+ CrossAxisAlignment表示副轴方向（和主轴垂直，即垂直方向    
+ 如果其内部的子控件超出屏幕尺寸，不但不会自动生成滚动条，还会报错
+ 如果要添加填充，边距，边框或背景色，请使用Container来设置
      new Container(...);
+ softWrap: true, //自动换行

+ softWrap: true, //自动换行
+ mainAxisAlignment:
  + MainAxisAlignment.spaceEvenly, //水平均匀等间距
  + mainAxisAlignment表示主轴方向（水平方向）
+ mainAxisSpacing: //每个子项沿主轴的逻辑像素数

### maxCrossAxisExtent

横轴的最大瓦片范围。此委托将根据以下条件为尽可能大的切片选择横轴范围：

+ 范围均匀地划分网格的横轴范围。
+ 范围最多为maxCrossAxisExtent。
+ 例如，如果网格是垂直的，网格宽度为500.0像素， maxCrossAxisExtent为150.0，则此委托将创建一个包含4列宽度为125.0像素的网格。

