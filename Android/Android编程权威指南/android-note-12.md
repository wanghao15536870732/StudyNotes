---
title: Android编程权威指南（第2版）学习笔记 --第29章 定制视图与触摸时间 挑战练习
tags:
  - Android
  - Android编程权威指南(第2版)
categories: Android
top: 97
---
![u=1269396152,216456559&fm=26&gp=0.jpg](https://upload-images.jianshu.io/upload_images/9140378-86a4d99c8f8c8470.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
***
<!--more-->

## 创建定制视图
### Android 视图分类
+ 简单视图。简单视图内部也可以很复杂;之所以归为简单类别，是因为简单视图不包括子视图。而且，简单视图几乎总是会执行定制绘制
+ 聚合视图。聚合视图由其他视图对象组成。聚合视图通常管理着子视图，但不负责执行定制绘制。图形绘制任务都委托给了各个子视图

### 创建定制视图三步骤
+ 聚合视图。聚合视图由其他视图对象组成。聚合视图通常管理着子视图，但不负责执行定制绘制。图形绘制任务都委托给了各个子视图
+ 继承选定的超类，并至少覆盖一个超类构造方法
+ 覆盖其他关键方法，以定制视图行为

### 创建BoxDrawingView
#### BoxDrawingView 是一个简单的视图，同时也是View的直接子类
以View为超类，创建一个初始的视图类
```java
public class BoxDrawingView extends View{
   //  Used when creating the view in code
    //  在代码中创建视图时使用
    public BoxDrawingView(Context context){
        this(context,null);
    }

    //  Used when inflating the view from XML
    // 从XML扩展视图时使用
    public BoxDrawingView(Context context, AttributeSet attrs){
        super(context,attrs);
    }
}

```

#### 在布局当中添加该View
+ 注意在引用时我们必须使用自定义 View 的全路径类名，这样布局 inflater 才能够找到它
+ 布局 inflater 解析布局 XML 文件，并按视图定义创建 View 实例。如果元素名不是全路径类名，布局 inflater 会转而在 android.view 和 android.widget 包中寻找目标。如果目标视图类放置在其他包中，布局 inflater 将无法找到目标并最终导致应用崩溃
```html
<?xml version="1.0" encoding="utf-8"?>
<com.example.lab.android.nuc.draganddraw.view.BoxDrawingView
    xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"/>
```
## 处理触摸事件
### 触摸事件简介
+ 监听触摸事件的一种方式是使用一下View的方法，设置一个触摸事件监听器:
```java
public void setOnTouchListener(View.OnTouchListener l)
```
+ 该方法的工作方式与setOnClickListener(View.OnClickListener)相同。实现View.OnTouchListener接口，供触摸事件发生时调用
+ 由于我们定制的视图是View的子类，因此可直接覆盖以下的方法：
```java
public boolean onTouchEvent(MotionEvent event)
```
+ 该方法接受一个MotionEvent类实例，MotionEvent类可用来描述包括位置和动作的触摸事件。动作用于描述事件所处的阶段

|动作常量|动作描述|
| :--:          | :--:                 |
| --------------------------------------------- | ----------------------------------------------- |
| ACTION_DOWN   | 手指触摸到屏幕       |
| ACTION_MOVE   | 手指在屏幕上移动     |
| ACTION_UP     | 手指离开屏幕         |
| ACTION_CANCEL | 父视图拦截了触摸事件 |

### 实现BoxDrawingView视图类
```java
public class BoxDrawingView extends View{
  private static final String TAG = "BoxDrawingView";

  ......

   @Override
    public boolean onTouchEvent(MotionEvent event) {
        PointF current = new PointF( event.getX(),event.getY());
        String action = "";

        switch (event.getActionMasked()){
            case MotionEvent.ACTION_DOWN:
                action = "ACTION_DOWN";

                break;
            case MotionEvent.ACTION_MOVE:
                action = "ACTION_MOVE";

                break;
            case MotionEvent.ACTION_POINTER_DOWN:
                action = "POINTER_DOWN";

                break;
            case MotionEvent.ACTION_UP:
                action = "ACTION_UP";

                break;
            case MotionEvent.ACTION_CANCEL:
                action = "ACTION_CANCEL";

                break;
        }
        Log.e( TAG,action + " at x = " + current.x +
                ",y = " + current.y);
        return true;
    }
}
```
+ 现在X和Y坐标已经封装到PointF对象中，现在需要同时传递这两个坐标值，而Android提供的PointF容器刚好满足了这一需求

## 跟踪运动事件
### 首先，要知道定义矩形的两个坐标点，需要定义一个类用于储存这两个坐标值
新建一个一个 [Box.java](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/DragAndDraw/app/src/main/java/com/example/lab/android/nuc/draganddraw/base/Box.java) 类
```java
public class Box {
    private PointF mOrigin;
    private PointF mCurrent;

    public Box(PointF origin){
        mOrigin = origin;
        mCurrent = origin;
    }
    public void setOrigin(PointF origin) {
        mOrigin = origin;
    }


    public PointF getCurrent() {
        return mCurrent;
    }

    public PointF getOrigin() {
        return mOrigin;
    }

    public void setCurrent(PointF current) {
        mCurrent = current;
    }
}
```
### 添加拖拽生命周期方法  [BoxDrawingView.java](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/DragAndDraw/app/src/main/java/com/example/lab/android/nuc/draganddraw/view/BoxDrawingView.java)
+ 当用户手指在屏幕上滑动时，mCurrentBox。mCurrent会得到更新，在取消触摸事件或用户用手指开屏幕时，我们应清空mCurrentBox以结束屏幕绘制
+ ACTION_MOVE事件发生时调用的invalidate()方法，该方法会强制BoxDrawingView重新绘制自己
```java
public class BoxDrawingView extends View{
  private static final String TAG = "BoxDrawingView";

  private Box mCurrentBox;
  private List<Box> mBoxen = new ArrayList<>( );
  ......

   @Override
    public boolean onTouchEvent(MotionEvent event) {
        PointF current = new PointF( event.getX(),event.getY());
        String action = "";

        switch (event.getActionMasked()){
            case MotionEvent.ACTION_DOWN:
                action = "ACTION_DOWN";
                mCurrentBox = new Box( current);
                mBoxen.add( mCurrentBox );
                break;
            case MotionEvent.ACTION_MOVE:
                action = "ACTION_MOVE";
                if (mCurrentBox != null) {
                  //如果只有一只手指按下，而且还未曾旋转过的话，就进行大小的缩放
                  mCurrentBox.setCurrent(current);
                  invalidate();
                }
                break;
            case MotionEvent.ACTION_UP:
                action = "ACTION_UP";
                mCurrentBox = null;
                break;
            case MotionEvent.ACTION_CANCEL:
                action = "ACTION_CANCEL";
                mCurrentBox = null;
                break;
        }
        Log.e( TAG,action + " at x = " + current.x +
                ",y = " + current.y);
        return true;
    }
}

```

## onDraw(...)方法内的绘制图形
### onDeaw绘制简介
+ 应用启动时，所有视图都处于无效状态。
+ 也就是说，视图还没有绘制到屏幕上。为解决这个问题，Android 调用了顶级 View 视图的 draw()方法。这会引起自上而下的链式调用反应。
+ 首先，视图完成自我绘制，然后是子视图的自我绘制，再然后是子视图的子视图的自我绘制，如此调用下去直至继承结构的末端。
+ 当继承结构中的所有视图都完成自我绘制后，最顶级 View 视图也就生效了。
为加入这种绘制，可覆盖以下 View 方法:
```java
  protected void onDraw(Canvas canvas)
```
+ Canvas 和 Paint 是 Android 系统的两大绘制类:
  + Canvas 类拥有我们需要的所有绘制操作。其方法可决定绘在哪里以及绘什么，比如线条、圆形、字词、矩形等
  + Paint 类决定如何绘制。其方法可指定绘制图形的特征，例如是否填充图形、使用什么字
体绘制、线条是什么颜色等
### 创建Point
```java
public class BoxDrawingView extends View{
   private static final String TAG = "BoxDrawingView";

   private Box mCurrentBox;
   private List<Box> mBoxen = new ArrayList<>( );

   private Paint mBoxPaint;
   private Paint mBackgroundPaint;

  ...

  //  Used when inflating the view from XML
    // 从XML扩展视图时使用
    public BoxDrawingView(Context context, AttributeSet attrs){
        super(context,attrs);

        //Paint the Box a nice semitransparent red (ARGB)
        // 漆成漂亮的半透明红色(ARGB)
        mBoxPaint = new Paint( );
        mBoxPaint.setColor( 0x22ff0000 );

        //Paint the background off-white
        //  白色背景
        mBackgroundPaint = new Paint( );
        mBackgroundPaint.setColor( 0xfff8efe0 );
    }

}
```
+ 有了Point对象的支持，现在可以在屏幕上绘制矩形框了
### 4.3 覆盖onDraw()方法
```java
public class BoxDrawingView extends View{

  ......

    @Override
    protected void onDraw(Canvas canvas) {
        canvas.drawPaint(mBackgroundPaint);

        for (Box box : mBoxen){
            float left = Math.min( box.getOrigin().x,box.getCurrent().x );
            float right = Math.max( box.getOrigin().x,box.getCurrent().x);
            float top = Math.min( box.getOrigin().y,box.getCurrent().y );
            float bottom = Math.max( box.getOrigin().y,box.getCurrent().y);
            canvas.drawRect( left,top,right,bottom,mBoxPaint);
        }
    }

}
```

## 5. 挑战练习
### 5.1 设备旋转问题
+ 修改 [BoxDrawingView.java](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/DragAndDraw/app/src/main/java/com/example/lab/android/nuc/draganddraw/view/BoxDrawingView.java) 类，添加onSaveInstanceState()以及onRestoreInstanceState()方法
+ 使用 Bundle 传递需要存储的参数
```java
public class BoxDrawingView extends View{

  //要给整个视图加上 ID，onSaveInstanceState()以及
  //onRestoreInstanceState()方法才会被调用
    private static final String
            TAG = "BoxDrawingView",
            KEY_SUPER_DATA = "key_super_data",
            KEY_BOXEN = "key_boxen";

    ......

    @Override
    protected Parcelable onSaveInstanceState() {
        Bundle bundle = new Bundle( );
        // 存储父类需要存储的内容
        Parcelable superData = super.onSaveInstanceState();
        bundle.putParcelable(KEY_SUPER_DATA, superData);
        // 存储所有的矩形
        bundle.putSerializable(KEY_BOXEN, (ArrayList) mBoxen);
        invalidate();
        return bundle;
    }

    @Override
    protected void onRestoreInstanceState(Parcelable state) {
        Bundle bundle = (Bundle) state;
        Parcelable superData = bundle.getParcelable( KEY_SUPER_DATA );
        mBoxen = (ArrayList<Box>) bundle.getSerializable( KEY_BOXEN );
        super.onRestoreInstanceState( superData );
        invalidate();
    }

    .....

}
```
### 5.2 旋转矩形框
+ 需要使用 MotionEvent.getActionMasked() 方法来获取事件 ID，处理多点触控
+ ACTION_POINTER_DOWN  指的是屏幕上已经有手指了，并且另一根手指按下的情况，也就是说现在已经指导两个手指都按下了
+ 图形的旋转一般是在绘制的时候旋转画布（canvas），需要的参数有旋转的角度（用度表示）以及旋转中心坐标
+ 在 Box 类中加入最开始的角度 mOriginAngle，已旋转后的角度 mRotatedAngle 两个成员变量，以及一个获取中心点坐标的方法

```java
 public class Box {

    ...

    //此次按下的角度
    private float mOriginAngle;
    private float mCurrentAngle;

    public Box(PointF origin){
        mOrigin = origin;
        mCurrent = origin;
        mOriginAngle = 0;
        mCurrentAngle = 0;
    }

    getter()、setter()方法 ...

      //获取旋转中心坐标
    public PointF getCenter(){
        return new PointF(
                (mCurrent.x + mOrigin.x) / 2,
                (mCurrent.y + mOrigin.y) / 2
        );
    }

}
```
+ 旋转触摸事件处理
```java
@Override
    public boolean onTouchEvent(MotionEvent event) {
        PointF current = new PointF( event.getX(),event.getY());
        String action = "";

        switch (event.getActionMasked()){

            ...

            case MotionEvent.ACTION_MOVE:
                action = "ACTION_MOVE";
                if (mCurrentBox != null) {
                    if (event.getPointerCount() == 1 && mCurrentBox.getCurrentAngle() == 0) {
                        //如果只有一只手指按下，而且还未曾旋转过的话，就进行大小的缩放
                        mCurrentBox.setCurrent(current);
                    }
                    // 如果按下了两根手指
                    if (event.getPointerCount() == 2) {
                        //获取角度
                        float angle = (float) (Math.atan((event.getY(1) - event.getY(0)) /
                                (event.getX(1) - event.getX(0))) * 180 / Math.PI);
                        Log.i(TAG, "onTouchEvent: angle:" + (angle - mCurrentBox.getOriginAngle()));
                        // 已旋转的角度 = 之前旋转的角度 + 新旋转的角度
                        // 新旋转的角度 = 本次 move 到的角度 - 手指按下的角度
                        mCurrentBox.setCurrentAngle(mCurrentBox.getCurrentAngle() + angle
                                - mCurrentBox.getOriginAngle());
                        mCurrentBox.setOriginAngle(angle);
                    }
                    invalidate();
                }
                break;
            case MotionEvent.ACTION_POINTER_DOWN:
                action = "POINTER_DOWN";
                //两根手指同时按下
                if (event.getPointerCount() == 2) {
                    // 首先获取按下时的角度（有一个弧度转角度的过程）
                    // 每次按下的时候将角度存入现在矩形的原始角度
                    float angle = (float) (Math.atan((event.getY(1) - event.getY(0)) /
                            (event.getX(1) - event.getX(0))) * 180 / Math.PI);
                    mCurrentBox.setOriginAngle(angle);
                }
                break;

          ...

        }
        Log.e( TAG,action + " at x = " + current.x +
                ",y = " + current.y);
        return true;
    }
```

***
GIthub 具体代码：[hyyyrwang.github.io](https://github.com/wanghao15536870732/Android-programming-authority-guide/tree/master/DragAndDraw)
