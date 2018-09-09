---
title: Python编程快速上手 学习笔记(一) 匹配模式与正则表达式
tags:
  - Python
  - Python编程快速上手
categories: Python
top: 103
---

![正则表达式的匹配](https://upload-images.jianshu.io/upload_images/9140378-686e8aaebcf43c4b.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
***
<!--more-->

# 用正则表达式查找文本模式

## 什么是正则表达式？

+ 正则表达式简称 regex，是文本模式的描述方法
+ 例如，\d是一个正则表达式，他就可以表示0-9的任何一位数字
+ 因此，正则表达式\d\d\d-\d\d\d-\d\d\d\d就可以匹配333-333-4444 (即美国的普通电话号，而中国的电话号好像不能用正则表达式匹配，我也没想过...)

## 开始创建

### 创建正则表达式对象

Python 中的所有正则表达式都在 re 模块当中

```Python
 import re
```

向re.compile()传入一个字符串值，就表示正则表达式，会返回一个 Regex 模式对象

```python
import re
phoneNumberRegex = re.compile(r'\d\d\d-\d\d\d-\d\d\d\d')
```

现在phoneNumberRegex 变量当中包含了一个Regex对象

#### 匹配 Regex 对象

+ Regex 有一个 search() 方法用于查找传入的字符串，寻找该正则表达式的所有匹配
+ 如果没有查找到，search() 方法就会返回None
+ 如果找到了，search()  方法就会返回一个Match 对象，Match 对象有一个 group() 方法，他返回被查找字符串中实际匹配的文本

```Python
import re
if __name__ == '__main__':
    phoneNumberRegex = re.compile(r'\d\d\d-\d\d\d-\d\d\d\d')
    mo = phoneNumberRegex.search('My phonenumber is 415-234-6570')
    print(mo.group())

输出： 415-234-6570
```

## 现在可以尝试一些更强大的功能了 -- 用正则表达式匹配更多模式

### 利用括号分组

+ #### 在正则表达式中添加括号，就会创建'分组'：(\d\d\d)-(\d\d\d-\d\d\d\d)
+ #### 然后就可以使用 group(...) 方法 ，定向的取出匹配的文本

```Python
import re
if __name__ == '__main__':
    phoneNumberRegex = re.compile(r'(\d\d\d)-(\d\d\d-\d\d\d\d)')
    mo = phoneNumberRegex.search('My phonenumber is 415-234-6570')
    print(mo.group(1))
    print(mo.group(2))
    print(mo.group(0))
    print(mo.group())

输出：415
     234-6570
     415-234-6570
     415-234-6570
```

+ #### 调用 groups() 方法可以一次获得多有分组,并且可以使用多重赋值的技巧

```Python
import re
if __name__ == '__main__':
    phoneNumberRegex = re.compile(r'(\d\d\d)-(\d\d\d-\d\d\d\d)')
    mo = phoneNumberRegex.search('My phonenumber is 415-234-6570')
    print(mo.groups())
    areaCode,mainNumber = mo.groups()
    print(areaCode)
    print(mainNumber)

输出：
('415', '234-6570')
415
234-6570
```

### 利用管道(这个翻译有点骚...) 匹配多个分组

#### 什么是管道？

+ 字符 '|' 又被称为"管道"，使用它，可以匹配许多表达式中的一个，即正则表达式 wang | hao 将匹配'wang' 或 'hao'

```Python
import re
if __name__ == '__main__':
    phoneNumberRegex = re.compile(r'wang|hao')
    mo1 = phoneNumberRegex.search('my name is wang hao.')
    print(mo1.group())

    mo2 = phoneNumberRegex.search('my name is hao wang.')
    print(mo2.group())

输出：
    wang
    hao
```

+ 也可以使用管道来匹配多个模式当中的一个，作为正则表达式的一部分
+ 假设你希望匹配'wangwei','wangtao','wangxing','wangyuli'中任意一个，因为所有这些字符串都以'wang'开头的，就可以通过括号实现

```python
import re
if __name__ == '__main__':
    phoneNumberRegex = re.compile(r'wang(wei|tao|xing|yuli)')
    mo1 = phoneNumberRegex.search('my name is wangtao.')
    print(mo1.group())
    print(mo1.group(1))

输出：
    wangtao
    tao
```

+ 调用group()会返回完全匹配的wangtao，而group(1)知识返回了括号里面匹配的tao

### 利用问号实现可选匹配

```Python
import re
if __name__ == '__main__':
    phoneNumberRegex = re.compile(r'Bat(wo)?man')
    mo = phoneNumberRegex.search('The Adaventures of Batman')
    print(mo.group())

    moo = phoneNumberRegex.search('The Adaventures of Batwoman')
    print(moo.group())

输出：
    Batman
    batwoman
```

+ 正则表达式中的(wo)?部分表明，模式 wo 是可以选的部分，即改正则表达式匹配的文本当中，wo将会出现零次或一次，所以他两个字符串都会匹配
+ 修改之前寻找号码的例子

```Python
import re
if __name__ == '__main__':
    phoneNumberRegex = re.compile(r'(\d\d\d-)?\d\d\d-\d\d\d\d')
    mo = phoneNumberRegex.search('my phonenumber is 415-555-4242')
    print(mo.group())

    moo = phoneNumberRegex.search('555-4242')
    print(moo.group())

输出：
    415-555-4242
    555-4242
```

### 利用 * 匹配零次或多次

```Python
import re
if __name__ == '__main__':
    phoneNumberRegex = re.compile(r'Bat(wo)*man')
    mo = phoneNumberRegex.search('The Adaventures of Batman')
    print(mo.group())
    # Batman
    moo = phoneNumberRegex.search('The Adaventures of Batwoman')
    print(moo.group())
    # Batwoman
    mooo = phoneNumberRegex.search('The Adaventures of Batwowowowoman')
    print(mooo.group())
    # Batwowowowoman
```

### 利用 + 号实现一次或多次匹配

```Python
import re
if __name__ == '__main__':
    phoneNumberRegex = re.compile(r'Bat(wo)+man')

    mo1 = phoneNumberRegex.search('The Adaventures of Batwoman')
    print(mo1.group())
    # Batwoman
    mo2 = phoneNumberRegex.search('The Adaventures of Batwowowowoman')
    print(mo2.group())
    # Batwowowowoman
    mo3 = phoneNumberRegex.search('The Adaventures of Batman')
    print(mo3 == None)
    # True
```

### 用花括号匹配特定次数

+ 即正则表达式(Ha){3}将匹配字符串'HaHaHa',但不会匹配其他字符串
+ 除了指定数字之外，还可以指定范围，即(Ha){3,5}将匹配'HaHaHa'、'HaHaHaHa'、'HaHaHaHaHa'
+ 也可以不限范围(Ha){3,}将会匹配 3 次或者更多实例

```python
import re
if __name__ == '__main__':
    phoneNumberRegex = re.compile(r'(Ha){3}')
    mo1 = phoneNumberRegex.search('HaHaHa')
    print(mo1.group())
    # HaHaHa

    mo2 = phoneNumberRegex.search('Ha')
    # 一次的HA无法匹配三个，所以返回None
    print(mo2== None)
    # True
```

## 贪心与非贪心匹配

### Python的正则表达式默认的是‘贪心’的，这表示在又二义的情况下，他们会尽可能的匹配更长的字符串，如果想取消这种贪心，可以在结束的花括号后面跟一个问号

```python
import re
if __name__ == '__main__':
    greedyHaRegex = re.compile(r'(Ha){3,5}')
    mo1 = greedyHaRegex.search('HaHaHaHaHa')
    print(mo1.group())
    # HaHaHaHaHa

    nongreesdyHaRegex = re.compile(r'(Ha){3,5}?')
    mo2 = nongreesdyHaRegex.search('HaHaHaHaHa')
    print(mo2.group())
    # HaHaHa
```

## findall()方法

### 除了search()方法之外，Regex还有一个findall()方法。search()方法将返回一个Match对象，包含查找字符串中的‘第一次’匹配的文本，而findall()方法间给返回一组字符串，包含所有匹配

```python
import re
if __name__ == '__main__':
    phoneNumberRegex = re.compile(r'\d\d\d-\d\d\d-\d\d\d\d')
    mo1 = phoneNumberRegex.search('Cell: 435-232-5345 Work: 234-534-5533')
    print(mo1.group())
    # 435-232-5345

    mo2 = phoneNumberRegex.findall('Cell: 435-232-5345 Work: 234-534-5533')
    print(mo2)
    # ['435-232-5345', '234-534-5533']
```

### 如果正则表达式当中包含又分组，findall()就会返回远足的列表，每个元组表示一个找到的匹配

```python
import re
if __name__ == '__main__':
    phoneNumberRegex = re.compile(r'(\d\d\d)-(\d\d\d)-(\d\d\d\d)')
    mo = phoneNumberRegex.findall('Cell: 236-790-1123 Work: 465-452-6107')
    print(mo)

    # 结果：[('236', '790', '1123'), ('465', '452', '6107')]
```

## 字符分类

|缩写字符分类|表示|
|:--|:--|
|\d|0到9的任何数字|
|\D|除0到9数字之外的任何数字|
|\w|任何字母、数字、下划线字符(匹配单词字符))|
|\W|出字母、数字和下划线以外的字符|
|\s|空格、制表符或换行符(匹配空白字符)|
|\S|除空格、制表符或换行符之外的字符|

```python
import re
if __name__ == '__main__':
    phoneNumberRegex = re.compile(r'\d+\s\w+')
    mo = phoneNumberRegex.findall('12 drums,11 pipers,10 lords,9 ladies,8 maids,'
                                  '7 swans,6 geese,5 rings,4 birds,3 hens,2 doves,1 partridge')
    print(mo)

    # 结果：['12 drums', '11 pipers', '10 lords', '9 ladies', '8 maids', '7 swans', '6 geese', '5 rings', '4 birds', '3 hens', '2 doves', '1 partridge']
```

## 建立自己字符分类

### 由于以上的字符分类太过于广泛，有时候想自己约束一个范围，其实也很简单，可以用方括号来定义自己的字符串分类

### 假如现在要匹配所有的元音字符

```python
import re
if __name__ == '__main__':
    myRegex = re.compile(r'[ariouAEIOU]')
    print(myRegex.findall("Robocup eats baby food. BABY FOOD."))

    # 结果: ['o', 'o', 'u', 'a', 'a', 'o', 'o', 'A', 'O', 'O']
```

## ^ 跟 & 的用途

+ ### 可以在正则表达式的开始出插入字符，表示匹配以被查找文本开头为开始的字符串，例如 正则表达式 r'^Hello'匹配以‘Hello’开始的字符串

```python
import re
if __name__ == '__main__':
    myRegex = re.compile(r'^Hello')
    print(myRegex.search('Hello World!'))
    # <_sre.SRE_Match object; span=(0, 5), match='Hello'>
    print(myRegex.search('He said hello,') == None)
    # True
```

+ ### 那 & 想必你也知道了，就是表示 匹配以被查找文本开头为结尾的字符串，例如 正则表达式 r'\d$' 匹配以数字结尾的字符串

```python
import re
if __name__ == '__main__':
    myRegex = re.compile(r'\d$')
    print(myRegex.search('my age is 19'))
    # <_sre.SRE_Match object; span=(11, 12), match='9'>
    print(myRegex.search('my age is nineth') == None)
    # True
```

### + (r'^\d+$') 匹配都是数字的字符串

```python
import re
if __name__ == '__main__':
    myRegex = re.compile(r'^\d+$')
    print(myRegex.search('35335119'))
    # <_sre.SRE_Match object; span=(0, 8), match='35335119'>
    print(myRegex.search('13213132dflsfg') == None)
    # True
```

## 通配字符

### 什么是通配字符？

+ #### 在正则表达式当中，. (英文句点) 字符称为‘通配符’,它匹配除了换行之外的所有字符
+ #### 要注意，句点符号值匹配一个字符串

```python
import re
if __name__ == '__main__':
    myRegex = re.compile(r'.at')
    print(myRegex.findall('The cat in the hat sat on the flat mat.'))
    # ['cat', 'hat', 'sat', 'lat', 'mat']
```

### 用 .* (点-星) 匹配所有字符

+ #### 点-星也使用的是贪心模式，总是匹配尽可能多的文本

```python
import re
if __name__ == '__main__':
    myRegex = re.compile(r'Fiest Name: (.*) Last Name: (.*)')
    mo = myRegex.search('Fiest Name: AI Last Name: wanghao')
    print(mo)
    # <_sre.SRE_Match object; span=(0, 33), match='Fiest Name: AI Last Name: wanghao'>
    print(mo.group(1))
    # AI
    print(mo.group(2))
    # wanghao
```

+ #### 同样，点-星也可以使用 '非贪心' 模式,同样也是加？号

```python
import re
if __name__ == '__main__':
    greeedyRegex = re.compile(r'<.*?>')
    mo1 = greeedyRegex.search('<To go to the NUC> for study.>')
    print(mo1.group())
    # <To go to the NUC>
    nongreeedyRegex = re.compile(r'<.*>')
    mo2 = nongreeedyRegex.search('<To go to the NUC> for study.>')
    print(mo2.group())
    # <To go to the NUC> for study.>
```

## 用句点字符匹配换行

### 点-星匹配换行以外的所有字，通过传入re.DOTALL 作为 re.compile()的第二个参数，就可以让句点字符匹配所有字符， 包括换行符

```python
import re
if __name__ == '__main__':
    onNewlineRegex = re.compile(r'.*')
    mo1 = onNewlineRegex.search('Serve the public truse.\nProtext the innocent.\n'
                              'Upload the law')
    print(mo1.group())
    # Serve the public truse.
    newlineRegex = re.compile('.*',re.DOTALL)
    mo2 = newlineRegex.search('Serve the public truse.\nProtext the innocent.\n'
                              'Upload the law')
    print(mo2.group())
    # Serve the public truse.
    # Protext the innocent.
    # Upload the law
```
