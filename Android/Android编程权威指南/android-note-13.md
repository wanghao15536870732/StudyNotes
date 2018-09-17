---
title: Android编程权威指南（第2版）学习笔记 --第30章 属性动画篇 挑战练习
tags:
  - Android
  - Android编程权威指南(第2版)
categories: Android
top: 98
---
![u=3506959887,3177548658&fm=26&gp=0.jpg](https://upload-images.jianshu.io/upload_images/9140378-1616005242b22d1b.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
***
<!--more-->

#### 属性动画相关的类介绍

+ ObjectAnimator： 动画的执行类
+ ValueAnimator： 动画的执行类
+ AnimatorSet：可以放一起执行的动画集，设置执行的先后顺序，时间等
+ AnimatorInflater： 加载属性动画的xml文件
+ TypeEvaluator： 类型估值，主要用于设置动画操作属性的值，能帮助ObjectAnimator对象精确地计算开始到结束间的递增值
+ TimeInterpolator： 时间插值，用于控制动画执行过程
+ PropertyValuesHolder： 属性存储器，为两个执行类提供更新多个属性的功能
+ Keyframe：为 PropertyValuesHolder提供多个关键帧的操作值
+ AnimatorUpdateListener：动画更新监听
+ AnimatorListener：动画执行监听，在动画开始、重复、结束、取消时进行回调
总的来说，属性动画就是，动画的执行类来设置动画操作的对象的属性、持续时间，开始和结束的属性值，时间差值等，然后系统会根据设置的参数动态的变化对象的属性



#### 深入学习：其他动画 API
[Android属性动画](http://bbs.itheima.com/thread-172632-1-1.html)(出处: 黑马程序员IT技术论坛)

[Hongyang](https://blog.csdn.net/lmj623565791) 的两篇[对属性动画完全解析](http://blog.csdn.net/lmj623565791/article/details/38067475)

a ndroid 4.4引入了[新的视图转场框架](https://www.jianshu.com/p/98f2ec280945)

#### 挑战练习
+ ##### 日落可逆 (点击屏幕，等太阳落下后，再次点击屏幕，让太阳升起来)
```java
public class SunsetFragment extends Fragment {
    private View mSceneView;
    private View mSunView;
    private View mSkyView;
    private int mBlueSkyColor;
    private int mSunsetSkyColor;
    private boolean isSunDown = true; // 是否落日
    private ObjectAnimator sunsetSkyAnimator;
    private ObjectAnimator nightSkyAnimator;
    private float sunYFirstStart;
    private float sunYFirstEnd;
    private boolean isFirstClick = true; // 是否第一次点击
    private ObjectAnimator downAnimatior;
    private AnimatorSet downAnimatorSet;
    private ObjectAnimator upAnimatior;
    private AnimatorSet upAnimatorSet;
    public static SunsetFragment newInstance() {
        return new SunsetFragment();
    }
    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_sunset, container, false);
        mSceneView = view;
        mSunView = view.findViewById(R.id.sun);
        mSkyView = view.findViewById(R.id.sky);
        mBlueSkyColor = ContextCompat.getColor(getActivity(), R.color.blue_sky);
        mSunsetSkyColor = ContextCompat.getColor(getActivity(), R.color.sunset_sky);
        initSkyAnimation();
        mSceneView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (isFirstClick) {
                    sunYFirstStart = mSunView.getTop();
                    sunYFirstEnd = mSkyView.getHeight();
                    initUpDownAnimation();
                }
                isFirstClick = false;
                if(!downAnimatorSet.isRunning() && !upAnimatorSet.isRunning()){
                    if (isSunDown) {
                        downAnimatorSet.start();
                    } else {
                        upAnimatorSet.start();
                    }
                    isSunDown = !isSunDown;
                }
            }
        });
        return view;
    }
    // 初始化落日，升日动画
    private void initUpDownAnimation() {
        downAnimatior = ObjectAnimator.ofFloat(mSunView, "y", sunYFirstStart, sunYFirstEnd).setDuration(3000);
        downAnimatior.setInterpolator(new AccelerateInterpolator());
        downAnimatorSet = new AnimatorSet();
        downAnimatorSet.play(downAnimatior).with(sunsetSkyAnimator);
        upAnimatior = ObjectAnimator.ofFloat(mSunView, "y", sunYFirstEnd, sunYFirstStart).setDuration(3000);
        upAnimatior.setInterpolator(new AccelerateInterpolator());
        upAnimatorSet = new AnimatorSet();
        upAnimatorSet.play(upAnimatior).with(nightSkyAnimator);
    }
    // 初始化天空颜色两种动画
    private void initSkyAnimation() {
        sunsetSkyAnimator = ObjectAnimator.ofInt(mSkyView, "backgroundColor", mBlueSkyColor, mSunsetSkyColor).setDuration(3000);
        sunsetSkyAnimator.setEvaluator(new ArgbEvaluator());
        nightSkyAnimator = ObjectAnimator.ofInt(mSkyView, "backgroundColor", mSunsetSkyColor, mBlueSkyColor).setDuration(3000);
        nightSkyAnimator.setEvaluator(new ArgbEvaluator());
    }
}
```

+ ##### 添加太阳的动画特效,让它有规律的放大或缩小或是加一圈的光线(这实际上就是反复执行一段动画，可以考虑使用ObjectAnimator的setRepeatCount(int) 的方法)

+ ##### 在日落过程当实现动画反转，在太阳慢慢下来时点击屏幕，让太阳无缝的回升至原来所在的位置
<br>
参考大神简书 [https://www.jianshu.com/p/b0ddebfa1ee0](https://www.jianshu.com/p/b0ddebfa1ee0)

***
GIthub 具体代码：[hyyyrwang.github.io](https://github.com/wanghao15536870732/Android-programming-authority-guide/tree/master/Sunset)
