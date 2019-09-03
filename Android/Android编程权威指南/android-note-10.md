---
title: Android编程权威指南（第2版）学习笔记 --第27章 broadcast intent
tags:
  - Android
  - Android编程权威指南(第2版)
categories: Android
top: 95
---
![u=2555228228,3915540837&fm=26&gp=0.jpg](https://upload-images.jianshu.io/upload_images/9140378-1773d93c6af667ff.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
***
<!--more-->

## <center>本章主要讲解了如何监听系统发送的broadcast intent,以及如何使用broadcast receiver处理他们</center>

## 一般 intent 跟 broadcast intent
许多系统组件需要知道某些事件的发生。为满足这样的需求，Android 提供了 broadcast intent 组件。broadcast intent 的工作原理类似于之前学过的 intent , 唯一不同的是 broadcast intent 可同时被多个叫作 broadcast receiver 的组件接收

![img01.png](https://upload-images.jianshu.io/upload_images/9140378-c871428744753940.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/600)

### 接受broadcast：重启后唤醒
#### standalone receiver

standalone receiver 是一个在 manifest 配置文件中声明的 broadcast receiver。即便应用进程已消亡，standalone receiver 也可以被激活。(另一种就是可以同 fragment 或 activity 的生命周期绑定的 dynamic receiver。)

首先建立这样一个 BroadcastReceive新类，继承android.content.BroadcastReceive新类
```java
public class StartupReceiver extends BroadcastReceiver {

    private static final String TAG = "StartupReceiver";

    @Override
    public void onReceive(Context context, Intent intent) {
        Log.i( TAG,"Received broadcast intent: " + intent.getAction() );
    }
}
```
#### 在mainfest文件当中添加receiver
```html
<receiver android:name=".receiver.StartupReceiver">
    <intent-filter>
          <action android:name="android.intent.action.BOOT_COMPLETED"/>
    </intent-filter>
</receiver>
```
## 过滤前台通知消息
解决了重启后的唤醒问题，还有一个缺陷，通知消息修然很有用，但是应用开着时不应该收到通消息，因此，我们改进方案，同样,我们使用 broadcast intent来解决这个题,但用法和以前完全不同
+ 首先,我们发送(或接收)定制版 broadcast intent(最后会锁定它,只允许 PhotoGallery 应用部件接收它)
+ 其次,不再使用 manifest文件，改用代码为 broadcast intent动态登记 receiver
+ 最后发送一个有序 Broadcast 在一组 receiver 中传递数据,借此保证最后才运行某个 receiver

### 发送 broadcast intent
只需要创建一个intent,并创建一个intent,并传入sendBroadcast(Intent) 即可
```java
public class PollService extends IntentService {
    public static final String ACTION_SHOW_NOTIFICATION =
            "com.example.lab.android.nuc.photogallery.SHOW_NOTIFICATION";

    @Override
    protected void onHandleIntent(@Nullable Intent intent) {

      ...

        String resultId = items.get( 0 ).getId();
        if (resultId.equals(lastResultId)){
            Log.i( TAG,"Got a old result: " + resultId);
        }else {
            Log.i( TAG,"Got a new result: " + resultId );

            ...


             NotificationManagerCompat notificationManagerCompat =
                     NotificationManagerCompat.from( this );
             notificationManagerCompat.notify(0,notification);

             sendBroadcast( new Intent( ACTION_SHOW_NOTIFICATION ) );

            showBackgroundNotification( 0,notification );
        }
        QueryPreferences.setLastResulted( this,resultId );
    }

    ......

}
```
### 动态 broadcast receiver
我们要只在应用开启的时候接受发过来的广播过滤，就不能在 manifest 中声明一个过滤器，而是要动态地建立一个广播接收器,新建[VisiblaFragment.java](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/Fragment/VisibleFragment.java)类，继承Fragment类，如果想在 Fragment.onCreate(Bundle)和 Fragment.onDestroy()方法中实现登记或撤销登记，应使用 getActivity().getApplicationContext()方法
```java
ublic abstract class VisibleFragment extends Fragment {

    private static final String TAG = "VisibleFragment";

    @Override
    public void onStart() {
        super.onStart();
        IntentFilter filter = new IntentFilter(PollService.ACTION_SHOW_NOTIFICATION );
        getActivity().registerReceiver( mOnShowNotification,filter,
                PollService.PERM_PRIVATE,null);
    }

    @Override
    public void onStop() {
        super.onStop();
        getActivity().unregisterReceiver( mOnShowNotification );
    }

    private BroadcastReceiver mOnShowNotification = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
           Toast.makeText( getActivity(),
                   "Got a broadcast:" + intent.getAction(),
                   Toast.LENGTH_SHORT )
                   .show();
        }
    };
}

```
### 使用有序 broadcast

![download.png](https://upload-images.jianshu.io/upload_images/9140378-48f8638b9671e6a5.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 发送有序broadcast [Pollservice.java](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/service/PollService.java)
```java
public class PollService extends IntentService {

    private static final String TAG = "PollService";
    public static final String REQUEST_CODE = "REQUEST_CODE";
    public static final String NOTIFICATION = "NOTIFICATION";

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

            // Resources resources = getResources();
            // Intent i = PhotoGalleryActivity.newIntent( this );
            // PendingIntent pi = PendingIntent.getActivity(this,0,i,0);
            //
            // Notification notification = new NotificationCompat.Builder( this )
            //         .setTicker( resources.getString( R.string.new_pictures_title))
            //         .setSmallIcon( android.R.drawable.ic_menu_report_image )
            //         .setContentTitle(resources.getString( R.string.new_pictures_title ))
            //         .setContentText( resources.getString( R.string.new_pictures_text ) )
            //         .setContentIntent( pi )
            //         .setAutoCancel( true )
            //         .build();

            //摈弃之前无序broadcast的方法
//            NotificationManagerCompat notificationManagerCompat =
//                    NotificationManagerCompat.from( this );
//            notificationManagerCompat.notify(0,notification);
//
//            sendBroadcast( new Intent( ACTION_SHOW_NOTIFICATION ) );

            showBackgroundNotification( 0,notification );
        }
        QueryPreferences.setLastResulted( this,resultId );
    }


    /**
     * 新建新的方法，用于发送有序的broadcast
     */
    private void showBackgroundNotification(int requesCode,Notification notification){
        Intent i = new Intent( ACTION_SHOW_NOTIFICATION );
        i.putExtra( REQUEST_CODE,requesCode );
        i.putExtra( NOTIFICATION,notification );
        sendOrderedBroadcast(i,PERM_PRIVATE,null,null ,
                Activity.RESULT_OK,null,null);
    }
}
```
#### 实现 result receiver
新建一个[NotificationReceiver.java](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/receiver/NotificationReceiver.java)类，继承broadcastReceiver类
```java
/**
 * 用于接受PollService当中发出的有序broadcast
 */

public class NotificationReceiver extends BroadcastReceiver {

    private static final String TAG = "NotificationReceiver";

    @Override
    public void onReceive(Context context, Intent intent) {
        Log.i( TAG,"received result: " + getResultData() );

        if (getResultCode() != Activity.RESULT_OK){
            return;
        }

        int requestCode = intent.getIntExtra( PollService.REQUEST_CODE,0 );
        Notification notification = (Notification)
                intent.getParcelableExtra( PollService.NOTIFICATION );
        NotificationManagerCompat notificationManagerCompat =
                NotificationManagerCompat.from( context );
        notificationManagerCompat.notify( requestCode,notification );

    }
}
```
#### 登记notification receiver
```html
<manifest ...>

  <applocation
      ... >

        <receiver android:name=".receiver.NotificationReceiver"
            android:exported="false">
            //制定为最小级，保证最后接受
            <intent-filter android:priority="-999">
                <action android:name="com.example.lab.android.nuc.photogallery.SHOW_NOTIFICATION"/>
            </intent-filter>
        </receiver>

        <service android:name=".service.JobSchedulerService"
            android:exported="false">
        </service>
    </applocation>
</manifest>
```
***

Github 具体代码：[hyyyrwang.github.io](https://github.com/wanghao15536870732/Android-programming-authority-guide/tree/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/receiver)
