---
title: Android编程权威指南（第2版）--第16章 使用intent拍照 挑战练习
tags:
  - Android
  - Android编程权威指南(第2版)
categories: Android
top: 90
---
![13112Q52601-0.jpg](https://upload-images.jianshu.io/upload_images/9140378-c24e07e3cc2c0928.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
***
<!--more-->

## 16.7挑战练习：优化照片显示
### 新建dialog_photo.xml

```html
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
              android:orientation="vertical"
              android:layout_width="match_parent"
              android:layout_height="match_parent">

    <ImageView
        android:id="@+id/crime_photo_detail"
        android:layout_width="match_parent"M
        android:layout_height="match_parent"
        />

</LinearLayout>
```

### 新建PhotoDetailFragment.java

```java

public class PhotoDetailFragment extends DialogFragment {

    private static final String ARG_File = "file";
    private ImageView mPhotoView;

    public static PhotoDetailFragment newInstance(File file) {
        Bundle args = new Bundle();
        args.putSerializable(ARG_File, file);

        PhotoDetailFragment fragment = new PhotoDetailFragment();
        fragment.setArguments(args);
        return fragment;
    }

    @NonNull
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        File file = (File) getArguments().getSerializable(ARG_File);

        View v = LayoutInflater.from(getActivity())
                .inflate(R.layout.dialog_photo, null);
        mPhotoView = (ImageView) v.findViewById(R.id.crime_photo_detail);

        Bitmap bitmap = PictureUtils.getScaledBitmap(
                file.getPath(), getActivity());
        mPhotoView.setImageBitmap(bitmap);

        return new AlertDialog.Builder(getActivity())
                .setView(v)
                //.setTitle(R.string.date_picker_title)
                .setPositiveButton(android.R.string.ok, null)
                .create();

    }
}
```
### 修改CrimeFragment.java

```java
private static final int REQUEST_PHOTO = 3;
private static final String DIALOG_PHOTO = "DialogPhoto";
```

onCreateView增加处理

```java
mPhotoView = (ImageView) v.findViewById(R.id.crime_photo);
        mPhotoView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (mPhotoFile == null || !mPhotoFile.exists()) {
                    mPhotoView.setImageDrawable(null);
                } else {

                    FragmentManager manager = getFragmentManager();
                    PhotoDetailFragment dialog = PhotoDetailFragment.newInstance(mPhotoFile);
                    dialog.setTargetFragment(CrimeFragment.this, REQUEST_PHOTO);
                    dialog.show(manager, DIALOG_PHOTO);

                }

            }
        });
        updatePhotoView();
```

### 演示结果：
<center>

![示](https://upload-images.jianshu.io/upload_images/9140378-6867c3422b8cc8ab.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/240)

</center>

---

## 16.8 挑战练习：优化缩略图加载

### 修改CrimeFragment.java

#### updatePhotoView,调用带宽高参数的getScaledBitmap

```java
private void updatePhotoView(int width, int height) {
        if (mPhotoFile == null || !mPhotoFile.exists()) {
            mPhotoView.setImageDrawable(null);
        } else {
            Bitmap bitmap = PictureUtils.getScaledBitmap(
                    mPhotoFile.getPath(), width, height); // change this one
            mPhotoView.setImageBitmap(bitmap);
        }
    }
```

#### onCreateView加上

```java
mPhotoObserver = mPhotoView.getViewTreeObserver();
        mPhotoObserver.addOnGlobalLayoutListener(new ViewTreeObserver.OnGlobalLayoutListener() {
            @Override
            public void onGlobalLayout() {
                updatePhotoView(mPhotoView.getWidth(), mPhotoView.getHeight());
            }
        });

        return v;
```

#### 修改onActivityResult，不然返回拍完照片返回CrimeFragment的时候会显示不出略缩图

```java
else if (requestCode == REQUEST_PHOTO) {

                    updatePhotoView(mPhotoView.getWidth(), mPhotoView.getHeight());
        }
```



### 上述代码运行无误，可以达到效果，虽然可以通过OnGlobalLayoutListener这个方式获取视图的宽和高，但是还没搞清楚，待日后补充吧

参考：[点击打开链接](http://www.cnblogs.com/chase1/p/7192683.html)

Github具体代码：[hyyyrwang.github.io](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/Criminallntent2/app/src/main/java/com/example/lab/android/nuc/criminallntent/Fragment/CrimeFragment.java)<br>
我的简书：[https://www.jianshu.com/p/1b9785db93a6](https://www.jianshu.com/p/1b9785db93a6)
***
