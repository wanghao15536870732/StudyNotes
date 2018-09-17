---
title: Android编程权威指南 (第2版) --第12章 对话框 挑战练习
tags:
  - Android
  - Android编程权威指南 (第2版)
categories: Android
top: 86
---
***
<!--more-->
## <center>本章主要介绍了各类对话框的使用以及一个时间选择框的挑战练习</center>
## 12.4 挑战练习：更多对话框
***

### Crime里面增加存储小时和分钟的变量
```java
private int mHour;
private int mMinute;
```
#### 并通过右键generate添加getter和setter方法

***
### 创建dialog_time.xml文件
```java
<?xml version="1.0" encoding="utf-8"?>
<TimePicker xmlns:android="http://schemas.android.com/apk/res/android"
    android:id="@+id/dialog_time_picker"
    android:layout_width="match_parent"
    android:layout_height="match_parent">
</TimePicker>
```
***
### 创建TimePickerFragment.java
```java
public class TimePickerFragment extends DialogFragment {

    public static final String EXTRA_HOUR =
            "om.example.lab.android.nuc.criminallntent.hour";
    public static final String EXTRA_MINUTE =
            "om.example.lab.android.nuc.criminallntent.minute";

    public static final String ARG_Hour = "hour";
    public static final String ARG_Minute = "minute";
    private TimePicker timePicker;

    public static TimePickerFragment newInstance(int hour,int minute){
        Bundle arge = new Bundle( );
        arge.putSerializable(ARG_Hour,hour);
        arge.putSerializable( ARG_Minute,minute );

        TimePickerFragment fragment = new TimePickerFragment();
        fragment.setArguments( arge );
        return fragment;
    }

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        //转换成小时跟分钟
        int hour = (int) getArguments().getSerializable( ARG_Hour );
        int minute = (int) getArguments().getSerializable( ARG_Minute );
        View view = LayoutInflater.from( getActivity() ).inflate( R.layout.dialog_time,null);

        //找到布局控件
        timePicker = (TimePicker) view.findViewById( R.id.dialog_time_picker);
        timePicker.setCurrentHour( hour );
        timePicker.setCurrentMinute( minute );



        return new AlertDialog.Builder(getActivity())
                .setView( view )
                .setTitle( "Time of Crime" )
                .setPositiveButton( android.R.string.ok, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        int hour = timePicker.getCurrentHour();
                        int minute = timePicker.getCurrentMinute();
                        sendResult( Activity.RESULT_OK,hour,minute );
                    }
                } )
                .create();
    }

    private void sendResult(int resultCode,int hour,int minute){
        if (getTargetFragment() == null){
            return;
        }
        Intent intent = new Intent( );
        intent.putExtra( EXTRA_HOUR ,hour);
        intent.putExtra( EXTRA_MINUTE,minute);
        getTargetFragment()
                .onActivityResult( getTargetRequestCode(),resultCode,intent );

    }
}
```

***
### 在fragment_crime.xml新增一个button用于显示timepicker
```java
  <Button
            android:id="@+id/crime_time"
            android:text="@string/time"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_marginLeft="16dp"
            android:layout_marginRight="16dp"
            android:background="@drawable/bt_selector"/>
```
***
### 在CrimeFragment.java中，onCreateView方法增加对新button的处理
```java
      mTimeButton = (Button) v.findViewById( R.id.crime_time );
        mTimeButton.setOnClickListener( new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentManager fragmentManager = getFragmentManager();
                TimePickerFragment dialog = TimePickerFragment.newInstance( mCrime.getHour(),mCrime.getMinute());
                dialog.setTargetFragment( CrimeFragment.this,REQUEST_TIME);
                dialog.show(fragmentManager,DIALOG_DATE );
            }
        } );
```
#### 增加updateTime()方法，实现具体时间的正确显示；修改onActivityResult方法，增加对具体时间返回值的处理
```java
 if (requestCode == REQUEST_TIME){
            int hour = (int) data.getSerializableExtra( TimePickerFragment.EXTRA_HOUR );
            int minute = (int) data.getSerializableExtra( TimePickerFragment.EXTRA_MINUTE );
            mCrime.setHour( hour );
            mCrime.setMinute( minute );
            updateTime();
        }
        if (requestCode == REQUEST_DATE){
            //覆盖onActivityResult()方法从extra中获取日期数据，
            Date date = (Date) data.getSerializableExtra(DatePickerFragment.EXTRA_DATE);

            //设置对应的Crimed的记录日期
            mCrime.setDate(date);
            updateCrime();
            //更新Button所显示的信息
            updateDate();
        }else if (requestCode == REQUEST_CNTACT && data != null){
            //获取日期的Uri
            Uri contactUri = data.getData();
            //创建了一条查询语句，要球返回全部联系人的姓名
            //然后查询数据库
            String[] queryFields = new String[]{
                    ContactsContract.Contacts.DISPLAY_NAME,

                    //记住这个是最重要的，别忘了
                    ContactsContract.Contacts._ID
            };
            Cursor c = getActivity().getContentResolver().
                    query(contactUri,queryFields,null,null,null);
            try{
                if (c.getCount() == 0) {
                    return;
                }
                c.moveToFirst();
                //获取联系人的姓名
                String suspect = c.getString(0);
//                String Photonumber = c.getString( 1 );
                mCrime.setSuspect(suspect);
                updateCrime();
//                mCrime.setPhotoNumber( Photonumber );
                mSuspectButton.setText(suspect);
                String _id = c.getString( 1 );
                SuspectContactId = _id;
            }finally {
                //关闭查询
                c.close();
            }

            /*
            挑战练习  添加拨号
             */
            Cursor cursor_1 = getActivity().getContentResolver()
                    .query( ContactsContract.CommonDataKinds.Phone.CONTENT_URI,
                            null,
                            ContactsContract.CommonDataKinds.Phone.CONTACT_ID + " = ?",
                            new String[]{SuspectContactId},
                            null);
            try{
                if (cursor_1.getCount() == 0){
                    return;
                }
                cursor_1.moveToFirst();
                int index = cursor_1.getColumnIndex( ContactsContract.CommonDataKinds.Phone.NUMBER );
                String number = cursor_1.getString( index );
                mCrime.setSuspectcontact( number );
                callSusoectButton.setEnabled( true );
                callSusoectButton.setText( number );
            }finally {
                cursor_1.close();
            }
        }else if (requestCode == REQUEST_PHOTO){
//            updatePhotoView();
            updateCrime();
            /**
             * 优化略缩图加载
             */
            updatePhotoView( mPhotoView.getWidth(),mPhotoView.getHeight() );
        }
    }
```
```java
 private void updateDate() {

//        mDataButton.setText(mCrime.getDate().toString());

        /**
         * 第八章挑战练习
         */
        String date = (String) DateFormat.format("EEEE, MMM dd, yyyy", mCrime.getDate());
        mDataButton.setText( date );

    }
    @SuppressLint("SetTextI18n")
    private void updateTime() {
        if (mCrime.getMinute() < 10){
            mTimeButton.setText( mCrime.getHour() + " : 0" + mCrime.getMinute() );
        }else {
            mTimeButton.setText( mCrime.getHour() + " : " + mCrime.getMinute() );
        }
    }
```
***

### 效果演示：

<center>

   ![CrimeFragment](https://upload-images.jianshu.io/upload_images/9140378-d709ded09bb22ca5.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/200)　　![TimePicker](https://upload-images.jianshu.io/upload_images/9140378-034abfcad32e2eaa.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/200)

</center>
<br>

Github具体代码：[hyyyrwang.github.io](https://github.com/wanghao15536870732/Android-programming-authority-guide/blob/master/Criminallntent2/app/src/main/java/com/example/lab/android/nuc/criminallntent/Fragment/CrimeFragment.java)<br>
简书：[https://www.jianshu.com/p/f0cb5f693f52](https://www.jianshu.com/p/f0cb5f693f52)

***
