# Bigram 分词

给出第一个词 first 和第二个词 second，考虑在某些文本 text 中可能以 "first second third" 形式出现的情况，其中 second 紧随 first 出现，third 紧随 second 出现。

对于每种这样的情况，将第三个词 "third" 添加到答案中，并返回答案。

示例 1：

```java
输入：text = "alice is a good girl she is a good student", first = "a", second = "good"
输出：["girl","student"]
```

示例 2：

```java
输入：text = "we will we will rock you", first = "we", second = "will"
输出：["we","rock"]
```

提示：

- 1 <= text.length <= 1000
- text 由一些用空格分隔的单词组成，每个单词都由小写英文字母组成
- 1 <= first.length, second.length <= 10
- first 和 second 由小写英文字母组成


```java
public class Solution{

    public String[] findOcurrences(String text, String first, String second) {
        String[] str = text.split(" "); // 将句子分成单词字符串数组
        String result = "";
        for (int i = 0; i < str.length - 2; i++)  //循环导倒数第三位
            if(str[i].equals(first) && str[i + 1].equals(second)) //如果匹配的话
                result = result.concat(str[i + 2]) + " ";  //以" "为后缀加到字符串rsult当中
        return result.equals("") ? new String[]{} : result.split(" ");  //判空并对整个字符串以" "分为字符串数组
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        String first = scanner.nextLine();
        String second = scanner.nextLine();
        Solution solution = new Solution();
        String[] result = solution.findOcurrences(input,first,second);
        for (int i = 0; i < result.length; i++) {
            System.out.println(result[i]);
        }
    }
}
```

最终的效果：

![image.png](https://upload-images.jianshu.io/upload_images/9140378-02713ea62e85c929.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/440)
![image.png](https://upload-images.jianshu.io/upload_images/9140378-331aa6c288cbac3c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/440)

> 来源：力扣（LeetCode）</br>
> 链接：https://leetcode-cn.com/problems/occurrences-after-bigram
