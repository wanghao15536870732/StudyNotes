# Flutter中的状态

_TapboxAState 类:

+ 管理TapboxA的状态.
+ 定义_active：确定盒子的当前颜色的布尔值.
+ 定义_handleTap()函数，该函数在点击该盒子时更新_active,并调用setState()更新UI.
+ 实现widget的所有交互式行为.

ParentWidgetState 类:

+ 为TapboxB 管理_active状态.
+ 实现_handleTapboxChanged()，当盒子被点击时调用的方法.
+ 当状态改变时，调用setState()更新UI.

TapboxB 类:

+ 继承StatelessWidget类，因为所有状态都由其父widget处理.
+ 当检测到点击时，它会通知父widget.

_ParentWidgetState 对象:

+ 管理_active 状态.
+ 实现 _handleTapboxChanged(), 当盒子被点击时调用.
当点击盒子并且_active状态改变时调用setState()更新UI
_TapboxCState 对象:

管理_highlight state.
GestureDetector监听所有tap事件。当用户点下时，它添加高亮（深绿色边框）；当用户释放时，会移除高亮。
当按下、抬起、或者取消点击时更新_highlight状态，调用setState()更新UI。
当点击时，将状态的改变传递给父widget.