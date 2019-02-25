import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter_lake/CircleFloatingMenu/menu/circle_floating_menu.dart';
import 'package:flutter_lake/CircleFloatingMenu/menu/floating_button.dart';
import 'package:oktoast/oktoast.dart';

class FloatingMenuPage extends StatelessWidget{
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('CirCleFloatingMenu'),
      ),
      body: Stack(
        children: <Widget>[
          Positioned(
            width: 300.0,
            height: 300.0,
            child: CircleFloatingMenu(
              menuSelected: (index){
                showToast('You choose NO.$index');
              },
              startAngle: degToRad(-90.0),
              endAngle: degToRad(90.0),
              floatingButton: FloatingButton(
                icon: Icons.add,
                size: 30.0,
                color: Colors.redAccent,
              ),
              subMenus: <Widget>[
                FloatingButton(
                  icon: Icons.widgets,
                ),
                FloatingButton(
                  icon: Icons.book,
                ),
                FloatingButton(
                  icon: Icons.translate,
                ),
                FloatingButton(
                  icon: Icons.alarm_add,
                ),
                FloatingButton(
                  icon: Icons.bluetooth,
                )
              ],
            ),
          ),
          Positioned(
            width: 300.0,
            height: 200.0,
            bottom: 12.0,
            right: 1.0,
            child: CircleFloatingMenu(
              menuSelected: (index){
                showToast('You Choose NO.$index');
              },
                floatingButton: FloatingButton(
                  color: Colors.green,
                  icon: Icons.add,
                  size: 30.0,
                ),
                subMenus:<Widget>[
                  FloatingButton(
                    icon: Icons.widgets,
                    elevation: 0.0,
                  ),
                  FloatingButton(
                    icon: Icons.translate,
                    elevation: 0.0,
                  ),
                  FloatingButton(
                    icon: Icons.alarm_add,
                    elevation: 0.0,
                  ),
                  FloatingButton(
                    icon: Icons.bluetooth,
                    elevation: 0.0,
                  ),
                ],
            ),
          )
        ],
      ),
    );
  }
}