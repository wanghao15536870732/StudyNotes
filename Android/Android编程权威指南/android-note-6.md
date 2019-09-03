---
title: Android编程权威指南（第2版）学习笔记 --第23章 HTTP与后台任务
tags:
  - Android
  - Android编程权威指南(第2版)
categories: Android
top: 91
---
![15032Q20351-1.jpg](https://upload-images.jianshu.io/upload_images/9140378-844fd04f5ddcafe8.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
***
<!--more-->
## <center>这一章主要讲解了如何使用Android的网络连接、搜索、服务、通知、广播接收器以及一些网络视图</center>


## 前提
#### 网络连接权限
```java
<uses-permission android:name="android.permission.INTERNET" />
```
### 网络请求函数
 [FlickrFetchr.java](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/Base/FlickrFetchr.java)
 ```java
  public byte[] getUrlBytes(String urlSpec) throws IOException {
        //先根据传入的字符串参数，及网站，创建一个URL对象
        URL url = new URL(urlSpec);
        ///然后调用openConnection()方法创建一个只想要访问URL的链接对象。
        //强制转换成HttpURLConnection对象
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        try {
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            //调用getInputStream()方法得到连接到指定的URl地址
            InputStream in = connection.getInputStream();

            if (connection.getResponseCode() != HttpURLConnection.HTTP_OK) {
                throw new IOException(connection.getResponseMessage() +
                        ": with " +
                        urlSpec);
            }
            int bytesRead = 0;
            byte[] buffer = new byte[1024];
            //调用read()方法读循环读取网络数据，直到读取完为止
            while ((bytesRead = in.read(buffer)) > 0) {
                out.write(buffer, 0, bytesRead);
            }
            out.close();
            return out.toByteArray();
        } finally {
            connection.disconnect();
        }
    }

    public String getUrlString(String urlSpec) throws IOException {
        //将得到的数据转换成String类型的数据
        return new String(getUrlBytes(urlSpec));
    }
 ```
 ## 使用AsyncTask在后台线程上运行代码
 ### 什么是AsyncTask?
 #### AsyncTask的生命周期
 + onPreExecute() 执行之前
 + onProgressUpdate() 更新进展
 + doInBackground() 在线程中真正要完成的事
 + onPostExecute() 完成之后要做的事（在 UI 线程中执行）
 + onCancelled() 退出之后
 #### AsyncTask的第一个参数：输入
 ```java
 AsyncTask<String,Void,Void> task = new AsyncTask<String,Void,Void>() {
	public Void doInBackground(String... params) {
		for (String parameter : params) {
			Log.i(TAG, "Received parameter: " + parameter);
		}
		return null;
	}
};
 ```

#### AsyncTask的第二个参数：进度
 由于在后台进程中无法完成必要的 UI 更新。因此 AsyncTask 提供了 publishProgress(…)和 onProgressUpdate(…)方法。在 onProgressUpdate(…)方法中执行 UI 更新就可行了，但必须在 doInBackground(…) 方法中使用 publishProgress(…)方法对它们进行管控。

 ```java
 final ProgressBar gestationProgressBar = /* 一个特定的进度条 */;
gestationProgressBar.setMax(42); /* 最大的进度 */
AsyncTask<Void,Integer,Void> haveABaby = new AsyncTask<Void,Integer,Void>() {
	public Void doInBackground(Void... params) {
		while (!babyIsBorn()) {
			Integer weeksPassed = getNumberOfWeeksPassed();
          publishProgress(weeksPassed); // 关键，将参数发送到 onProgressUpdate
          patientlyWaitForBaby();
		}
	}

	public void onProgressUpdate(Integer... params) {
		int progress = params[0];
		gestationProgressBar.setProgress(progress);
	}
};
/* call when you want to execute the AsyncTask */
haveABaby.execute();
```
#### AsyncTask的第三个参数：结果
```java
// PhotoGalleryFragment.java
private class FetchItemsTask extends AsyncTask<Integer, Void, List<GalleryItem>> {
    @Override
    protected List<GalleryItem> doInBackground(Integer... params) {
        return new FlickrFetchr().fetchItems(params[0]);
    }
    @Override
    protected void onPostExecute(List<GalleryItem> galleryItems) {
        mItems = galleryItems;
        setAdapter();
    }
}
```
### 使用后台线程最方便的是使用AsyncTask工具类,AsyncTask创建后台线程后，就可以在该线程上调用doInBackgroung(...)方法运行代码 [PhotoGalleryFragment.java](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/Fragment/PhotoGalleryFragment.java)
 ```java
     @SuppressLint("StaticFieldLeak")
    private class FetchItemsTask extends AsyncTask<Void, Void, Void> {

        private String mQuery;

        public FetchItemsTask(String qurey) {
            mQuery = qurey;
        }

        @Override
        protected List<GalleryItem> doInBackground(Void... voids) {
           try {
               String result = new FlickrFetchr().getUrlString("https://www.bignerdranch.com");
               Log.i(TAG,"Fetched contents of URL:" + result);
           }catch (IOException e){
               Log.e(TAG,"Failed to fetch URL: ",e);
           }
           return new FlickrFetchr().fetchItems();
           return null;
         }
       }
     }
 ```
### 启动AsyncTask
```java
 @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
       super.onCreate( savedInstanceState );
        //在Activity重新创建时可以不完全销毁Fragment，以便Fragment可以恢复
       setRetainInstance( true );
       // execute()会启动AsyncTask
       new FetchItemsTask().execute();
  }
```
## 线程与主线程
![一般线程与主线程](https://upload-images.jianshu.io/upload_images/9140378-8c37c9b356419872.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/2240)

网络连接需要时间，Web 服务器可能需要1~2秒的时间来响应访问请求，文件下载则耗时更久。考虑到这个因素，Android 禁止任何主线程网络连接行为。即使强行在主线程中进行网络连接，Android 也会抛出 NetworkOnMainThreadException 异常。<br>
线程是个单一执行序列。单个线程中的代码会逐步执行。所有 Android 应用的运行都是从主线程开始的。然而，主线程不是线程那样的预定执行序列。相反，它处于一个无限循环的运行状态，等待着用户或系统触发事件的发生。事件触发后，主线程便负责执行代码，以响应这些事件。<br>

## 挑战练习
### 整合GSON库，用GSON解析JSON类型的数据
#### 添加GSON库
dependencies中添加下面的依赖
```java
dependencies {
  implementation 'com.google.code.gson:gson:2.8.5'
}
```
#### 构建所对应的pojo类
新建类[PhotoBean.java](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/Base/PhotoBean.java),用于匹配对应的结构
```java
public static final String STATUS_OK = "ok",STATUS_FALSE = "fail";

    @SerializedName( "photos" )
    private PhotosInfo mPhotosInfo;
    @SerializedName( "stat" )
    private String mStatus;
    @SerializedName( "message" )
    private String mMessage;

    public class PhotosInfo{
        @SerializedName( "photo" )
        List<GalleryItem> mPhoto;

        public List<GalleryItem> getPhoto(){
            return mPhoto;
        }
    }

    //getter、setter...
}
```
#### 使用Gson
相比之前，简单许多，一行代码即可搞定
```java
PhotoBean photoBean = (PhotoBean) new Gson()
        .fromJson(jsonString, PhotoBean.class);
```
### 分页显示
#### 重写RecyclerView.onScrollListener的onScrollStateChanged()方法
+ SCROLL_STATE_IDLE: 视图没有被拖动，处于静止
+ SCROLL_STATE_DRAGGING： 视图正在拖动中
+ SCROLL_STATE_SETTLING： 视图在惯性滚动

```java
    /*
    分页加载
     */
   private RecyclerView.OnScrollListener onButtomListener = new RecyclerView.OnScrollListener() {
       @Override
       public void onScrollStateChanged(RecyclerView recyclerView, int newState) {
           super.onScrollStateChanged( recyclerView, newState );
           GridLayoutManager layoutManager = (GridLayoutManager) recyclerView.getLayoutManager();
           mLastPosition = layoutManager.findLastVisibleItemPosition();
           if (mPhotoAdapter == null) {
               return;
           }
          // 如果静止的时候最后的位置大于等于数据个数
        // 而且前一个任务完成时（防止多次重复）
           if (newState == RecyclerView.SCROLL_STATE_IDLE
                   && mLastPosition >= mPhotoAdapter.getItemCount() - 1) {
               if (mFetchItemsTask.getStatus() == AsyncTask.Status.FINISHED) {
                      // 下一页加一，在小于最大页数时
            	         // 弹出 Toast 表示正在加载
            	       // 然后打开一个新任务，加载下一页
                   mNextPage++;
                   if (mNextPage < MAX_PAGES) {
                       Toast.makeText( getActivity(), "waiting to load...", Toast.LENGTH_SHORT ).show();
                       updateItems( mNextPage );
                   } else {
                       Toast.makeText( getActivity(), "This is the end.", Toast.LENGTH_SHORT ).show();
                   }
               }
           }

       }

       @Override
       public void onScrolled(RecyclerView recyclerView, int dx, int dy) {
           super.onScrolled( recyclerView, dx, dy );
       }
   };
```
#### 添加数据并显示
```java

private void setAdapter() {

    if (isAdded()) {
        if (mPhotoAdapter == null) {
            mPhotoAdapter = new PhotoAdapter(mItems);
            mPhotoRecyclerView.setAdapter(mPhotoAdapter);
            mPhotoRecyclerView.addOnScrollListener(onButtomListener);
        } else {
            mPhotoAdapter.addData(mItems);
        }
    }
}
```
### 动态调整网格列
使用 ViewTreeObserver.OnGlobalLayoutListener 即可：
```java
        //添加动态调整网格
       mPhotoRecyclerView.getViewTreeObserver()
               .addOnGlobalLayoutListener( new ViewTreeObserver.OnGlobalLayoutListener() {
                   @Override
                   public void onGlobalLayout() {
                     // 计算列数，以 1080p 屏幕显示3列为基准
                       int columns = mPhotoRecyclerView.getWidth() / 240;
                       mPhotoRecyclerView.setLayoutManager(new GridLayoutManager(getActivity(), columns));
                         // 重新设置 LayoutManager、Adapter 和 Listener
                       mPhotoRecyclerView.getViewTreeObserver().removeOnGlobalLayoutListener(this);
                       mPhotoRecyclerView.setAdapter(new PhotoAdapter( mItems ));
                       mPhotoRecyclerView.addOnScrollListener(onButtomListener);
                        // 滚动到之前看到的位置
                       mPhotoRecyclerView.getLayoutManager().scrollToPosition(mLastPosition);
                   }
               } );
```
***

Github 具体代码 [hyyyrwang.github.io](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery)
