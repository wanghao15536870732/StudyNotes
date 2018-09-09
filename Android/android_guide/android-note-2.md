---
title: Android编程权威指南（第2版）--第13章 工具栏 挑战练习
tags:
  - Android
  - Android编程权威指南(第2版)
categories: Android
top: 87
---
***
<!--more-->

## 13.6 挑战练习：删除crime记录

### 这个比较简单，分三步

+ #### 第一步创建一个button

+ #### 第二步在CrimeLab增加删除方法
```java
public void removeCrime(Crime c) {
        mCrimes.remove(c);
    }
```
+ #### 第三步修改CrimeFragment.java的onCreateView方法，绑定按钮，增加监听事件
```java
mRemoveButton = (Button) v.findViewById(R.id.crime_remove_button);
        mRemoveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                CrimeLab.get(getActivity()).removeCrime(mCrime);
                getActivity().finish();
            }
        });
```

***


## 13.7 挑战练习：优化字符串资源显示
### 这个按照书本的代码进行修改即可,效果如如下:
</br>
<center>

![Criminallntent](https://upload-images.jianshu.io/upload_images/9140378-3ef7b2ce25207bb6.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

</center>

</br>

***

## 13.8 挑战练习：用于RecyclerView的空视图
### 修改fragment_crime_list.xml
#### 原本只有一个RecyclerView组建，现在增加父组建，并增加一个textview和一个button
```java
<?xml version="1.0" encoding="utf-8"?>
<RelativeLayout
    xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent">

    <RecyclerView
        xmlns:android="http://schemas.android.com/apk/res/android"
        android:id="@+id/crime_recycler_view"
        android:layout_width="match_parent"
        android:layout_height="match_parent"/>

    <TextView
        android:id="@+id/no_crime_textview"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:text="@string/no_crime"
        android:layout_centerInParent="true"
        android:layout_marginLeft="16dp"
        android:gravity="center"
        android:layout_marginRight="16dp"
        style="?android:listSeparatorTextViewStyle"
        android:layout_margin="15dp"/>

    <Button
        android:id="@+id/no_crime_add_button"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:layout_below="@+id/no_crime_textview"
        android:layout_marginLeft="16dp"
        android:layout_marginRight="16dp"
        android:text="@string/add_crime"
        android:background="@drawable/bt_selector"/>


</RelativeLayout>
```

#### string.xml里面加上

```html
<string name="no_crime">没有crime记录可以显示</string>
```
### 修改CrimeListFragment.java
#### 增加两个变量
```java
private TextView mNoCrimeTextView;
private Button mNoCrimeButton;
```
#### 修改onCreateView方法为上面两个变量绑定id组件

#### 修改updateUI()增加如下代码
```java
 public void updateUI(){

        CrimeLab crimeLab = CrimeLab.get(getActivity());

        List<Crime> crimes = crimeLab.getCrimes();
        //如果没有配置好CrimeAdapter,就创建一个CrimeAdapter
        if (mAdapter == null){
            //创建RecyclerAdapter
            mAdapter = new CrimeAdapter(crimes);
            // 然后设置给RecyclerView
            mCrimeRecyclerView.setAdapter(mAdapter);
        }else{
            //如果已经配置好CrimeAdapter，就调用notifyDataSetChanged()
            // 方法修改updateUI()方法
            mAdapter.setCrimes(crimes);
//            mAdapter.notifyDataSetChanged();
            //实现高效的RecyclerView刷新方法

            //如果想要刷新删除crime之后的CrimeListFragment，
//            mAdapter.notifyItemChanged( mIndex );  //单例更新  -- 会报错
            mAdapter.notifyDataSetChanged();  //全量更新
        }
```
```jkava
        /*
        挑战练习 用于RecyclerView的空列表
         */
        if (crimes.size() == 0){
            mNoCrimetextView.setVisibility( View.VISIBLE );
            mNoCrimeButton.setVisibility( View.VISIBLE );
        }else {
            mNoCrimeButton.setVisibility( View.GONE );
            mNoCrimetextView.setVisibility( View.GONE );
        }
```
```java
        updateSubtitle();
    }

```

</br>

Github具体代码：[hyyyrwang.github.io](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/Criminallntent2/app/src/main/java/com/example/lab/android/nuc/criminallntent/Fragment/CrimeListFragment.java)<br>
我的简书：[https://www.jianshu.com/p/3196eac17739](https://www.jianshu.com/p/3196eac17739)
***
