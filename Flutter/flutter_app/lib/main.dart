import 'package:flutter/material.dart';
// ignore: uri_does_not_exist
import 'package:english_words/english_words.dart';

void main() => runApp(new MyApp());

////将生成单词对代的码从MyApp移动到RandomWordsState中
class MyApp extends StatelessWidget {
  Widget build(BuildContext context) {
    // TODO: implement build
    // final wordPair = new WordPair.random();
    return new MaterialApp(
//      title: 'Welcome to Flutter',
//      home: new Scaffold(
//        appBar: new AppBar(
//          title: new Text('Welcome to Flutter'),
//        ),
//        body: new Center(
//          child: new RandowWords(),  //定义子控件为有状态控件RandowWords的实例
//        ),
//      ),
        title: 'Startup Name Generator',
        //更新主题
        theme: new ThemeData(
          primaryColor: Colors.cyanAccent
        ),
        home: new RandowWords(),
    );
  }
}

//添加有状态的 RandomWords widget
//RandomWords widget除了创建State类之外几乎没有其他任何东西
class RandowWords extends StatefulWidget{
  @override
  //为StatefulWidget控件RandowWords定义一个子类
  createState() => new RandowWordsState();
}

/**
 * wordpair 随机单词
 * 定义了一个状态控件，继承自状态类State<RandowWords>
 * <RandowWords>指明这个状态控件是RandowWords指控的
 */
class RandowWordsState extends State<RandowWords>{
    //向RandomWordsState类中添加一个_suggestions列表以保存建议的单词对。
    //该变量以下划线"_"开头，在Dart语言中会强制其变成私有的
    final _suggestions = <WordPair>[];

    //添加一个_saved集合，这个集合储存用户喜欢的单词对
    // 在这里，Set比List更合适。因为Set中不允许有重复的值
    final _saved = new Set<WordPair>();

    //添加一个 biggerFont 变量来增大字体大小
    final _biggerFont = const TextStyle(fontSize: 18.0);

//    // TODO: implement build
//    final wordPair = new WordPair.random(); //随机单词
//    //asPascalCase 驼峰样式，字符串里卖弄的每个单词的首字母都会大写
//    return new Text(wordPair.asPascalCase);

    // 这个函数在ListTile中显示每个新词对，在下一步中可以生成更漂亮的显示行
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
    /*
    *此方法构建显示建议单词对的ListView
    */
    Widget _buildSuggestions(){
      //ListView提供了一个builder属性，
      return new ListView.builder(
        padding: const EdgeInsets.all(16.0), //四周padding都设为16.0，四周形
        /*
        itemBuilder 值是一个匿名回调函数， 接受两个参数- BuildContext和行迭代器i。
        迭代器从0开始， 每调用一次该函数，i就会自增1，对于每个建议的单词对都会执行一次。
        该模型允许建议的单词对列表在用户滚动时无限增长。
         */
        itemBuilder: (context,i){
           //在每一列之前，添加一个1像素高的分隔线
          if(i.isOdd) return new Divider();  //idOdd方法：如果数字是奇数，则此属性返回布尔值true。
          final index = i~/2;  //语法 "i ~/ 2" 表示i除以2，但返回值是整形（向下取整）
          if(index >= _suggestions.length){  ///如果是建议列表中最后一个单词对
            // ...接着再生成10个单词对，然后添加到建议列表
            _suggestions.addAll(generateWordPairs().take(10));
          }
          // ignore: referenced_before_declaration
          return _buildRow(_suggestions[index]); //对于每一个单词对，_buildSuggestions函数都会调用一次_buildRow
        },
      );
    }
    //当用户点击导航栏中的列表图标时，建立一个route并将其推入到导航管理器栈中
    void _pushSaved(){
      //添加Navigator.push调用，这会使路由入栈（以后route入栈均指推入到导航管理器的栈）
      Navigator.of(context).push(
        //新页面的内容在在MaterialPageRoute的builder属性中构建，builder是一个匿名函数
        new MaterialPageRoute(
            builder: (context){
              final tiles = _saved.map(
                  (pair) {
                    return new ListTile(
                      title: new Text(
                        pair.asPascalCase,  //单词首字母大写
                        style: _biggerFont,  //单词字体的大小
                      ),
                    );
                  }
              );
              //ListTile的divideTiles()方法在每个ListTile之间添加1像素的分割线。
              final divided = ListTile //该 divided 变量保存最终的列表项
                  .divideTiles(
                    context: context,
                    tiles: tiles,
              ).toList();

              //builder返回一个Scaffold，其中包含名为“Saved Suggestions”的新route的应用栏
              return new Scaffold(
                appBar: new AppBar(
                  title: new Text('Save Suggestions'),
                ),
                body: new ListView(children: divided),
              );
            }
        )
      );
    }

    //该方法通过将生成单词对的代码从MyApp移动到RandomWordsState来生成单词对。
    @override
    Widget build(BuildContext context) {
      return new Scaffold(
        //相当于android中的AppBar
        appBar: new AppBar(
          title: new Text('Startip Name Generator'),
          //添加了一个列表图标。当用户点击列表图标时，包含收藏夹的新路由页面入栈显示
          actions: <Widget>[     //其实就是类似于Android中AppBar中的Menu
            new IconButton(icon: new Icon(Icons.list), onPressed: _pushSaved)
          ],
        ),
        body: _buildSuggestions(),
      );
    }
}






