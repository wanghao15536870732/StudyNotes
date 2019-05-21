# Android studio 找不到v4，v7包解决

> Android studio 3.1.2（可能其他版本也一样）无法引入v4、v7包报红，继承AppCompatActivity的都报 Cannot resolve symbol 'AppCompatActivity’错误，试了很多方法 修改gradle 的各种内容都无效，通过下面的步骤解决。

1、在打开2个或多个项目的情况下 关闭出错的那个项目。

2、点击左上角File--open recent ---拖到最底部Manage Projects ----删除出错的那个项目

3、重新导入改项目