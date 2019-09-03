---
title: Android编程权威指南（第2版）--第14章 SQLite数据库 挑战练习
tags:
  - Android
  - Android编程权威指南(第2版)
categories: Android
top: 88
---
***
<!--more-->

## 挑战练习：删除Crime记录

### 修改CrimeLab的deleteCrime方法
```java
public void deleteCrime(Crime c) {
        //mCrimes.remove(c);

        mDatabase.delete(
                CrimeTable.NAME,
                CrimeTable.Cols.UUID + " = ?",
                new String[] {
                  c.getId().toString();
                }
        );
}
```
***
### 前面的练习都做了的可能会发现，直接修改这个deleteCrime方法，运行删除后，app会意外终止，这是咋回事？
<br>
<center>

![what？](https://upload-images.jianshu.io/upload_images/9140378-ec679c2169d4fd52.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/240)

</center>
<br>

### 查看log之后，发现RecyclerView 报IndexOutOfBoundsException。原来是因为之前为了实现修改crime内容返回后，更新列表里的单一crime而不是全部更新的代码报错了

<center>
<br>

![woqu](https://upload-images.jianshu.io/upload_images/9140378-ad70faf55c454caf.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/2240)

<br>
</center>

```java
private void updateUI() {
        CrimeLab crimeLab = CrimeLab.get(getActivity());
        List<Crime> crimes = crimeLab.getCrimes();

        if (mAdapter == null) {
            mAdapter = new CrimeAdapter(crimes);
            mCrimeRecyclerView.setAdapter(mAdapter);
        } else {
            mAdapter.setCrimes(crimes);
            mAdapter.notifyDataSetChanged(); //全量更新
            //mAdapter.notifyItemChanged(mIndex); //单例更新 -- 此行报错
        }

        if (crimes.size() != 0) {
            mNoCrimeTextView.setVisibility(View.INVISIBLE);
            mNoCrimeButton.setVisibility(View.INVISIBLE);
        } else {
            mNoCrimeTextView.setVisibility(View.VISIBLE);
            mNoCrimeButton.setVisibility(View.VISIBLE);
        }


        updateSubtitle();

    }
```

### 调用deleteCrime方法后，该Crime实例已经从数据库中删除了。但是改回原来的notifyDataSetChanged()方法就不会报错，但是相反会牺牲效率。可以弄一个变量记录是否为删除动作，再根据判断具体调用不同的更新方法。<br>

我的简书：[https://www.jianshu.com/p/32152f1396a6](https://www.jianshu.com/p/32152f1396a6)

***
