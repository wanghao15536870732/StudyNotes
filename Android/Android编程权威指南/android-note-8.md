---
title: Android编程权威指南（第2版）学习笔记 --第25章 搜索
tags:
  - Android
  - Android编程权威指南(第2版)
categories: Android
top: 93
---
![u=1983816984,3550559459&fm=26&gp=0.jpg](https://upload-images.jianshu.io/upload_images/9140378-0ba92a814310e10c.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
***
<!--more-->
## <center>本章的任务是使用SearchView为PhotoGalllery应用添加Flickr图片搜索功能</center>

## 重构
### 首先，重构 FlickerFether的代码以复用JSON数据解析逻辑
```java
public class FlickrFetchr {
   private static final String FETCH_RECENTS_METHOD = "flickr.photos.getRecent";
    private static final String SEARCH_METHOD = "flickr.photos.search";
    //这里创建了完整的Flickr API请求URL，便利类Url。Builder可创建正确转移的参数化URL
    private static final Uri ENDPOINT =  Uri.
            parse("https://api.flickr.com/services/rest/")
            .buildUpon()
            .appendQueryParameter("method", "flickr.photos.getRecent")
            .appendQueryParameter("api_key", API_KEY)
            .appendQueryParameter("format", "json")
            .appendQueryParameter("nojsoncallback", "1")
            .appendQueryParameter("extras", "url_s")   //该参数制定了图片的大小
            //这里用Url.builder()构建了完整的Flickr APi请求URL,
            .build();

            ...

            //改为私有方法
    // public List<GalleryItem> fetchItems(){
    private List<GalleryItem> downloadGalleryItems(String url) {
        List<GalleryItem> items = new ArrayList<>();
        try {

            //之前的解析代码

            // String url = Uri.parse("https://api.flickr.com/services/rest/")
            // .buildUpon()
            // .appendQueryParameter("method", "flickr.photos.getRecent")
            // .appendQueryParameter("api_key", API_KEY)
            // .appendQueryParameter("format", "json")
            // .appendQueryParameter("nojsoncallback", "1")
            // .appendQueryParameter("extras", "url_s")   //该参数制定了图片的大小
            // //这里用Url.builder()构建了完整的Flickr APi请求URL,
            // .build().toString();

            String jsonString = getUrlString(url);
            Log.e(TAG, "Received JSON: " + jsonString);
            //将jsonString 类型的数据装换成JSONObject而类型的
            JSONObject jsonBody = new JSONObject(jsonString);
            //调用parseItems()方法进行数组存储
            parseItems(items,jsonBody);
        } catch (JSONException e) {
            Log.e(TAG, "Failed to parse JSON");
        } catch (IOException ioe) {
            Log.e(TAG, "Failed to fetch items", ioe);
        }
        return items;
    }

    ...

}
```

### 添加创建URL的辅助方法
在downloadGalleryItems(String url)方法中添加一个新方法基于搜索、下载和查询创建URL
```java
   /**
     * 创建新方法用于搜索下载和查询URL参数
     */
    private String buildUrl(String method,String query){
        Uri.Builder uriBuilder = ENDPOINT.buildUpon()
                .appendQueryParameter( "method",method );
        if (method.equals( SEARCH_METHOD )){
            uriBuilder.appendQueryParameter( "text",query );
        }
        return uriBuilder.build().toString();
    }

```

### 添加方法用于下载跟搜索
参数值是动态的，如果判断出不是搜索，他就会附加一个text参数值，如果判断出是搜索，他还会附加一个text参数值
```java

private static final String FETCH_RECENTS_METHOD = "flickr.photos.getRecent";
private static final String SEARCH_METHOD = "flickr.photos.search";

public List<GalleryItem> fetchRecentPhotos(){
        String url = buildUrl(FETCH_RECENTS_METHOD,null);
        return downloadGalleryItems( url );
    }

    public List<GalleryItem> searchPhotos(String query){
        String url = buildUrl( SEARCH_METHOD,query );
        return downloadGalleryItems( url );
    }
```
### 硬编码的搜索字符串
如果搜索字符串为空，fetchItemsTask就会执行Flickr搜索任务
，否则，就会默认下载最新公共图片
```java
@Override
        protected List<GalleryItem> doInBackground(Void... voids) {
//            try {
//                String result = new FlickrFetchr().getUrlString("https://www.bignerdranch.com");
//                Log.i(TAG,"Fetched contents of URL:" + result);
//            }catch (IOException e){
//                Log.e(TAG,"Failed to fetch URL: ",e);
//            }
//            return new FlickrFetchr().fetchItems();
//            return null;
            //将GalleryItem对象List传递给onPostExecute()方法使用
//            String query = "robot";

            if (mQuery == null) {
                //如果搜索框内容为空,就会默认加载最新的公共图片
                return new FlickrFetchr().fetchRecentPhotos();
            } else {
                ///如果搜索框为非空，执行搜索任务
                return new FlickrFetchr().searchPhotos( mQuery );
            }
        }
```
## SearchView的使用
### 首先在在res/menu当中创建一个新的菜单XML文件
```html
<?xml version="1.0" encoding="utf-8"?>
<menu xmlns:tools="http://schemas.android.com/tools"
    xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto">

    <item android:id="@+id/menu_item_search"
        android:title="@string/search"
        app:showAsAction="ifRoom"
        app:actionViewClass="android.support.v7.widget.SearchView" />

    <item android:id="@+id/menu_ite_clear"
        android:title="@string/clear_search"
        app:showAsAction="never"/>
    <item
        android:id="@+id/menu_item_toggle_polling"
        android:title="@string/start_polling"
        app:showAsAction="ifRoom"/>
</menu>
```
### 然后让其响应点击事件
在OnCreate()方法当中调用setHasOptionsMenu(true)方法让fragment接受菜单回调方法
，然后，覆盖onCreateOptionsMenu(...)方法并实例化菜单XMl文件
```java
public class PhotoGalleryFragment extends VisibleFragment {

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate( savedInstanceState );
        //在Activity重新创建时可以不完全销毁Fragment，以便Fragment可以恢复
        setRetainInstance( true );

        //让fragment接收菜单回调方法
        setHasOptionsMenu( true );
  }

  @Override
  public void onCreateOptionsMenu(Menu menu, MenuInflater menuInflater){
    super.onCreateOptionsMenu( menu, menuInflater );
    menuInflater.inflate( R.menu.fragment_photo_gallery, menu );
  }
}
```

### 响应用户搜索
#### SearchView.OnQueryTextListener()接口已经提供了接受回调的方式，更新onCreateOptionsMenu(...)方法，实现这个监听方法
```java
public class PhotoGalleryFragment extends VisibleFragment {
  ...

  @Override
  public void onCreateOptionsMenu(Menu menu, MenuInflater menuInflater){
    super.onCreateOptionsMenu( menu, menuInflater );
    menuInflater.inflate( R.menu.fragment_photo_gallery, menu );

      /**
         * 实现SearchView。OnQueryTextListener监听方法
         */
        //首先从菜单中取出MenuItem并把它保存在searchItem变量当中
    final MenuItem searchItem = menu.findItem( R.id.menu_item_search );

    //使用getActionView()取出searchView
    final SearchView searchView = (SearchView) searchItem.getActionView();
    searchView.setOnQueryTextListener( new SearchView.OnQueryTextListener() {
        @Override
        public boolean onQueryTextSubmit(String query) {
        Log.d( TAG, "QueryTextSubmit: " + query );
        updateItems();
        return true;
      }
        @Override
        public boolean onQueryTextChange(String newText) {
        Log.d( TAG, "QueryTextChange: " + newText );
        return false;
      }
    });
  }

  private void updateItems(){
    new fetchItemsTask().execute();
  }

}
```
### 最后在onCreate(...)方法中，删除创建和执行FetchItemsTask的那行代码，改用updateItems()封装方法
```java
public class PhotoGalleryFragment extends VisibleFragment {
   @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate( savedInstanceState );
        setRetainInstance( true );
        //让fragment接收菜单回调方法
        setHasOptionsMenu( true );
        //execute()会启动AsyncTask
//        new FetchItemsTask().execute();
        updateItems();
    }
}
```
## 使用SharedPreferrences 实现轻量级数据储存
### 什么是Sharepreferrences?
![images.jpg](https://upload-images.jianshu.io/upload_images/9140378-45bcb5ad456dabd9.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

 + shared preferences 本质上就是文件系统中的文件，可使用 SharedPreferences 类读写它。
 + SharedPreferences 实例用起来更像一个键值对仓库(类似于 Bundle)，但它可以通过持久化存储保存数据。键值对中的键为字符串，而值是原子数据类型。
 + 它们实际上是一种简单的 XML 文件，但SharedPreferences 类已屏蔽了读写文件的实现细节。shared preferences 文件保存在应用沙盒中，所以，类似密码这样的敏感信息不应该用它来保存。<br>
+ 要获得定制的 SharedPreferences 实例,可使用Context.getSharedPreferences (String,int)方法。
+ 这种情况下，最好使用PreferenceManager. getDefaultSharedPreferences(Context)方法，该方法会返回具有私有权限和默认名称的实例(仅在当前应用内可用)。

### 使用SharedPreferrences
#### 添加一个[QUeryPreferences.java](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/Base/QueryPreferences.java)类管理保存的查询字符串
```java

public class QueryPreferences {
    private static final String PREF_SEARCH_QUERY = "searchQuery";

    //通过SharePreference得到数据
    public static String getStoreQuery(Context context){
        return PreferenceManager.getDefaultSharedPreferences( context )
                .getString( PREF_SEARCH_QUERY,null );
    }
    //通过SharePreference写入数据
    public static void setStoreQuery(Context context,String query){
        PreferenceManager.getDefaultSharedPreferences( context )
                .edit()
                .putString( PREF_SEARCH_QUERY,query )
                .apply();
    }
}
```
#### 储存用户提交的信息
```java
public class PhotoGalleryFragment extends VisibleFragment {
  ...

   @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater menuInflater) {
        searchView.setOnQueryTextListener( new SearchView.OnQueryTextListener() {
            @Override
            public boolean onQueryTextSubmit(String query) {
                Log.d( TAG, "QueryTextSubmit: " + query );
                //储存用户提交的查询信息
                QueryPreferences.setStoreQuery( getActivity(), query );
                updateItems();
                return true;
            }

            @Override
            public boolean onQueryTextChange(String newText) {
                Log.d( TAG, "QueryTextChange: " + newText );
                return false;
            }
        } );
    }
}
```
#### 清除查询信息
在用户从溢出菜单选择Clear Search 选项时清除储存的查询信息(设置为 null )
```java
public class PhotoGalleryFragment extends VisibleFragment {
  ...

   @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.menu_ite_clear:
                QueryPreferences.setStoreQuery( getActivity(), null );
                updateItems();
                return true;
            default:
                return super.onOptionsItemSelected( item );
        }
    }
}
```
## 优化应用
### 让SearchView文本框默认显示已保存的查询信息
```java
public class PhotoGalleryFragment extends VisibleFragment {
  ...

   @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater menuInflater) {
        ...

        searchView.setOnQueryTextListener( new SearchView.OnQueryTextListener() {
            ...

        } );
        /**
         * 优化应用
         * 回调方法设置搜索文本框的值
         */
        searchView.setOnClickListener( new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String query = QueryPreferences.getStoreQuery( getActivity() );
                searchView.setQuery( query, false );
            }
        } );
    }
  ...

}
```
## 优化练习：深度优化PHotoGallery应用
+ 用户一提交搜索,就隐藏软键盘,收起 Searchview视图(回
到只显示搜索按钮的初始状态)
+ 用户一提交搜索,就初始化 Recyctervie显示一个搜索结果加载状态界面(使用状态指示器)。下载到JSON数据之后,就删除状态指示器。也就是说,一旦开始下载图片就不应显示加载状态了。
```java
public class PhotoGalleryFragment extends VisibleFragment {
  ...

   @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater menuInflater) {
        ...

        searchView.setOnQueryTextListener( new SearchView.OnQueryTextListener() {
        Log.d( TAG, "QueryTextSubmit: " + query );

                //储存用户提交的查询信息
                QueryPreferences.setStoreQuery( getActivity(), query );
                // 优化隐藏键盘
               if (searchView != null){
                   //得到输入管理对象
                   InputMethodManager inputMethodManager = (InputMethodManager) getActivity()
                           .getSystemService( Context.INPUT_METHOD_SERVICE );
                   if (inputMethodManager != null){
                       /*
                        这将让键盘在所有的情况下都被隐藏，但是一般我们在点击搜索按钮后,输入法都会乖乖的自动隐藏的。
                        */

                       // 输入法如果是显示状态，那么就隐藏输入法
                       inputMethodManager.hideSoftInputFromWindow( searchView.getWindowToken(),0 );
                   }
                   searchView.onActionViewCollapsed();// 不获取焦点
               }
                return true;
            }

            @Override
            public boolean onQueryTextChange(String newText) {
                Log.d( TAG, "QueryTextChange: " + newText );
                return false;
            }

        } );
    }
  ...

}
```
***
Github 具体代码：[hyyyr wang.github.io](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/PhotoGallery/app/src/main/java/com/example/lab/android/nuc/photogallery/Fragment/PhotoGalleryFragment.java)
