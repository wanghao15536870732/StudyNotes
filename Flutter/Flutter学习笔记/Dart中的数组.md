# 在 Dart 中，数组即 List。

```dart
var array = [1, 2, 3];
```

复制代码Dart 会自动推导数组的类型是 List<int>，你不能向里添加非 
int 类型的对象。

```dart
void main() {
  var array = ["it's string[]", 1, 2, 3];
  array.add(5);
  print(array);
}

>>>
[it's string[], 1, 2, 3, 5]

```

复制代码上面的操作是被允许的，因为该数组会被推导为 String 数组。

通过 `const` 关键字，可以创建一个常量数组：

```dart
var nums = const [1, 2, 3];
```

复制代码你不能再对 nums 进行任何的修改了。