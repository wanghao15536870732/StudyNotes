
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:english_words/english_words.dart';
import 'package:flutter_lake/FlutterWord/wordWidget.dart';

class Word extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      title: 'Flutter Word',
      theme: new ThemeData(
        primaryColor: Colors.blueAccent
      ),
      home: new RandomWords(),
    );
  }
}

//添加有状态的 RandomWords widget
//RandomWords widget除了创建State类之外几乎没有其他任何东西
class RandomWords extends StatefulWidget{
  @override
  createState() => new RandomWordState();
}

/**
 * wordpair 随机单词
 * 定义了一个状态控件，继承自状态类State<RandowWords>
 * <RandowWords>指明这个状态控件是RandowWords指控的
 */
class RandomWordState extends State<RandomWords>{

  //向RandomWordsState类中添加一个_suggestions列表以保存建议的单词对。
  //该变量以下划线"_"开头，在Dart语言中会强制其变成私有的
  final _suggestions = <WordPair>[];

  //添加一个_saved集合，这个集合储存用户喜欢的单词对
  // 在这里，Set比List更合适。因为Set中不允许有重复的值
  final _saved = new Set<WordPair>();

  //添加一个 biggerFont 变量来增大字体大小
  final _biggerFont = const TextStyle(fontSize: 18.0);

  // 这个Widget在ListTile中显示每个新词对，在下一步中可以生成更漂亮的显示行
  Widget _buildRow(WordPair pair){
    final alreadySaved = _saved.contains(pair);
    return new ListTile(
      title: new Text(
        pair.asPascalCase,
        style: _biggerFont,
      ),
      trailing: new Icon(
        alreadySaved ? Icons.favorite : Icons.favorite_border,
        color: alreadySaved ? Colors.red : null,
      ),
      onTap: (){
        setState(() {  //当图标被点击时，函数调用setState()会为State对象触发build()方法，从而导致对UI的更新
          if(alreadySaved){  //如果单词条目已经添加到收藏夹中
            _saved.remove(pair);  //再次点击它将其从收藏夹中删除
          }else{
            _saved.add(pair);
          }
        });
      },
    );
  }

  /*
    *此方法构建显示建议单词对的ListView
    */
  Widget _buildSuggestion(){
    return new ListView.builder(
      padding: const EdgeInsets.all(16.0), //四周padding都设为16.0

      /*
    itemBuilder 值是一个匿名回调函数,该模型允许建议的单词对列表在用户滚动时无限增长。
    * */
      itemBuilder: (context, i) {
        ////在每一列之前，添加一个1像素高的分隔线
        if (i.isOdd) return new Divider(); //idOdd方法：如果数字是奇数，则此属性返回布尔值true。
        final index = i ~/ 2; //（向下取整）
        if (index >= _suggestions.length) {
          // ...接着再生成10个单词对，然后添加到建议列表
          _suggestions.addAll(generateWordPairs().take(10));
        }
        return _buildRow(
            _suggestions[index]); //对于每一个单词对，_buildSuggestions函数都会调用一次_buildRow
      },
    );
  }



  void _pushSaved(){
    Navigator.of(context).push(
      new MaterialPageRoute(
          builder: (context){
            final tiles = _saved.map(
                (pair){
                  return new ListTile(
                    title: new Text(
                      pair.asPascalCase,
                      style: _biggerFont,
                    ),
                    onTap: (){
                      Navigator.of(context).push(
                        new MaterialPageRoute(builder:(context) => new WordWidget(pair.asPascalCase)),
                      );
                    },
                  );
                }
            );

            //ListTile的divideTitles()方法在每个ListTile之间添加分割线
            final divided = ListTile.divideTiles(
              context: context,
              tiles: tiles,
            ).toList();

            Widget _buildSave(){
              if(_saved.isNotEmpty){
               return ListView(
                   children: divided,
               );
              }else{
                return new Center(
                  child: new Container(
                    child: new Text(
                        '还没有单词被收藏呦~',
                      style: new TextStyle(
                        fontSize: 18.0,
                        color: Colors.black,
                      ),
                    ),
                  ),
                );
              }
            }

            //builder返回一个Scaffold，其中包含名为“Saved Words”的新route的应用栏
            return new Scaffold(
              appBar: new AppBar(
                title: new Text('Save Words'),
              ),
              body: _buildSave(),
            );
          }
      )
    );
  }


  //该方法通过将生成单词对的代码从MyApp移动到RandomWordsState来生成单词对。
  @override
  Widget build(BuildContext context) {
    // TODO: implement build
    return new Scaffold(
      appBar: new AppBar(
        title: new Text('Start Word Generator'),
        actions: <Widget>[
          new IconButton(
              icon: new Icon(Icons.list),
              onPressed: _pushSaved
          )
        ],
      ),
      body: _buildSuggestion(),
    );
  }
}

