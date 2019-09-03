# Dart中的异步任务

在 Dart 中，使用 async 和 await 关键字来处理异步任务。

```dart
task() async {
    var entrypoint = await findEntrypoint();
    print(entrypoint);
}
```

> 在上面这个 异步函数 中，进行了一个耗时任务 findEntrypoint()，然后调用了 print(entrypoint) 输出耗时任务返回结果

## async

> async 关键字是用来标识一个函数是异步函数，该类函数会有一个返回值，其类型为 Future

```dart
Future<T> login() async {
    //..
}
```

创建一个异步函数很简单，只需要给函数加个 `async` 关键字就行。

其中，范型 `T` 具体是什么，取决于你的异步函数 `return` 的是什么

## await

> await 关键字被用于修饰一个异步函数，它表示逻辑执行到这，需要等待异步函数执行完成，返回结果了才能接着执行

此时，异步函数（async修饰的函数）的返回值类型就是 `Future<T>` 中的 `T`，你无需在从 `Future` 中获取。

```dart
Future<String> task(String path) async {
  String r = await getFileContent(path);
  return r;
}
```

注意，await 关键字只能在异步函数中使用，即如果你在一个函数中使用了 await，那这个函数就需要被变为异步函数