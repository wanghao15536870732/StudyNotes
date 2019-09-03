---
title: Android编程权威指南（第2版）学习笔记 --第28章 网页浏览
tags:
  - Android
  - Android编程权威指南(第2版)
categories: Android
top: 96
---
![u=4194479329,432879413&fm=26&gp=0.jpg](https://upload-images.jianshu.io/upload_images/9140378-86bc8fbd0d9b3698.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
***
<!--more-->
## <center>本章主要讲解了利用WebView在android应用中浏览网页,即在photoGallery的基础上添加一个功能：点击照片可以访问照片的url</center>
***
## 较简单方式:隐式Intent
### 通过隐式intent实现网页浏览
隐士intent可启动浏览器，并在其中打开图片URL指向的网页，实现一个发送隐式intent的方法
```java
public class PhotoGalleryFragment extends VisibleFragment {

    ......

      //来时准备视图层的部分
    private class PhotoHolder extends RecyclerView.ViewHolder implements View.OnClickListener{

//        private TextView mTitleTextView;

        private ImageView mItemImageView;
        private GalleryItem mGalleryItem;

        public PhotoHolder(View itemView) {
            super( itemView );
            mItemImageView = (ImageView) itemView.findViewById( R.id.fragment_photo_gallery_image_view );
//          mTitleTextView = (TextView) itemView;
            itemView.setOnClickListener( this );
        }

//        public void bindGalleryItem(GalleryItem item){
//            Picasso.with( getActivity() )
//                    .load( item.getUrl() )
//                    .placeholder( R.drawable.bill_up_close )
//                    .into( mItemImageView );
//        }


        public void bindDrawable(Drawable drawable) {
            mItemImageView.setImageDrawable( drawable );
        }

        public void bindGalleryItem(GalleryItem galleryItem){
            mGalleryItem = galleryItem;
        }

        @Override
        public void onClick(View v) {
           Intent intent = new Intent( Intent.ACTION_VIEW,mGalleryItem.getPhotoPageUri() );
           startActivity( intent );
        }
    }

    ......

}
```
### 绑定GalleryItem
```java
private class PhotoAdapter extends RecyclerView.Adapter<PhotoHolder> {

        ......

        @Override
        public void onBindViewHolder(@NonNull PhotoHolder holder, int position) {

            GalleryItem galleryItem = mGalleryItems.get( position );
            holder.bindGalleryItem(galleryItem);
            //改为绑定图片
            //先去的照片的信息
            Drawable placeholder = getResources().getDrawable( R.drawable.bill_up_close );
            //再绑定照片
            holder.bindDrawable( placeholder );
            holder.bindGalleryItem(galleryItem);
            mThumbnailDownloader.queueThumbnail( holder, galleryItem.getUrl() );
        }

        ......
}
```
***
## 使用WebView
### 首先在 fragment 的布局文件中声明，然后在 fragment 中获取实例，然后设置逻辑：

```html
<?xml version="1.0" encoding="utf-8"?>
<RelativeLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent">
    <WebView
        android:id="@+id/fragment_photo_page_web_view"
        android:layout_width="match_parent"
        android:layout_alignParentBottom="true"
        android:layout_height="match_parent"
        android:layout_below="@+id/fragment_page_progress_bar">

    </WebView>
</RelativeLayout>
```
[PhotoPageFragment.java](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/Fragment/PhotoPageFragment.java)

```java
public class PhotoPageFragment extends VisibleFragment{
    private static final String ARG_URI = "photo_page_url";

    private Uri mUri;
    private WebView mWebView;

    public static PhotoPageFragment newInstance(Uri uri){
        Bundle args = new Bundle( );
        args.putParcelable( ARG_URI,uri );

        PhotoPageFragment fragment = new PhotoPageFragment();
        fragment.setArguments( args );
        return fragment;
    }

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate( savedInstanceState );
        mUri = getArguments().getParcelable( ARG_URI );
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate( R.layout.fragment_photo_page,container,false );

        mWebView = (WebView) view.findViewById( R.id.fragment_photo_page_web_view );
        return view;
    }
}
```
### 加载URL
```java
public class PhotoPageFragment extends VisibleFragment{

    ......

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate( R.layout.fragment_photo_page,container,false );

        mWebView = (WebView) view.findViewById( R.id.fragment_photo_page_web_view );
        mWebView.getSettings().setJavaScriptEnabled( true );
        mWebView.setWebViewClient( new WebViewClient(){
            public boolean shoudOverrideUrlLoading(WebView view,String url){
                return false;
            }
        });
        mWebView.loadUrl(muri.toString());
        return view;
    }
}
```
***
## 用 WebChromeClient 优化 WebView 显示
### 添加标题和进度条
```html
<?xml version="1.0" encoding="utf-8"?>
<RelativeLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent">


    <ProgressBar
        android:id="@+id/fragment_page_progress_bar"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:layout_alignParentTop="true"
        android:visibility="gone"
        style="?android:attr/progressBarStyleHorizontal"
        android:background="?attr/colorPrimary"/>
    <WebView
        android:id="@+id/fragment_photo_page_web_view"
        android:layout_width="match_parent"
        android:layout_alignParentBottom="true"
        android:layout_height="match_parent"
        android:layout_below="@+id/fragment_page_progress_bar"/>

</RelativeLayout>
```
### 使用WebChromeClient
```java
public class PhotoPageFragment extends VisibleFragment{

    ...

    private WebView mWebView;
    private ProgressBar mProgressBar;

    ...

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate( R.layout.fragment_photo_page,container,false );

        mProgressBar = (ProgressBar) view.findViewById( R.id.fragment_page_progress_bar );
        mProgressBar.setMax( 100 );

        mWebView = (WebView) view.findViewById( R.id.fragment_photo_page_web_view );
        mWebView.getSettings().setJavaScriptEnabled( true );

        mWebView.setWebChromeClient( new WebChromeClient(){
            @Override
            public void onProgressChanged(WebView view, int newProgress) {
                                    if (newProgress == 100){
                        mProgressBar.setVisibility( View.GONE);
                    }else {
                        mProgressBar.setVisibility( View.VISIBLE );
                        mProgressBar.setProgress( newProgress );
                    }
            }

            public void onReceivedTitle(WebView view, String title) {
                super.onReceivedTitle( view, title );
                AppCompatActivity activity = (AppCompatActivity) getActivity();
                activity.getSupportActionBar().setSubtitle( title );
            }
        } );
        mWebView.setWebViewClient( new WebViewClient(){
            public boolean shoudOverrideUrlLoading(WebView view,String url){
                return false;
            }
        });

        mWebView.loadUrl(mUri.toString());
    }
}
```
###  处理 WebView 的设备旋转问题

+ 尝试旋转设备屏幕，可以发现 WebView 必须重新加载网页。这是因为 WebView 包含太多的数据，无法在 onSaveInstanceState(…)方法内全部保存。所以每次设备旋转，它都必须从头开始加载网页数据。
+ 因为 WebView 是视图层级结构的一部分，所以旋转后它肯定会销毁并重建，不能用 retainFragment 来保留。
+ 对于一些类似的类(如 VideoView)，Android 文档推荐让 activity 自己处理设备配置变更。也就是说，无需销毁重建 activity，就能直接调整自己的视图以适应新的屏幕尺寸。这样，WebView 也就不必重新加载全部数据了。
+ android:configChanges 属性表明，如果因键盘开或关、屏幕方向改变、屏幕大小改变(也包括 Android 3.2之后的屏幕方向变化)而发生设备配置更改，那么 activity 应自己处理配置更改

```html
<activity android:name=".PhotoPageActivity"
	android:configChanges="keyboardHidden|orientation|screenSize"/>
```
***
## 挑战练习
### 使用后退键浏览历史页面
```java
    /**
     * 挑战练习    WebView使用后退键浏览历史网页
     *
     * 重写WebView所在Fragment绑定的Activity的onBackPressed方法
     */
    @Override
    public void onBackPressed() {
        WebView webView = mPhotoPageFragment.getWebView();
        //canGoBack判断是否有历史信息
        if (webView.canGoBack()){
            //如果有的话，就利用goBack回到前一个历史网页
            webView.goBack();
        }else {
            super.onBackPressed();
        }
    }
```
### 非 HTTP 链接支持
```java
public class PhotoPageFragment extends VisibleFragment{

    ......

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {

        ......

        mWebView.setWebChromeClient( new WebChromeClient(){

            .....

        } );
        if (mUri.getScheme().equals( "HTTP" ) || mUri.getScheme().equals( "HTTPS" )){
            Intent intent = new Intent(Intent.ACTION_VIEW);
            startActivity( intent );
        }else {
            mWebView.loadUrl(mUri.toString());
        }
        return view;
    }

    public WebView getWebView(){
        return mWebView;
    }
}

```

Github 具体代码[hyyyrwang.github.io](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/Fragment/PhotoPageFragment.java)

***
