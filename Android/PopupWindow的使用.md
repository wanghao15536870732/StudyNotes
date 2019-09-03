# PopupWindow的使用

## 创建

> 通过上下文创建PopupWindow, 创建后默认有一个透明的背景.默认宽高(0,0), 没有内容和焦点的PopupWindow

```java
PopupWindow ()	// 创建一个空的PopupWindow

PopupWindow (View contentView)	

PopupWindow (int width, 
                int height)

PopupWindow (View contentView, 	// PopupWindow的内容View, 相当于setContentView
                int width, 	// 宽, 相当于setwidth()
                int height,  // 高, 相当于setHeight
                boolean focusable) // 是否可获取焦点, 相当于setFocusable()

```

> 创建PopupWindow必要的三个条件

```java
void setHeight (int height) // 因为PopupWindow没有默认布局所以必须指定宽高
void setWidth (int width)
void setContentView (View contentView) // 需要显示的内容
```

> 用到LayoutParams.WRAP_CONTENT包裹布局. 布局多大就显示多大的PopupWindow

```java
PopupWindow popupWindow = new PopupWindow(popupView, ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT, true);
```

## 显示

> 显示PopupWindow的两种方式

+ 1.随着某个控件`showAsDropDown`
+ 2.设置屏幕坐标`showAtLocation`

## 隐藏PopupWindow

```jav
void dismiss();
```

## 状态

### 可被点击

```java
boolean isTouchable() //判断是否可被点击
void setTouchable (boolean touchable)  //设置是否可被点击
```

### 多点触控

```java
void setSplitTouchEnabled(boolean enabled)
boolean isSplitTouchEnabled()
```

### 忽略CheekPress事件(即物体触摸在屏幕上的尺寸超过手指尺寸范围)

```java
void setIgnoreCheekPress()  //默认为false,即不忽略
```

### 外部点击取消

```java
void setOutsideTouchable(boolean touchable)  //设置外部是否可被点击
boolean isOutsideTouchable()
```

### 解决NavigationBar重叠

```java
void setAttachedInDecor(boolean enabled)
```

### 可获取焦点

> 当PopupWindow可获取焦点时按下手机返回键将不会销毁当前Activity而是关闭当前PopupWindow.为了更加符合用户操作逻辑，一般还是设置为true

```java
void setFocusable(boolean focusable)
boolean isFocusable()
```

### 设置背景

```java
void setBackgroundDrawable(Drawable background)
Drawable getBackground()
```

### 设置阴影

```java
void setElevation(float elevation)
float getElevation()
```

### 设置PopupWindow宽和高

```java
void setWindowLayoutMode(int widthSpec,int heightSpec) //该方法在API23后被舍弃，由setWidth(int) 和 setHeight(int) 代替
```

### 窗口裁剪

> PopupWindow默认是不会超出屏幕边界的，但是党该方法为false时会采用精准位置，曹处屏幕范围

```java
void setClippingEnable(boolean enabled)
boolean isClippingEnabled()
```

## 动画效果

### 设置动画

```java
void setAnimationStyle(int animationStyle)
int getAnimationStyle()
```

> 传入一个Style样式的id,分别由两个属性组成，各代表

```html
<style name="popupwindow_animation_style">
    <item name="android:windowEnterAnimation">@anim/dialog_bottom_enter</item>
    <item name="android:windowExitAnimation">@anim/dialog_bottom_exit</item>
</style>
```

### 进场和退场动画

> 在Android6.0(API 23)后加入的方法. 配合Material Design的转场动画使用

+ 进场动画

```java
void setEnterTransition(Translition enterTransition)
Transition getEnterTransition()
```

+ 退场动画

```java
void setExitTransition(Transition exitTransition)
Transition getExitTransition()
```

## 获取

### 获取最大高度

> PopupWindow使用showAsDropDown()能够显示的最大高度

```java
int getMaxAvailableHeight(View anchor)

int getMaxAvailableHeight(View anchor,int yOffset)  //控件Y轴偏移后可显示的最大高度
int getMaxAvailableHeight(View anchor,int yOffset,boolean ignoreBottomDecorations)

```

## 输入模式

> 针对PoPupWindow中包含EditText控件

```java
void setInputMethodMode (int mode)
int getInputMethodMode ()
```

+ INPUT_METHOD_FROM_FOCUSABLE 根据可否获取焦点判断是否可输入
+ INPUT_METHOD_NEEDED 允许输入
+ INPUT_METHOD_NOT_NEEDED 不允许输入

### 软键盘模式

```java
void setSoftInputMode (int mode) // mode为WindowManager.LayoutParams的softInputMode常量
int getSoftInputMode ()
```

> 显示状态模式

+ SOFT_INPUT_STATE_UNSPECIFIED 默认模式
+ SOFT_INPUT_STATE_ALWAYS_HIDDEN 总是隐藏
+ SOFT_INPUT_STATE_ALWAYS_VISIBLE 自动弹出软键盘

> 调整模式

+ SOFT_INPUT_ADJUST_UNSPECIFIED 默认模式
+ SOFT_INPUT_ADJUST_RESIZE 软键盘弹出后PopupWindow会自动调整坐标,不被遮挡

## 监听事件

### 隐藏事件监听(执行dismiss()后的方法)

```java
void setOnDismissListener(PopupWindow.OnDismissListener onDismissListener)
```

### 触摸事件拦截

> 只有PopupWindow处于被显示的状态下才可更新

###

```java
void setTouchIntercepter(View.onTouchListener l)
```

## 更新

### 更新状态

> 该方法不能更新PopupWindow的宽高, 只能更新PopupWindow的状态

```java
void update()
```

### 更新尺寸

```java
void update (int width,int height)// 更新PopupWindow的宽高
```

### 更新显示位置

> 相当于重新showAsDropDown,相对于控件的位置更新

```java
void update (View anchor,int width,int height) // 更新显示控件的位置

void update (View anchor,int xoff,int yoff,int width,int height)// 相对于控件的偏移值
```

> `showAtLocation`的相对原点是自身位置.

```java
void update (int x,int y,// 坐标偏移
        int width,int height)// PopupWindow宽高
  
void update (int x,int y,int width, int height,
        boolean force) // 可获取焦点
```


## 参考

>  掘金[刘强东](https://juejin.im/user/57c9a80379bc440063f3e0dc)的[PopupWindow最全使用说明](https://juejin.im/post/58ed82c3a22b9d0063469e98)
