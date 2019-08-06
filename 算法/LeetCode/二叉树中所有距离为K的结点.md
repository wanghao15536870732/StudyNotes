# 二叉树中所有距离为K的结点

给定一个二叉树（具有根结点 root）， 一个目标结点 target ，和一个整数值 K 。

返回到目标结点 target 距离为 K 的所有结点的值的列表。 答案可以以任何顺序返回。

示例 1：

```c
输入：root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2

输出：[7,4,1]

解释：
所求结点为与目标结点（值为 5）距离为 2 的结点，
值分别为 7，4，以及 1
```

![tree](https://upload-images.jianshu.io/upload_images/9140378-619d827f7ca48876.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/240))

> 注意，输入的 "root" 和 "target" 实际上是树上的结点。
上面的输入仅仅是对这些对象进行了序列化描述。

提示：

- 给定的树是非空的，且最多有 K 个结点。
- 树上的每个结点都具有唯一的值 0 <= node.val <= 500 。
- 目标结点 target 是树上的结点。
- 0 <= K <= 1000.



### 最终代码

```java
class Solution {
    private List<Integer> results = new ArrayList<>();//记录结果
    private Set<TreeNode> visited = new HashSet<>();//记录访问过的节点

    //找到左右父节点，递归BFS遍历3个节点，即可得到结果
    public List<Integer> distanceK(TreeNode root, TreeNode target, int K) {
        gain(root,target,K);
        return results;
    }

    public void gain(TreeNode root,TreeNode target,int K){
        if(K==0&&target!=null){
            results.add(target.val);
            return;
        }
        if(target==null){
            return;
        }
        //找到target节点的父节点随后深度优先遍历
        TreeNode parent = findParent(root,target);
        List<TreeNode> travel = new ArrayList<>();
        travel.add(parent);
        travel.add(target.left);
        travel.add(target.right);
        visited.add(target);//添加进入集合
        //发散递归遍历
        for(TreeNode item:travel){
            if(!visited.contains(item)){
                gain(root,item,K-1);
            }
        }
    }

    private TreeNode findParent(TreeNode root,TreeNode target){
        if(target==null||root==null){
            return null;
        }
        if(root.left==target||root.right==target){
            return root;
        }
        TreeNode parent = findParent(root.left,target);
        if(parent==null){
            parent = findParent(root.right,target);
        }
        return parent;
    }
}
```

> 来源：力扣（LeetCode）</br>
> 链接：https://leetcode-cn.com/problems/all-nodes-distance-k-in-binary-tree
