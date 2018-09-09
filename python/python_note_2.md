---
title: Python编程快速上手 学习笔记(二) 电话号码和 E-mail 地址提取程序
tags:
  - Python
  - Python编程快速上手
categories: Python
top: 104
---
![12.jpg](https://upload-images.jianshu.io/upload_images/9140378-b5624c2f9b81ebb6.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
***
<!--more-->

# Python编程快速上手 学习笔记(二)

## 先复习一下上一篇文章[Python编程快速上手 学习笔记(一) 匹配模式与正则表达式](https://wanghao15536870732.github.io/2018/09/02/python/python-note-1/) 的主要内容

|正则表达式符号|代表的意思|
| :--                  | :--                                     |
| ？                   | 匹配零次或一次前面的分组                |
| *                    | 匹配零次或多次前面的分组                |
| +                    | 匹配一次或多次前面的分组                |
| {n}                  | 匹配n次前面的分组                       |
| {n,}                 | 匹配n次或更多前面的分组                 |
| {,m}                 | 匹配零次到m次前面的分组                 |
| {n,m}                | 匹配至少n次，至多m次前面的分组          |
| {n,m}? 、 * ?  、+ ? | 对前面的分组进行非贪心匹配              |
| ^ spam               | 意味着查找的字符串必须以 spam 开头      |
| .                    | 匹配所有字符，换行字符除外              |
| \d、\w 和 \s         | 分别匹配数字、单词和空格                |
| \D、\W 和 \S         | 分别匹配数字、单词和空格 除外的所有字符 |
| [abc]                | 匹配方括号内的任意字符                  |
| [^abc]               | 匹配不在方括号内的任意字符              |

## 深入学习正则表达式

### 不区分大小写的匹配

通常，正则表达式是不区分大小写的，但是有时候，你不关心他们是不是大小写，可以向 re.compile() 传入re.IGNORECASE 或 re.I, 作为第二个参数

```Python
import re
if __name__ == '__main__':
    robocop = re.compile(r'wanghao',re.I)
    print(robocop.search('WangHao is my best friends.').group())
    # WangHao

    print(robocop.search('WANGHAO is my best friends.').group())
    # WANGHAO

    print(robocop.search('wanghao is my best friends.').group())
    # wanghao
```

### 用sub()方法替换字符串

+ 正则表达式不仅能够找到这些匹配的文本，而且还可以用新的文本替换掉这些模式，那就是 sub() 方法 这个方法接受两个参数，第一个是用于取代发现的匹配，第二个是正则表达式匹配的内容

```python
import re
if __name__ == '__main__':
    namesRegex = re.compile(r'Wang \w+')
    mo = namesRegex.sub('CENSORED','Wang hao gives the ben to Wang Tao')
    print(mo)
    # CENSORED gives the ben to CENSORED
```

+ 有时候，你可能需要使用匹配的文本本身，作为替换的一部分，sub() 第一个参数的 \1、\2、\3 ......,表示‘在替换中输入分组1、2、3......的文本’

+ 例如加入要隐去密探的姓名，只显示他们名字的第一个字母， 就可以使用正则表达式 Wang(\w)\w* ,传入 'r\1****' 作为sub() 的第一个参数，字符串中的\1 将由分组 1 匹配的文本所替代

```python
import re
if __name__ == '__main__':
    agentNamesRegex = re.compile(r'Wang (\w)\w*')
    mo = agentNamesRegex.sub(r'\1***','Wang hao gives Wang tianrui to Wang tao.')
    print(mo)
    # h*** gives t*** to t***.
```

### 管理复杂的正则表达式

+ 匹配简单的文本模式，正则表达式还应付过来，但是要匹配复杂的文本模式，可能会有点棘手，不过，你可以告诉 re.compile() ,忽略正则表达式字符串中的空白符和注释，从而缓解这一点，要想实现这一模式，可以向re.compile() 传入变量 re.VERBOSE,作为第二个参数
+ 摈弃了之前的这种啰嗦

```python
import re
if __name__ == '__main__':
    phoneRegex = re.compile(r'(((\d{3}|\(\d{3}\)))?(\s|-|\.)?\d{3}(\s|-|\.)\d{4}(\s*(ext|x|ext.)\s*\d{2,5})?)')

```

+ 改进之后的表达式

```python
import re
if __name__ == '__main__':
    phoneRegex = re.compile(r'''(
        ((\d{3}|\(\d{3}\)))?  # 电话地区号
        (\s|-|\.)?    # 分隔符
        \d{3}    # 前3位数字
        (\s|-|\.)   # 分隔符
        \d{4}   # 后四位数字
        (\s*(ext|x|ext.)\s*\d{2,5})?   # 拓展
        )''',re.VERBOSE)
```

### 组合使用 re.IGNORECASE、re.DOTALL 和 re.VERBOSE

如果你想用 re.VERBOSE 来鞭子额注释，又想用 re.IGNORECASE 来忽略大小写，抱歉，re.compile 函数只接受一个只作为它的第二个参数，不过我们可以使用管道来跳过这个限制，即用 | 将两个参数分隔开

```python
someRegex = re.compile('foo' ,re.IGNORECASE | re.UNICODE)
```

## 电话号码和 E-mail 地址提取程序

### 先为电话号码创建一个正则表达式

首先需要创建一个正则表达式才能够用来查找电话号码

```Python
import re,pyperclip
if __name__ == '__main__':
    phoneRegex = re.compile(r'''(
        (\d{3}|\(\d{3}\))?  # 电话地区号 三个数字(即\d{3}) 或括号里面三个数字(即 \(\d{3}\) )
        (\s|-|\.)?    # 分隔符  空格(\s)、短横(-) 或 句点 (.)
        \d{3}    # 前3位数字
        (\s|-|\.)   # 分隔符
        \d{4}   # 后四位数字
        (\s*(ext|x|ext.)\s*\d{2,5})?   # 拓展
        )''',re.VERBOSE)
```

### 为 E-mail 地址创建一个正则表达式

+ 用户名可以是一个或多个字符串，大小写字母、数字、句点、下划线、百分号、加号或短横
+ 域名跟姓名用 @ 分隔开
+ 姓名 可以是大小写字母、数字、句号跟下划线
+ .com 部分 其实可以匹配 .三个字母

```python
emailRegex = re.compile(r'''
        [a-zA-Z0-9._%+-]+  # username
        @               # @符号
        [a-zA-Z0-9._]+  # 姓名
        (\.[a-zA-Z]{2,4})  # . 跟其他的一些东西
        ''',re.VERBOSE)
```

### 在剪切板文本中找到所有匹配

```python
 text = str(pyperclip.paste())
    matches = []
    # 查找 电话号码
    for groups in phoneRegex.findall(text):
        #  1、3、5 正好是 区号、前三个跟后四个数字
        phoneNum = '_'.join([groups[1],groups[3],groups[5]])
        if groups[8] != '':
            phoneNum += ' x' + groups[8]
        matches.append(phoneNum)
    # 查找 电子邮件
    for groups in emailRegex.findall(text):
        matches.append(groups[0])
```

### 所有匹配连接成一个字符串，赋值到剪切板

```python
 if len(matches) > 0:
        pyperclip.copy('\n'.join(matches))
        print('Copied to clipboard:')
        print('\n'.join(matches))
    else:
        print('No phone numbers or emial address found.')
```

### 运行程序

打开浏览器，访问　[https://nostarch.com/contactus](https://nostarch.com/contactus)　,将页面当中的所有数据赋值到剪切板，打开程序，运行

```python
import re,pyperclip
if __name__ == '__main__':
    # 电话号码的正则表达式
    phoneRegex = re.compile(r'''(
        (\d{3}|\(\d{3}\))?  # 电话地区号
        (\s|-|\.)?    # 分隔符
        (\d{3})    # 前3位数字
        (\s|-|\.)   # 分隔符
        (\d{4})   # 后四位数字
        (\s*(ext|x|ext\.)\s*(\d{2,5}))?   # 拓展
        )''',re.VERBOSE)
    # E-mial 的正则表达式
    emailRegex = re.compile(r'''(
        [a-zA-Z0-9._%+-]+  # username
        @               # @符号
        [a-zA-Z0-9.-]+  # 姓名
        (\.[a-zA-Z]{2,4})  # . 跟其他的一些东西
        )''',re.VERBOSE)
    text = str(pyperclip.paste())
    matches = []
    # 查找 电话号码
    for groups in phoneRegex.findall(text):
        #  1、3、5 正好是 区号、前三个跟后四个数字
        phoneNum = '-'.join([groups[1],groups[3],groups[5]])

        if groups[8] != '':
            phoneNum += ' x' + groups[8]
        matches.append(phoneNum)
    # 查找 电子邮件
    for groups in emailRegex.findall(text):
        matches.append(groups[0])
    if len(matches) > 0:
        pyperclip.copy('\n'.join(matches))
        print('Copied to clipboard:')
        print('\n'.join(matches))
    else:
        print('No phone numbers or emial address found.')
```

```python
# 结果：
    '''
    Copied to clipboard:
    800-420-7240
    415-863-9900
    415-863-9950
    info@nostarch.com
    media@nostarch.com
    academic@nostarch.com
    info@nostarch.com
    '''
```

***

具体代码：Github Pages:  　[hyyyrwang.github.io](https://github.com/wanghao15536870732/Quick-Python-Programming/blob/master/automate_online_materials/phoneAndEmail.py)