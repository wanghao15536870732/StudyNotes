import 'package:flutter/material.dart';
import 'package:flutter_lake/CircleFloatingMenu/circle_floating_menu_page.dart';
import 'package:flutter_lake/FlutterLake/flutter_lake.dart';
import 'package:flutter_lake/FlutterWeather/weather.dart';
import 'package:flutter_lake/test.dart';
import 'package:oktoast/oktoast.dart';
import 'package:flutter_localizations/flutter_localizations.dart';
import 'package:flutter_lake/route.dart';

void main() => runApp(MyApp());


class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return OKToast(
      textStyle: TextStyle(fontSize: 18.0,color: Colors.white),
      backgroundColor: Colors.grey.withAlpha(200),
      radius: 8.0,
      child: MaterialApp(
        title: 'Fluter UI',
        theme: ThemeData(
          primarySwatch: Colors.pink,
        ),
        home: MyHomePage(title: 'Flutter UI',),
        localizationsDelegates: [
          GlobalMaterialLocalizations.delegate,
          GlobalWidgetsLocalizations.delegate,
        ],
        supportedLocales: [
          const Locale('zh','CH'),
          const Locale('en','US'),
        ],
        routes: {
          UIRoute.circleFloatingMenu:(_) => FloatingMenuPage(),
          UIRoute.flutterLake:(_) => FlutterLake(),
          UIRoute.flutterTest:(_) => SampleApp(),
          UIRoute.flutterWeather:(_) => Weather(),
        },
      ),
    );
  }
}

class MyHomePage extends StatefulWidget{
  MyHomePage({Key key,this.title}):super(key:key);

  final String title;

  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: PreferredSize(
          child: Container(
            child: AppBar(
              title: Text(widget.title),
              backgroundColor: Colors.transparent,
              elevation: 0.0,
            ),
            decoration: BoxDecoration(
              gradient: LinearGradient(
                begin: Alignment.topLeft,
                end: Alignment.bottomRight,
                colors: [
                  Colors.pinkAccent,
                  Colors.white,
                ],
              )
            ),
          ),
          preferredSize:
          new Size(MediaQuery.of(context).size.width, kToolbarHeight)
      ),
      body: SafeArea(
        top: false,
        bottom: false,
        child: Container(
          decoration: BoxDecoration(
            gradient: LinearGradient(
              begin: Alignment.topLeft,
              end: Alignment.bottomRight,
              colors: [
                Colors.white,
                Colors.pinkAccent,
              ],
            ),
          ),
          child: ListView.builder(
              itemBuilder: (context,index){
                return _MenuDataItem(menus[index]);
              },
            itemCount: menus.length,
          ),
        ),
      ),
    );
  }
}

class _MenuDataItem extends StatelessWidget{

  const _MenuDataItem(this.data);

  final double height = 80.0;

  final _MenuData data;

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      behavior: HitTestBehavior.translucent,
      onTap: (){
        Navigator.of(context).pushNamed(data.routeName);
      },
      child: Container(
        height: height,
        margin: EdgeInsets.fromLTRB(10.0,4.0,10.0,4.0),
        child: Card(
          child: Padding(
              padding: const EdgeInsets.all(16.0),
            child: Row(
              crossAxisAlignment: CrossAxisAlignment.stretch,
              mainAxisAlignment: MainAxisAlignment.start,
              children: <Widget>[
                Padding(
                  padding: EdgeInsets.only(right: 10.0),
                  child: Icon(
                    data.icon,
                    color: Theme.of(context).accentColor,
                  ),
                ),
                Center(
                  child: Text(
                    data.title,
                    style: Theme.of(context).textTheme.subhead,
                  ),
                )
              ],
            ),
          ),
        ),
      ),
    );
  }
}
class _MenuData{

  const _MenuData({
    this.title,
    this.icon,
    this.routeName
  });

  final String title;
  final IconData icon;
  final String routeName;
}


final List<_MenuData> menus = [
  const _MenuData(
    title: 'CircleFloatingMenu',
    icon: Icons.view_module,
    routeName: UIRoute.circleFloatingMenu,
  ),
  const _MenuData(
    title: 'FlutterLake',
    icon: Icons.label,
    routeName: UIRoute.flutterLake,
  ),
  const _MenuData(
    title: 'FlutterTest',
    icon: Icons.book,
    routeName: UIRoute.flutterTest,
  ),
  const _MenuData(
    title:'FlutterWeather',
    icon: Icons.ac_unit,
    routeName: UIRoute.flutterWeather,
  )
];