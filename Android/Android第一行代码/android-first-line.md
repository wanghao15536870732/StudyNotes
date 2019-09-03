---
title: Android第一行代码(第三版) 解决RecyclerView遮住Toolber的问题
tags:
  - Android
  - Android第一行代码
categories: Android
top: 85
---
***
<!--more-->
## 解决RecyclerView遮住Toolber的问题

### 遮住的问题就像这张图片一样，来的太快，就像龙卷风.......
​

​​![logo.png](https://upload-images.jianshu.io/upload_images/9140378-5b3a1a91ea6a4ef2.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/240)

### 搞了半天这是神马情况
![这是神马情况](https://upload-images.jianshu.io/upload_images/9140378-a60dae556ca7093e.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/140)

***

### 还是静下心来分析一下为什么RecyclerView会把Toolber遮住吧

#### 首先看一下布局文件的代码
```java
<android.support.v4.widget.DrawerLayout
    xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    android:id="@+id/drawer_layout"
    android:layout_height="match_parent"
    android:layout_width="match_parent" >

    <android.support.design.widget.CoordinatorLayout
        android:layout_width="match_parent"
        android:layout_height="match_parent">

        <android.support.design.widget.AppBarLayout
            android:layout_width=""
            android:layout_height="">

        </android.support.design.widget.AppBarLayout>

        <android.support.v7.widget.Toolbar
            android:id="@+id/toolbar"
            android:layout_width="match_parent"
            android:layout_height="?attr/actionBarSize"
            android:background="?attr/colorPrimary"
            android:theme="@style/ThemeOverlay.AppCompat.Dark.ActionBar"
            app:popupTheme="@style/ThemeOverlay.AppCompat.Light"/>

        <android.support.v7.widget.RecyclerView
            android:id="@+id/recycler_view"
            android:layout_width="match_parent"
            android:layout_height="match_parent"/>

        <android.support.design.widget.FloatingActionButton
            android:id="@+id/fab"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_gravity="bottom|end"
            android:layout_margin="16dp"
            android:src="@drawable/ic_done"
            android:elevation="8dp"/>
        <com.example.lab.android.nuc.materialtest.DragFloatActionButton
            android:id="@+id/fab_move"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_gravity="bottom|start"
            android:layout_margin="16sp"
            android:src="@drawable/ic_add"/>
    </android.support.design.widget.CoordinatorLayout>

    <!--<TextView-->
        <!--android:layout_width="match_parent"-->
        <!--android:layout_height="match_parent"-->
        <!--android:layout_gravity="start"-->
        <!--android:text="This is menu"-->
        <!--android:textSize="30sp"-->
        <!--android:background="#FFF"/>-->

    <android.support.design.widget.NavigationView
        android:id="@+id/nav_view"
        android:layout_height="match_parent"
        android:layout_width="match_parent"
        android:layout_gravity="start"
        app:menu="@menu/nav_menu"
        app:headerLayout="@layout/nav_header" />

</android.support.v4.widget.DrawerLayout>
```
#### 可以清楚的看到RecyclerView跟Toolbar都是放在CoordinatorLayout当中的

想必大家都很清楚
```java
CoordinatorLayout 就是加强版的FrameLayout
```
但是FrameLayout中的控件在不进行明确定位的情况下，默认都会摆放到左上角
那这咋整？

#### 传统情况下，使用偏移是唯一的解决办法
![download.jpg](https://upload-images.jianshu.io/upload_images/9140378-b58b166567b60a1b.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/240)

但是我们使用的可不是普通的FrameLayout，而是CoordinatorLayout，因此自然会有一些更加巧妙地方法了

#### 即：Design support库中提供的另外的一个工具——AppBarLayout
那么我们怎样用AppBarLayout才能解决前面的覆盖问题呢？
其实只需要两步就可以了：
+ 将ToolBar嵌套到AppBarLayout中
+ 给RecyclerView指定一个布局行为

#### 将布局代码更改为:
```java
<android.support.v4.widget.DrawerLayout
    xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    android:id="@+id/drawer_layout"
    android:layout_height="match_parent"
    android:layout_width="match_parent" >

    <android.support.design.widget.CoordinatorLayout
        android:layout_width="match_parent"
        android:layout_height="match_parent">

        <android.support.design.widget.AppBarLayout
            android:layout_width="match_parent"
            android:layout_height="match_parent">
            <android.support.v7.widget.Toolbar
                android:id="@+id/toolbar"
                android:layout_width="match_parent"
                android:layout_height="?attr/actionBarSize"
                android:background="?attr/colorPrimary"
                android:theme="@style/ThemeOverlay.AppCompat.Dark.ActionBar"
                app:popupTheme="@style/ThemeOverlay.AppCompat.Light"/>
        </android.support.design.widget.AppBarLayout>

        <android.support.v7.widget.RecyclerView
            android:id="@+id/recycler_view"
            android:layout_width="match_parent"
            android:layout_height="wrap_content" //谨记这里不是match_view，我自己就错在这里了
            app:layout_behavior="@string/appbar_scrolling_view_behavior"/>

        <android.support.design.widget.FloatingActionButton
            android:id="@+id/fab"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_gravity="bottom|end"
            android:layout_margin="16dp"
            android:src="@drawable/ic_done"
            android:elevation="8dp"/>
        <com.example.lab.android.nuc.materialtest.DragFloatActionButton
            android:id="@+id/fab_move"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_gravity="bottom|start"
            android:layout_margin="16sp"
            android:src="@drawable/ic_add"/>
    </android.support.design.widget.CoordinatorLayout>

    <!--<TextView-->
        <!--android:layout_width="match_parent"-->
        <!--android:layout_height="match_parent"-->
        <!--android:layout_gravity="start"-->
        <!--android:text="This is menu"-->
        <!--android:textSize="30sp"-->
        <!--android:background="#FFF"/>-->

    <android.support.design.widget.NavigationView
        android:id="@+id/nav_view"
        android:layout_height="match_parent"
        android:layout_width="match_parent"
        android:layout_gravity="start"
        app:menu="@menu/nav_menu"
        app:headerLayout="@layout/nav_header" />

</android.support.v4.widget.DrawerLayout>
```

#### 效果如图：

![df.png](https://upload-images.jianshu.io/upload_images/9140378-52c875c3f6e39aa7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/240)

***
#### 此外在Toolbar里面添加一行代码就会显得更人性化
```java
<android.support.v7.widget.Toolbar
   android:id="@+id/toolbar"
   android:layout_width="match_parent"
   android:layout_height="?attr/actionBarSize"
   android:background="?attr/colorPrimary"
   android:theme="@style/ThemeOverlay.AppCompat.Dark.ActionBar"
   app:popupTheme="@style/ThemeOverlay.AppCompat.Light"
   app:layout_scrollFlags="scroll | enterAlways | snap"/>
```
#### 几种布局行为
+ scroll <br>
当RecyclerView向上滚动的时候，ToolBar会跟着一起向上滚动并实现隐藏
+ enterAlways <br>
当RecyclerView向下滚动的时候，Toolbar会跟着一起向下滚动并重新显示
+ snap <br>
当ToolBar还没有隐藏或者显示的时候，会根据当前滚动的距离，自动选择时显示还是隐藏


***
