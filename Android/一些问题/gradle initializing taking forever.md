# Android Flutter 常见错误

## 1. gradle initializing taking forever（一直在 Initializing gradle）

+ 尝试手动安装[/gradle-4.6-bin.zip](https://services.gradle.org/distributions/gradle-4.6-bin.zip)，然后解压缩
+ 打开<path_to_flutter_app> / android / gradlew
+ 查找：CLASSPATH = $ APP_HOME / gradle / wrapper / gradle-wrapper.jar 并替换为：CLASSPATH = <path_to_downloaded_gardle>/gradle-4.6/lib/gradle-launcher-4.6.jar
+ 查找：exec“$ JAVACMD”“$ {JVM_OPTS [@]}” - classpath“$ CLASSPATH”org.gradle.wrapper.GradleWrapperMain“$ @” 
+ 并替换为：exec“$ JAVACMD”“$ {JVM_OPTS [@]} “-classpath”$ CLASSPATH“org.gradle.launcher.GradleMain”$ @“

## 2.java.lang.RuntimeException: Timeout of 120000 reached waiting for exclusive access to file: C:\Users\王浩\.gradle\wrapper\dists\gradle-4.10.2-all\9fahxiiecdb76a5g3aw9oi8rv\gradle-4.10.2-all.zip

+ 1.删除/Users/weidingqiang/.gradle/wrapper/dists/gradle-2.4-all
+ 2.重新下载gradle-2.4-all.zip，放到/Users/weidingqiang/.gradle/wrapper/dists/gradle-2.4-all/3i2gobhdl0fm2tosnn15g540i0/ 目录下
+ 即可