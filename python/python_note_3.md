---
title: Python编程快速上手 学习笔记(三) 从Web抓取信息
tags:
  - Python
  - Python编程快速上手
categories: Python
top: 105
---
![u=3923554256,4102456212&fm=26&gp=0.jpg](https://upload-images.jianshu.io/upload_images/9140378-28b350a488cb4b5f.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/540)
***
<!--more-->

# Python编程快速上手 学习笔记(三) 从Web抓取信息

## 用 requests 模块从 Web 下载文件

### 首先 安装 request 模块 

+ 打开命令行，输入以下代码，并运行

```python
pip install request
```

+ 然后可以做一个测试，在 IDLE 或者 Pychrome 当中输入

```python
>>> import requests
```

+ 如果没有报错们应该表示安装成功了

### 用 requests.get() 函数下载一个网页

+ requests.get() 函数接受一个将要下载的 URL 字符串 
+ 通过在 requests.get() 的返回值上调用 type() , 会返回一个 Response 对象，其中包含Web服务器对请求做出的反应

```python
import webbrowser,sys,requests
# webbrowser 模块用于加载浏览器
# sys 模块用于读入可能的命令行参数
if __name__ == '__main__':
    res = requests.get('http://www.gutenberg.org/cache/epub/1112/pg1112.txt')
    print(type(res))
    # <class 'requests.models.Response'>
    print(res.status_code == requests.codes.ok)
    # True
    print(len(res.text))
    # 178981
    print(res.text[:250])
    # ﻿The Project Gutenberg EBook of Romeo and Juliet, by William Shakespeare
    # This eBook is for the use of anyone anywhere at no cost and with
    # almost no restrictions whatsoever.  You may copy it, give it away or
    # re-use it under the terms of the Proje
```

+ 通过检查Response对象的 res.status_code 属性，可以查看网页的访问是否成功
+ 如果请求成功，下载的页面就作为一个字符串，保存到了 Respose 对象的 text 变量当中

### 检查错误

+ 除了检查 Response 对象的 status_code 属性之外，还有一个比较简单的方法
+ 就是在 Response 对象上面调用  raise_for_status() 方法

```python
import requests
if __name__ == '__main__':
    res = requests.get('http://nothing')
    print(res.raise_for_status())
    '''
    requests.exceptions.ConnectionError: HTTPConnectionPool(host='nothing', port=80): Max retries exceeded with url: / (Caused by NewConnectionError('<urllib3.connection.HTTPConnection object at 0x00000246FDD4DB00>: Failed to establish a new connection: [Errno 11001] getaddrinfo failed',))
    '''
```

+ 可以用try 和 except 语句将 raise_for_status() 代码包裹起来，处理这一行错误，不让程序崩溃

```python
import requests
if __name__ == '__main__':
    res = requests.get('http://nothing')
    try:
        res.raise_for_status()
    except:
        print('There was a problem: %s' % (exc))
```

## 将下载的文件保存到硬盘

### 如何将数据写入文件

+ 现在可能会想用 标准的 open() 函数 跟 write() 方法，将Web 网页保存到硬盘中的一个文件
+ 首先，必须用‘ 写二进制 ’ 模式打开该文件，即向函数传入字符串‘wb’,作为 open() 的第二个参数
+ 要注意，即使该页面是纯文本的，还是要写入二进制数据，而不是文本数据

### for 循环 + iter_content() 方法

+ 为了保存到文件，可以使用for 循环 跟 Response 对象的 iter_content() 方法

```python
import requests
if __name__ == '__main__':
    res = requests.get('http://www.gutenberg.org/cache/epub/1112/pg1112.txt')
    res.raise_for_status()
    playFile = open('D:\\Desktop\\test.txt','wb')
    for chunk in res.iter_content(10000):
        playFile.write(chunk)
    playFile.close()
```

+ iter_content() 方法在循环的每一次迭代当中，返回一段内容，都是bytes数据类型，10万的字节两比较适合

### 总结大致过程：

+ 调用 requests.get() 下载该文件
+ 用‘Web’ 调用 open() .以二进制的方式打开一个新的文件
+ 利用 Respose 对象的iter_content() 方法 做循环
+ 在每一次的迭代当中调用 write() ，将内容写入文件
+ 调用 close() 关闭该文件

# HTML

