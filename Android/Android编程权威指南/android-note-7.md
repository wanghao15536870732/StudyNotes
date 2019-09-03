---
title: Android编程权威指南（第2版）学习笔记 --第24章 Looper、Handler和HandlerThread
tags:
  - Android
  - Android编程权威指南(第2版)
categories: Android
top: 92
---
![16091G34644-2.jpg](https://upload-images.jianshu.io/upload_images/9140378-da4d73fe4993a1f5.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
***
<!--more-->
## <center>本文主要讲解了Looper、Handler和HandlerThread的关系以及如何使用它们进行线程间的交互</center>

## 定义
### Looper
Android 系统中，线程有一个消息队列(message queue)。使用消息队列的线程叫作消息循环(message loop)。消息循环会循环检查队列上是否有新消息。消息循环由线程和 looper 组成。Looper 对象管理着线程的消息队列。
主线程就是个消息循环，因此也拥有 looper。主线程的所有工作都是由其 looper 完成的。looper 不断从消息队列中抓取消息，然后完成消息指定的任务
### message
Message 类是 Handler 的子类用于 Handler 传递消息，它有好几个实例变量，其中有三个需在实现时定义

+ What  用户定义的 int 型消息代码，用来描述消息。
+ obj 随消息发送的用户指定对象
+ target 处理消息的handler

Message的目标是Handler类的一个实例，Handler可看作message handler的简称，创建Message时，他会自动的与一个Handler相关联。Message待处理时，Handler对象负责触发消息处理事件
### Handler
要处理消息以及消息制定的任务，首先需要一个Handler的实例，Handler不仅仅是处理Message的target，也是创建跟发布Message的接口.通常不需要手动设置消息的目标

### 三者的关系


![timg.jpg](https://upload-images.jianshu.io/upload_images/9140378-3c5e11827ddfcd6e.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/440)

+ Looper拥有Message收件箱,所以 (Message必须在 Looper上发布或处理,既然有这层关系
为与 Looper协同工作, Handler总是引用着它。
+ 一个 Handler与一个 Looper相关联,一个 Message也仅与一个目标 HandLer(也称作Message目标)相关联。Looper拥整个Message队列,多个Message可以引用同一目标Handler。
+ 多个 Handler也可与一个 Looper相关联。这意味着一个 Handler的 Message可能与另
 Handler的 Message存放在同一消息队列中。
***

## HandlerThread
### ThumbnailDownloader.java 此处略去几十行代码
```java
public class ThumbnailDownloader<T> extends HandlerThread{
    private static final String TAG = "ThumbnailDownloader";
    private static final int MESSAGE_DOWNLOAD = 0;
    private static final int MESSAGE_PRELOAD = 1;
    private boolean mHasQuit = false;
    private Handler mRequestHandler;
    //该方法是在Looper首次检查消息队列之前调用的
    // 该方法成了建立Handler的最好地方了
    protected void onLooperPrepared() {
        mRequestHandler = new Handler(){
            @Override
            public void handleMessage(Message msg) {
                //先检查消息类型，在获取obj的值(T类型下载请求)
                if (msg.what == MESSAGE_DOWNLOAD){

            }else if (msg.what == MESSAGE_PRELOAD){

                }
            }
        };
        int maxCacheSize = 4 * 1024 * 1024; //4MB
        mCache = new LruCache<>(maxCacheSize);
    }


    //创建名为queueThumbnai的存根方法
    //需要一个T类型对象
    public void queueThumbnail(T target,String url){
        Log.i(TAG,"Got a URL: " + url);
        if (url == null){

        }else {

        }
    }

    public void queuePreloadThumbnail(String url) {
//        Log.i(TAG, "queuePreloadThumbnail: Got a URL: " + url);
        mRequestHandler.obtainMessage(MESSAGE_PRELOAD, url).sendToTarget();
    }

    //添加消息清理机制
    public void clearQueue() {
        mRequestHandler.removeMessages(MESSAGE_DOWNLOAD);
        mRequestHandler.removeMessages(MESSAGE_PRELOAD);
    }

}

```

### 主线程中

```java

mThumbnailDownloader = new ThumbnailDownloader<>();
mThumbnailDownloader.start();
mThumbnailDownloader.getLooper();
// 在需要的时候调用
mThumbnailDownloader.queueThumbnail(holder, url);

```
***
## 线程交互
### 下载线程
```java
    //创建一个变量用于储存Handler变量的值
    private Handler mResponseHandler;
    private ThumbnailDownloadListener<T> mThumbnailDownloadListener;


    //新增一个用来(在请求者和结果之间) 通信的监听器接口
    public interface ThumbnailDownloadListener<T>{
        void onThumbnailDownloaded(T target,Bitmap thumbnail);
    }

    //添加 ThumbnailDownloader的setter方法
    public void setThumbnailDownloadListener(ThumbnailDownloadListener<T> listener) {
        mThumbnailDownloadListener = listener;
    }

    //新建构造方法提嗲原来的构造方法,返回线程的Handler
    public ThumbnailDownloader(Handler responseHandler){
        super(TAG);
        mResponseHandler = responseHandler;
    }

```
### 主线程中
#### 主线程可以调用上面的方法，得到主线程的Handler跟回调接口
```java
        private ThumbnailDownloader<PhotoHolder> mThumbnailDownloader;

        //创建线程
        mThumbnailDownloader = new ThumbnailDownloader<>( responseHandler );
        mThumbnailDownloader.setThumbnailDownloadListener(
                new ThumbnailDownloader.ThumbnailDownloadListener<PhotoHolder>() {
                    @Override
                    //shi用个返回的Bitmap执行UI更新操作
                    public void onThumbnailDownloaded(PhotoHolder target, Bitmap thumbnail) {
                        Drawable drawable = new BitmapDrawable( getResources(), thumbnail );
                        target.bindDrawable( drawable );
                    }
                }
        );

        //启动线程
        mThumbnailDownloader.start();

        //要在start()方法之后调用getLooper()方法，这是一种保证线程就绪的处理方式
        mThumbnailDownloader.getLooper();
        Log.i( TAG, "Background thread started" );
```
### 下载线程给主线程Looper发送消息

+ Handler默认与当前线程的 Looper相关联。这个 Handler是在 contrate()方法中创建的,因此它会与主线程的 doepel相关联
+ 现在,通过 mResponseHandler, ThumbnaiDownloader能够访问与主线程Looper绑定的Handler。同时，还有ThumbnaiDownloadeListener使用返的Bitmap行UI更新操作。具体来说就是通过onThumbnaiLDownloaded实现,使用新下载的Bitmap来设置PhotoHoldler的Drawable　
+ 和在后台线程上把下载图片的请求放入消息队列类似我们也可以返回定制Message给主线
程,要求显示已下载图片a不过,这需要另一个 HandLer-子类,以及一个 thapd-teMessage
覆盖方法。方便起见,我转而使用另一个方便的Handler方法 -- post(Runnable)
+ Handler.post(Runnable)是一个发 mEssage的便利方法。具体如下:
 ```java
 Runnable myRunnable = new Runnable(){
   @Override
   public void run(){

   }
 };
 Message m = mHandler.obtainMessage();
 m.callback = myRunnable;
 ```
#### 在ThumbnaiDownloader.java添加代码
```java
//Handler.post(Runnable)是一个发布Message的方法
            mResponseHandler.post(new Runnable() {
                @Override
                public void run() {
                    if (!mRequestMap.get( target ).equals( url ) || mHasQuit){
                        return;
                    }
                    mRequestMap.remove(target);
                    mThumbnailDownloadListener.onThumbnailDownloaded(target,bitmap);
                }
            });
```
## 挑战练习
### 4.1 预加载
#### 在ThumbnaiDownloader.java添加代码
```java
    /**
     * 挑战练习 预加载
     * @param <T>
     */
    private LruCache<String,Bitmap> mCache;

        @SuppressLint("HandlerLeak")
    @Override
    //该方法是在Looper首次检查消息队列之前调用的
    // 该方法成了建立Handler的最好地方了
    protected void onLooperPrepared() {
        mRequestHandler = new Handler(){
            @Override
            public void handleMessage(Message msg) {
                //先检查消息类型，在获取obj的值(T类型下载请求)
                if (msg.what == MESSAGE_DOWNLOAD){
                    T target = (T) msg.obj;
                    Log.i(TAG,"Got a request for URL:" + mRequestMap.get(target));

                    //再将其target传入handleRequest()返回给发当中
                    handleRequest(target);
                }else if (msg.what == MESSAGE_PRELOAD){
                    String urlToPreload = (String) msg.obj;
                    handlePreload(urlToPreload);
//                    Log.i(TAG, "Preload URL: " + urlToPreload);
                }
            }
        };
        int maxCacheSize = 4 * 1024 * 1024; //4MB
        mCache = new LruCache<>(maxCacheSize);
    }

      ////专门提供下载服务的类
    private void handleRequest(final T target){
        try{
            final String url = mRequestMap.get(target);

            //确认Url有效之后
            if (url == null){
                return;
            }
//            //传给FlickrFetchr新实例，并把返回的字节转化成位图
//            byte [] bitmapBytes = new FlickrFetchr().getUrlBytes(url);
//            final Bitmap bitmap = BitmapFactory.
//                    decodeByteArray(bitmapBytes,0,bitmapBytes.length);
//            Log.i(TAG,"Bitmap created");
            final Bitmap bitmap;
            //如果没有之前的缓存
            if (mCache.get(url) == null) {
                byte[] bitmapBytes = new FlickrFetchr().getUrlBytes(url);
                bitmap = BitmapFactory.decodeByteArray(bitmapBytes, 0, bitmapBytes.length);
                //重新加载
                Log.i(TAG, "Bitmap created");
                //该方法保存了第一次加载的uri
                mCache.put(url, bitmap);
            } else {
                //如果有就直接取出加载,
                bitmap = mCache.get(url);
                Log.i(TAG, "Bitmap from cache");
            }

            //Handler.post(Runnable)是一个发布Message的方法
            mResponseHandler.post(new Runnable() {
                @Override
                public void run() {
                    if (!mRequestMap.get( target ).equals( url ) || mHasQuit){
                        return;
                    }
                    mRequestMap.remove(target);
                    mThumbnailDownloadListener.onThumbnailDownloaded(target,bitmap);
                }
            });

        }catch (IOException e){
            Log.e(TAG,"Error downloading image",e);
        }
    }

```
### 4.2 预加载
#### 下载线程中的调用
```java
 private void handlePreload(String url) {
        try {
            if (url == null) {
                return;
            }
            if (mCache.get(url) == null) {
                byte[] bitmapBytes = new FlickrFetchr().getUrlBytes(url);
                Bitmap bitmap = BitmapFactory
                        .decodeByteArray(bitmapBytes, 0, bitmapBytes.length);
                mCache.put(url, bitmap);
            }
        } catch (IOException ioe) {
            Log.e(TAG, "Error preloading image", ioe);
        }
    }
```
#### 主线程当中的调用
```java
        @Override
        public void onBindViewHolder(@NonNull PhotoHolder holder, int position) {
          /**
             * 为前十个个和后十个预加载
             */
            for (int i = Math.max( 0,position - 10);
                 i < Math.min( mGalleryItems.size() - 1,position + 10) ;
                 i ++) {
                Log.e( TAG,"Preload position" + i );
                mThumbnailDownloader.queuePreloadThumbnail( mGalleryItems.get( i ).getUrl() );
            }
        }

```
***

GitHub具体代码: [hyyyrwang .github.io](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/Thread/ThumbnailDownloader.java)
