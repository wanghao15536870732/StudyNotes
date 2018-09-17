---
title: Android编程权威指南（第2版）学习笔记 --第26章 后台服务
tags:
  - Android
  - Android编程权威指南(第2版)
categories: Android
---

![banner_service.png](https://upload-images.jianshu.io/upload_images/9140378-5ef5aa6209b176c4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
***
<!--more-->


# 本章主要讲解了android 的四大组件之一 -- service

+ 使用AlarmManager延迟服务运行
+ 使用PendingIntent管理定时器
+ 通知信息
+ JobScheduler 和 JobService

## 首先 什么是Service？

### Service 简介

+ 与 activity 一样，服务是一个有生命周期回调方法的应用组件。这些回调方法同样也会在主 UI 线程上运行。
+ 初始创建的服务不会在后台线程上运行任何代码。而大多数重要服务都需要某种后台线程，IntentService 类提供了一套标准实现代码，所以推荐使用 IntentService

### Service 的生命周期

![20161016095658511.png](https://upload-images.jianshu.io/upload_images/9140378-745a0ef6c5cf8814.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/340)

如果是startService(Intent)方法启动的服务，其生命周期很简单，并具有三种生命周期回调方法：

+ onCreate(...)方法:服务创建时调用。
+ onStartCommand(Intent,int,int)方法:每次组件通过 startService(Intent)方法

启动服务时调用一次。它有两个整数参数，一个是标识符集，一个是启动 ID。标识符集用来表示当前 intent 发送究竟是一次重新发送，还是一次从没成功过的发送。每次调用 onStartCommand(Intent,int,int)方法，启动 ID 都会不同。因此，启动 ID 也可用于区分不同的命令。

+ onDestroy()方法:服务不再需要时调用。通常是在服务停止后。 服务停止时会调用 onDestroy()方法。服务停止的方式取决于服务的类型。
+ 服务的类型由 onStartCommand(…)方法的返回值确定，可能的服务类型有
  + Service.START_NOT_STICKY
  + START_REDELIVER_INTENT
  + START_STICKY

### 介绍两种不同类型的 service

#### non-sticky

IntentService是一种non-sticky服务，on-sticky 服务在服务自己认为已完成任务时停止。为获得 non-sticky 服务，应返回START_NOT_STICKY或START_REDELIVER_INTENT。
两者区别在于，如果系统需要在服务完成任务之前关闭它，则服务的具体表现会有所不同。

+ START_NOT_STICKY型服务说消亡就消亡了;
+ 而START_REDELIVER_INTENT型服务则会在资源不再吃紧时，尝试再次启动服务。

选择START_NOT_STICKY还是START_REDELIVER_INTEN，要取决于这个service 对于应用有多重要了，如果不重要，就选择START_NOT_STICKY。

#### sticky 服务

+ sticky 服务会持续运行，直到外部组件调用 Context.stopService(Intent)方法让它停止。 为获得 sticky 服务，应返回 START_STICKY
+ sticky 服务启动后会持续运行，除非某个组件调用 Context.stopService(Intent)方法停止它。如因某种原因需终止服务，可传入一个 null intent 给 onStartCommand(…)方法，实现服务的重启
+ sticky 服务适用于长时间运行的服务，如音乐播放器这种启动后一直保持运行状态，直到用户主动停止的服务

### service的创建跟使用

1.4.1 创建一个名为[PollService.java](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/service/PollService.java)的IntentService子类,用来轮询搜索结果的服务

```java
public class PollService extends IntentService {

    private static final String TAG = "PollService";

    public static Intent newIntent(Context context){
      return new Intent(context,PollService.class);
    }

    public PollService(String name) {
        super( TAG );
    }

    @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
    @Override
    protected void onHandleIntent(@Nullable Intent intent) {
        Log.i( TAG,"Received an intent : " + intent);
    }
}
```

#### 在mainfest配置文件当中添加服务

```html
<service android:name=".service.PollService"/>
```

#### 添加服务启动方法

```java
Intent intent = PollService.newIntent(getActivity());
getActivity().startService(intent);
```

***
##  服务的作用

### 2.1 安全的后台网络连接  使用ConnectivityManager确认网络连接是否可用

#### 检查网络的可用性

```java
public class PollService extends IntentService {
  private static final String TAG = "PollService";
  ...

  @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
    @Override
    protected void onHandleIntent(@Nullable Intent intent) {

        if (isNetWOrkAvailableAndConnected()){
            return;
        }
        Log.i( TAG,"Received an intent : " + intent);
    }

    public boolean isNetWOrkAvailableAndConnected(){
    ConnectivityManager cm = (ConnectivityManager) getSystemService( CONNECTIVITY_SERVICE );
    boolean isNetWorkAvailable = cm.getActiveNetworkInfo() != null;
    boolean isnetworkConnected = isNetWorkAvailable && cm.getActiveNetworkInfo().isConnected();
        return isnetworkConnected;
    }
}
```

#### 获得网络状态权限

```html
<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools"
    package="com.example.lab.android.nuc.photogallery">

    <uses-permission android:name="android.permission.INTERNET" />
    <application
        ...    >
        ...

    </application>
</manifest>
```

### 查找最新的返回结果

#### 更新[QueryPreferences.java](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/Base/QueryPreferences.java)以储存最近一次获取图片的ID

```java
public class QueryPreferences {

    private static final String PREF_LAST_RESULT_ID = "lastResultId";

    public static String getLastResultId(Context context){
        return PreferenceManager.getDefaultSharedPreferences( context )
                .getString( PREF_LAST_RESULT_ID,null);
    }
    public static void setLastResulted(Context context,String lastResult){
        PreferenceManager.getDefaultSharedPreferences( context )
                .edit()
                .putString( PREF_LAST_RESULT_ID,lastResult )
                .apply();
    }
}
```

#### 检查最新返回结果

```java
public class PollService extends IntentService {
  ...

    @Override
    protected void onHandleIntent(@Nullable Intent intent) {

        if (isNetWOrkAvailableAndConnected()){
            return;
        }
        Log.i( TAG,"Received an intent : " + intent);
        String query = QueryPreferences.getStoreQuery( this );
        String lastResultId = QueryPreferences.getLastResultId( this );
        List<GalleryItem> items;

        if (query == null){
            items = new FlickrFetchr().fetchRecentPhotos();
        }else {
            items = new FlickrFetchr().searchPhotos( query );
        }

        if (items.size() == 0){
            return;
        }
        String resultId = items.get( 0 ).getId();
        if (resultId.equals(lastResultId)){
            Log.i( TAG,"Got a old result: " + resultId);
        }else {
            Log.i( TAG,"Got a new result: " + resultId );
        }
        QueryPreferences.setLastResulted( this,resultId );
    }

  ...
}
```

***

## 使用 AlarmManager 延迟运行服务

### 使用PendingIntent管理定时器

#### 什么是PendingIntent?

+ PendingIntent 是一种 token 对象
+ 调用 PendingIntent.getService(…)方法获取 PendingIntent 时，我们告诉操作系统：“请记住， 我需要使用 startService(Intent)方法发送这个 intent。”随后，调用 PendingIntent 对象的 send()方法时，操作系统会按照要求发送原来封装的 intent。
+ PendingIntent 真正精妙的地方在于，将 PendingIntent token 交给其他应用使用时，它是代表当前应用发送 token 对象的。另外，PendingIntent 本身存在于操作系统而不是 token 里。
+ 如果使用同一个 intent 请求 PendingIntent 两次，得到的 PendingIntent 仍会是同一个。我们可借此测试某个 PendingIntent 是否已存在，或撤销已发出的 PendingIntent。

PendingIntent.getService(...) 方法打包了启动服务的方法的调用。它有四个参数:一个用来发送 intent 的 Context，一个区分 PendingIntent 来源的请求代码，一个待发送的 Intent 对象以及一组用来决定如何创建 PendingIntent 的标志符。

### 什么是 AlarmManager？

我们用 AlarmManager.setInexactRepeating(…) 方法开启了定时启动，该方法同样具有四个参数: 一个描述定时器时间基准的常量，定时器启动的时间，定时器循环的时间间隔以及一个到时要发送的 PendingIntent。

+ AlarmManager.ELAPSED_REALTIME 是基准时间值 ， 这表明我们是以 SystemClock. elapsedRealtime()走过的时间来确定何时启动时间的。也就是说，经过一段指定的时间，就启动定时器
+ 如使用 AlarmManager.RTC，启动基准时间就是当前时刻(例如，System. currentTimeMillis())。也就是说，一旦到了某个固定时刻，就启动定时器
+ 时间间隔由我们自己确定，不过推荐使用 AlarmManager 自身定义的常量

由于我们在代码中撤销定时器的同时也撤销了 PendingIntent，所以通过发送一个 PendingIntent.FLAG_NO_CREATE 标志给 getService 方法可以获取这个 PendingIntent 存在状态

### 在PollService当中添加 setServiceAlarm()方法

```java
public class PollService extends IntentService {

  private static final String TAG = "PollService";

  public static void setServiceAlerm(Context context,boolean ison){
      Intent i = PollService.newIntent( context );
      PendingIntent pi = PendingIntent.getService( context,0,i,0 );
      AlarmManager alarmManager = (AlarmManager) context.getSystemService( Context.ALARM_SERVICE );

        if (ison){
            alarmManager.setInexactRepeating( AlarmManager.ELAPSED_REALTIME,
                    SystemClock.elapsedRealtime(),POLL_INTERVAL,pi);
        }else {
            alarmManager.cancel( pi );
            pi.cancel();
        }

        QueryPreferences.setAlarm( context,ison );
    }
}
```

***

## 通知信息

### 如果服务需要与用户沟通，通知信息(notification)总是一个不错的选择。通知信息是指显示在通知抽屉上的消息条目，用户可向下滑动屏幕读取。 想要发送通知信息，首先要创建 Notification 对象,Notification 需使用构造对象来创建。完整的 Notification 至少应包括：

+ 在 Lollipop 之前的设备上，首次显示通知信息时，在状态栏上显示的 ticker text(Lollipop之后，ticker text 不再显示在状态栏上，但仍与可访问性服务相关)
+ 在状态栏上显示的图标(在 Lollipop 之前的设备上，图标在 ticker text 消失后出现);
+ 代表通知信息自身，在通知抽屉中显示的视图
+ 待触发的 PendingIntent，用户点击抽屉中的通知信息时触发

完成 Notification 对象的创建后，可调用 NotificationManager 系统服务的 notify(int, Notification)方法发送它

### 添加newIntent(...)静态方法 [PhotoGalleryActivity.java](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/Activity/PhotoGalleryActivity.java)

```java
public class PhotoGalleryActivity extends SingleFragmentActivity{

    public static Intent newIntent(Context context){
        return new Intent( context,PhotoGalleryActivity.class );
    }

    @Override
    protected Fragment createFragment() {
        return PhotoGalleryFragment.newInstance();
    }
}
```

### 添加通知信息 [Pollservice.java](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/service/PollService.java)

+ 调用 setTicker(CharSequence)和 setSmallIcon (int)方法，配置 ticker text 和小图标
+ setContentTitle (CharSequence)  设置标题
+ setContentText(CharSequence)  显示文字
+ 用户在下拉抽屉中点击 Notification 消息时，传入 setContentIntent(PendingIntent)方法的 PendingIntent 会被触发
+ 调用 setAutoCancel (true)方法可调整上述行为。一旦执行了 setAutoCancel(true)设置方法，用户点击 Notification 消息时，该消息就会从消息抽屉中删除
+ 从当前 context 中取出一个 NotificationManagerCompat 实例，然后调用 Notifi- cationManagerCompat.notify(…)方法贴出消息。传入的整数参数是通知消息的标识符，在整个应用中该值应该是唯一的。如果使用同一 ID 发送两条消息，则第二条消息会替换掉第一条消息

```java
public class PollService extends IntentService {

    .....

    @Override
    protected void onHandleIntent(@Nullable Intent intent) {

        String resultId = items.get( 0 ).getId();
        if (resultId.equals(lastResultId)){
            Log.i( TAG,"Got a old result: " + resultId);
        }else {
            Log.i( TAG,"Got a new result: " + resultId );

            /*
            Notification的通知
             */
            Resources resources = getResources();
            Intent i = PhotoGalleryActivity.newIntent( this );
            PendingIntent pi = PendingIntent.getActivity(this,0,i,0);

            Notification notification = new NotificationCompat.Builder( this )
                    .setTicker( resources.getString( R.string.new_pictures_title))
                    .setSmallIcon( android.R.drawable.ic_menu_report_image )
                    .setContentTitle(resources.getString( R.string.new_pictures_title ))
                    .setContentText( resources.getString( R.string.new_pictures_text ) )
                    .setContentIntent( pi )
                    .setAutoCancel( true )
                    .build();

            showBackgroundNotification( 0,notification );
        }
        QueryPreferences.setLastResulted( this,resultId );
    }

    ......

}

```

***
GIthub 具体代码：[hyyyrwang.github.io](https://github.com/wanghao15536870732/Android-programming-authority-guide/tree/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/service)
