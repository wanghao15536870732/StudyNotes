---
title: Android编程权威指南(第2版) --第15章 隐式Intetnt 挑战练习
tags:
  - Android
  - Android编程权威指南(第2版)
categories: Android
top: 89
---
***
<!--more-->
## <center>本章主要讲述了如何使用Intent以及SQLite数据库的一些总结</center>


## 挑战练习：ShareCompat

```java

mReportButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                /*Intent i = new Intent(Intent.ACTION_SEND);
                i.setType("text/plain");
                i.putExtra(Intent.EXTRA_TEXT, getCrimeReport());
                i.putExtra(Intent.EXTRA_SUBJECT,
                        getString(R.string.crime_report_subject));
                i = Intent.createChooser(i, getString(R.string.send_report));
                startActivity(i);*/

                ShareCompat.IntentBuilder i = ShareCompat.IntentBuilder.from(getActivity());
                i.setType("text/plain");
                i.setText(getCrimeReport());
                i.setSubject(getString(R.string.send_report));
                i.startChooser();
            }
        });

```

### 参照大神博客：[点击打开链接](http://blog.csdn.net/zerrone/article/details/70521841?utm_source=itdadao&utm_medium=referral)

<br>

***

## 15.6 挑战练习：又一个隐式intent<br>

+ ### 增加一个call按钮，修改fragment_crime.xml

```java
<Button
        android:id="@+id/crime_call_suspect"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:text="@string/crime_call_suspect_text"
        android:layout_marginLeft="16dp"
        android:layout_marginRight="16dp"/>
```
+ ### 修改strings.xml，增加
```java
<string name="crime_call_suspect_text">Call Suspect</string>
```

+ ### 修改AndroidManifest.xml增加android.permission.READ_CONTACTS权限

```java
    </application>
    <uses-permission android:name="android.permission.READ_CONTACTS"/>
</manifest>
```


***

+ ### 增加数据库表及Crime字段SuspectContact

#### Crime.java

```java
private String mSuspectContact;

public String getSuspectContact() {
        return mSuspectContact;
    }

    public void setSuspectContact(String suspectContact) {
        mSuspectContact = suspectContact;
    }

```
***

###  CrimeLab.java
```java
private static ContentValues getContentValues (Crime crime) {
        ContentValues values = new ContentValues();
        values.put(CrimeTable.Cols.UUID, crime.getId().toString());
        values.put(CrimeTable.Cols.TITLE, crime.getTitle());
        values.put(CrimeTable.Cols.DATE, crime.getDate().getTime());
        values.put(CrimeTable.Cols.HOUR, crime.getHour());
        values.put(CrimeTable.Cols.MINUTE, crime.getMinute());
        values.put(CrimeTable.Cols.SOLVED, crime.isSolved() ? 1 : 0);
        values.put(CrimeTable.Cols.SUSPECT, crime.getSuspect());
        values.put(CrimeTable.Cols.SuspectContact, crime.getSuspectContact());//add this one

        return values;
    }
```
***

### CrimeDbSchema.java
```java
public static final class CrimeTable {
        public static final String NAME = "crimes";

        public static final class Cols {
            public static final String UUID = "uuid";
            public static final String TITLE = "title";
            public static final String DATE = "date";
            public static final String HOUR = "hour";
            public static final String MINUTE = "minute";
            public static final String SOLVED = "solved";
            public static final String SUSPECT = "suspect";
            public static final String SuspectContact = "suspectcontact"; //add this one
        }
    }
```
***

### CrimeBaseHelper.java
```java
public void onCreate(SQLiteDatabase db) {
        db.execSQL("create table " + CrimeTable.NAME + "(" +
                " _id integer primary key autoincrement, " +
                CrimeTable.Cols.UUID + ", " +
                CrimeTable.Cols.TITLE + ", " +
                CrimeTable.Cols.DATE + ", " +
                CrimeTable.Cols.HOUR + ", " +
                CrimeTable.Cols.MINUTE + ", " +
                CrimeTable.Cols.SOLVED + ", " +
                CrimeTable.Cols.SUSPECT + ", " +
                CrimeTable.Cols.SuspectContact + //add this one
                ")"
        );

    }
```
***

### CrimeCursorWrapper.java
```java
public Crime getCrime() {
        String uuidString = getString(getColumnIndex(CrimeTable.Cols.UUID));
        String title = getString(getColumnIndex(CrimeTable.Cols.TITLE));
        long date = getLong(getColumnIndex(CrimeTable.Cols.DATE));
        int hour = getInt(getColumnIndex(CrimeTable.Cols.HOUR));
        int minute = getInt(getColumnIndex(CrimeTable.Cols.MINUTE));
        int isSolved = getInt(getColumnIndex(CrimeTable.Cols.SOLVED));
        String suspect = getString(getColumnIndex(CrimeTable.Cols.SUSPECT));
        String suspectcontact = getString(getColumnIndex(CrimeTable.Cols.SuspectContact)); //add this one


        Crime crime = new Crime(UUID.fromString(uuidString));
        crime.setTitle(title);
        crime.setDate(new Date(date));
        crime.setHour(hour);
        crime.setMinute(minute);
        crime.setSolved(isSolved != 0);
        crime.setSuspect(suspect);
        crime.setSuspectContact(suspectcontact);//add this one


        return crime;
    }
```

***

### CrimeFragment.java   　　
+ #### onCreateView
```java
// Call Suspect function
        mCallSuspectButton = (Button) v.findViewById(R.id.crime_call_suspect);
        if (mCrime.getSuspectContact() == null) {
            mCallSuspectButton.setEnabled(false);
        } else {
            mCallSuspectButton.setEnabled(true);
            mCallSuspectButton.setText(mCrime.getSuspectContact());
        }
        mCallSuspectButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //startActivity(callContact);
                Intent intent = new Intent(Intent.ACTION_DIAL);
                intent.setData(Uri.parse("tel:" + mCrime.getSuspectContact()));
                startActivity(intent);
            }
        });
```
+ #### onActivityResult
```java
else if (requestCode == REQUEST_CONTACT && data != null) {
            Uri contactUri = data.getData();
            // Specify which fields you want your query to return values for
            String[] queryFields = new String[] {
                    ContactsContract.Contacts.DISPLAY_NAME,
                    ContactsContract.Contacts._ID
            };
            // Perform your query - the contactUri is like a "where" clause here
            Cursor c = getActivity().getContentResolver()
                    .query(contactUri, queryFields, null, null, null);

            String SuspectContactId = null;
            try {
                // Double-check that you actually got results
                if (c.getCount() == 0) {
                    return;
                }

                // Pull out the first column of the first row of data that is your suspect's name
                c.moveToFirst();
                String suspect = c.getString(0);
                mCrime.setSuspect(suspect);
                mSuspectButton.setText(suspect);

                String _id = c.getString(1);
                //mCrime.setSuspectContactId(_id);
                SuspectContactId = _id;

            } finally {
                c.close();
            }

            Cursor cursor = getActivity().getContentResolver()
                    .query(ContactsContract.CommonDataKinds.Phone.CONTENT_URI,
                            null,
                            ContactsContract.CommonDataKinds.Phone.CONTACT_ID + " = ?",
                            new String[] {SuspectContactId},
                    null);

            try {
                if (cursor.getCount() == 0) {
                    return;
                }

                cursor.moveToFirst();
                int index = cursor.getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER);
                String number = cursor.getString(index);
                mCrime.setSuspectContact(number);
                mCallSuspectButton.setEnabled(true);
                mCallSuspectButton.setText(number);

            } finally {
                cursor.close();
            }
        }
```
***

### 效果演示图：

<center>

![Screenshot_20180811-113519.png](https://upload-images.jianshu.io/upload_images/9140378-c19672464fd33f79.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/200)　　![Screenshot_20180811-113525.png](https://upload-images.jianshu.io/upload_images/9140378-64fb6769f08f32c4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/200)

</center>
<br>

Github具体代码：[hyyyrwang.github.io](https://github.com/wanghao15536870732/Android-programming-authority-guide/tree/master/Criminallntent2)
<br>
我的简书：[https://www.jianshu.com/p/c0c46a593c66](https://www.jianshu.com/p/c0c46a593c66)
***
