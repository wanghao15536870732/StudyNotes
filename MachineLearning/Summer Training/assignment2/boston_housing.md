


## 项目 : 预测波士顿房价


欢迎来到 DSVC 《机器学习》研讨班第二周的项目！在此文件中，有些示例代码已经提供给你，但你还需要实现更多的功能来让项目成功运行。除非有明确要求，你无须修改任何已给出的代码。以**编程练习**开始的标题表示接下来的内容中有需要你必须实现的功能。每一部分都会有详细的指导，需要实现的部分也会在注释中以**TODO**标出。请仔细阅读所有的提示！

除了实现代码外，你还**必须**回答一些与项目和实现有关的问题。每一个需要你回答的问题都会以**'问题 X'**为标题。请仔细阅读每个问题，并且在问题后的**'回答'**文字框中写出完整的答案。你的项目将会根据你对问题的回答和撰写代码所实现的功能来进行评分。

>**提示：**Code 和 Markdown 区域可通过 **Shift + Enter** 快捷键运行。此外，Markdown可以通过双击进入编辑模式。

---
## 第一步. 导入数据
在这个项目中，你将利用马萨诸塞州波士顿郊区的房屋信息数据训练和测试一个模型，并对模型的性能和预测能力进行测试。通过该数据训练后的好的模型可以被用来对房屋做特定预测---尤其是对房屋的价值。对于房地产经纪等人的日常工作来说，这样的预测模型被证明非常有价值。

此项目的数据集来自[UCI机器学习知识库(数据集已下线)](https://archive.ics.uci.edu/ml/datasets.html)。波士顿房屋这些数据于1978年开始统计，共506个数据点，涵盖了麻省波士顿不同郊区房屋14种特征的信息。本项目对原始数据集做了以下处理：
- 有16个`'MEDV'` 值为50.0的数据点被移除。 这很可能是由于这些数据点包含**遗失**或**看不到的值**。
- 有1个数据点的 `'RM'` 值为8.78. 这是一个异常值，已经被移除。
- 对于本项目，房屋的`'RM'`， `'LSTAT'`，`'PTRATIO'`以及`'MEDV'`特征是必要的，其余不相关特征已经被移除。
- `'MEDV'`特征的值已经过必要的数学转换，可以反映35年来市场的通货膨胀效应。

运行下面区域的代码以载入波士顿房屋数据集，以及一些此项目所需的Python库。如果成功返回数据集的大小，表示数据集已载入成功。


```python
# 载入此项目所需要的库
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# 检查你的Python版本
from sys import version_info
if version_info.major != 3 and version_info.minor != 6:
    raise Exception('请使用Python 3.6来完成此项目')
    
# 让可视化的结果在notebook中显示
%matplotlib inline
```


```python
# 载入波士顿房屋的数据集
data = pd.read_csv('housing.csv')
prices = data['MEDV']
features = data.drop('MEDV', axis = 1)
    
# 完成
print("Boston housing dataset has {} data points with {} variables each.".format(*data.shape))
```

    Boston housing dataset has 489 data points with 4 variables each.
    

__下面三张图的横坐标分别是：住宅平均房间数量、区域中被认为是低收入阶层的比率和镇上学生与教师数量比例，纵坐标是房屋的中值价格__


```python
plt.figure(figsize=(20, 10))
plt.subplot(2, 2, 1)
plt.title('RM')
plt.scatter(features.get_values()[:, 0], prices.get_values())
plt.subplot(2, 2, 2)
plt.title('LSTAT')
plt.scatter(features.get_values()[:, 1], prices.get_values())
plt.subplot(2, 2, 3)
plt.title('PTRATIO')
plt.scatter(features.get_values()[:, 2], prices.get_values())
```




    <matplotlib.collections.PathCollection at 0x1ffad04c668>




![png](output_5_1.png)


---
## 第二步. 分析数据
在项目的第一个部分，你会对波士顿房地产数据进行初步的观察并给出你的分析。通过对数据的探索来熟悉数据可以让你更好地理解和解释你的结果。

由于这个项目的最终目标是建立一个预测房屋价值的模型，我们需要将数据集分为**特征(features)**和**目标变量(target variable)**。
- **特征** `'RM'`， `'LSTAT'`，和 `'PTRATIO'`，给我们提供了每个数据点的数量相关的信息。
- **目标变量**：` 'MEDV'`，是我们希望预测的变量。

他们分别被存在`features`和`prices`两个变量名中。

### 编程练习 1：基础统计运算
你的第一个编程练习是计算有关波士顿房价的描述统计数据。我们已为你导入了` numpy `，你需要使用这个库来执行必要的计算。这些统计数据对于分析模型的预测结果非常重要的。
在下面的代码中，你要做的是：
- 计算`prices`中的`'MEDV'`的最小值、最大值、均值、中值和标准差；
- 将运算结果储存在相应的变量中。


```python
#TODO 1

#目标：计算价值的最小值
minimum_price = None
minimum_price = np.min(prices)

#目标：计算价值的最大值
maximum_price = None
maximum_price = np.max(prices)


#目标：计算价值的平均值
mean_price = None
mean_price = np.mean(prices)

#目标：计算价值的中值
median_price = None
median_price = np.median(prices)

#目标：计算价值的标准差
std_price = None
std_price = np.std(prices)

#目标：输出计算的结果
print("Statistics for Boston housing dataset:\n")
print("Minimum price: ${:,.2f}".format(minimum_price))
print("Maximum price: ${:,.2f}".format(maximum_price))
print("Mean price: ${:,.2f}".format(mean_price))
print("Median price ${:,.2f}".format(median_price))
print("Standard deviation of prices: ${:,.2f}".format(std_price))
```

    Statistics for Boston housing dataset:
    
    Minimum price: $105,000.00
    Maximum price: $1,024,800.00
    Mean price: $454,342.94
    Median price $438,900.00
    Standard deviation of prices: $165,171.13
    

### 问题 1 - 特征观察

如前文所述，本项目中我们关注的是其中三个值:`'RM'`、`'LSTAT'` 和`'PTRATIO'`，对每一个数据点:
- `'RM'` 是该地区中每个房屋的平均房间数量；
- `'LSTAT'` 是指该地区有多少百分比的房东属于是低收入阶层（有工作但收入微薄）；
- `'PTRATIO'` 是该地区的中学和小学里，学生和老师的数目比（`学生/老师`）。

_凭直觉，上述三个特征中对每一个来说，你认为增大该特征的数值，`'MEDV'`的值会是**增大**还是**减小**呢？每一个答案都需要你给出理由。_

**提示：**你预期一个`'RM'` 值是6的房屋跟`'RM'` 值是7的房屋相比，价值更高还是更低呢？

### 问题 1 - 回答：

- `RM`值越大，代表该地区每个房屋的平均房间数量越多，则该地区的房价就越高。
- `LSTAT`值越大，代表该地区低收入阶层的房东越多，则该地区整体的房价也就越低，从上图的图像趋势也可以看得出来。
- `PTRATIO`值越大，学生相比老师要更多，表示教育资源更匮乏，房价更低。

### 编程练习 2: 数据分割与重排
接下来，你需要把波士顿房屋数据集分成训练和测试两个子集。通常在这个过程中，数据也会被重排列，以消除数据集中由于顺序而产生的偏差。
在下面的代码中，你需要

将`features`和`prices`的数据都分成用于训练的数据子集和用于测试的数据子集。
  - 分割比例为：80%的数据用于训练，20%用于测试；
  - 选定一个数值以设定 `random_seed` ，这会确保结果的一致性；
  - 提示：打乱训练集和测试集的数据时，只要创建一个 list，然后用这个 list 分别应用于 X，y 生成训练集和测试集。
 ```
 test = np.array([1, 3, 5, 7, 9, 11])
 """ test[[0,1,2]] = [1, 3, 5]
 """ test[[1,3,5]] = [3, 7, 11]
 ```
  
  可能需要用到的函数
  - (numpy.random.seed)[https://docs.scipy.org/doc/numpy/reference/generated/numpy.random.seed.html]
  - (numpy.random.shuffle)[https://docs.scipy.org/doc/numpy/reference/generated/numpy.random.shuffle.html]


```python
print(features.shape)
print(prices.shape)
```

    (489, 3)
    (489,)
    


```python
features.values
```




    array([[ 6.575,  4.98 , 15.3  ],
           [ 6.421,  9.14 , 17.8  ],
           [ 7.185,  4.03 , 17.8  ],
           ...,
           [ 6.976,  5.64 , 21.   ],
           [ 6.794,  6.48 , 21.   ],
           [ 6.03 ,  7.88 , 21.   ]])




```python
klist = np.array([[1,2,3],
         [4,5,6],
         [7,8,9]])
np.random.shuffle(klist)
print(klist)
X_train = klist[:2,:]
print(X_train)
```

    [[7 8 9]
     [4 5 6]
     [1 2 3]]
    [[7 8 9]
     [4 5 6]]
    


```python
LEN, seed = 489, 666
test_ratio = 0.2 # 测试数据所占比例
def generate_train_and_test(X, y):
    """打乱并分割数据为训练集和测试集"""
    np.random.seed(seed)  # 设置随机种子
    
    test_size = int(LEN * test_ratio)  # 计算测试数据的size
    
    list = X.copy()  # 拷贝用于随机矩阵使用
    np.random.shuffle(list)
    X_train = list[test_size:,:]
    X_test = list[:test_size,:]
    
    list = y.copy()
    np.random.shuffle(list)
    y_train = list[test_size:]
    y_test = list[:test_size]
    
    return X_train, X_test, y_train, y_test

X_train, X_test, y_train, y_test = generate_train_and_test(features.values, prices.values)
```


```python
#  另外一种方法，使用np.random.ermutation()方法
LEN, seed = 489, 666
test_ratio = 0.2 # 测试数据所占比例
def generate_train_and_test(X, y):
    """打乱并分割数据为训练集和测试集"""
    random_seed = np.random.seed(seed)
    shuffled_indexes = np.random.permutation(LEN) #随机打乱X长度的数 
    # 补充一个np.random.permutation与np.random.shuffle的不同之处
    # permutation会返回一个打乱后的副本；而shuffle只是打乱进行洗牌，并没有返回值
    # 传入参数返回洗牌后的arange

    test_size = int(len(X) * test_ratio) # 测试数据的大小
    test_indexed = shuffled_indexes[:test_size] # 取出测试数据的下标,0 - test_size
    train_indexes = shuffled_indexes[test_size:] # 取出训练数据的下标,test_size - len(X)

    X_train = X[train_indexes,:]  # 根据下标取出训练数据
    y_train = y[train_indexes]

    X_test = X[test_indexed,:]  # 根据下标取出测试数据
    y_test = y[test_indexed]
    
    
    return X_train, X_test, y_train, y_test

X_train, X_test, y_train, y_test = generate_train_and_test(features.values, prices.values)
```


```python
# 用于测试
n1 = np.random.permutation(10)
print(n1)

list = [1,2,3,4]
np.random.shuffle(list)
print(list)
```

    [2 3 0 5 9 6 4 8 1 7]
    [1, 4, 3, 2]
    

### 问题 2 - 训练及测试
*将数据集按一定比例分为训练用的数据集和测试用的数据集对学习算法有什么好处？*

*如果果用模型已经见过的数据，例如部分训练集数据进行测试，又有什么坏处？*

**提示：** 如果没有数据来对模型进行测试，会出现什么问题？

### 问题 2 - 回答:

- 将数据集分为`训练集`跟`测试集`的目的，是可以利用`测试数据集`对`训练数据集`训练得到的模型进行测试，以保证模型的各项拟合能力
- 使用模型已经见过的数据，无法对模型起到矫正作用，即使模型出现了过拟合、欠拟合等问题，也无法检测出来。
- 如果没有数据来对模型进行测试，就无法得出整个模型的拟合效果，也就不清楚这个模型到底做得好不好了。

---
## 第三步. 模型衡量标准

### 编程练习3：定义衡量标准
如果不能对模型的训练和测试的表现进行量化地评估，我们就很难衡量模型的好坏。通常我们会定义一些衡量标准，这些标准可以通过对某些误差或者拟合程度的计算来得到。在这个项目中，你将通过运算[*决定系数*](http://stattrek.com/statistics/dictionary.aspx?definition=coefficient_of_determination) R<sup>2</sup> 来量化模型的表现。模型的决定系数是回归分析中十分常用的统计信息，经常被当作衡量模型预测能力好坏的标准。

R<sup>2</sup>的数值范围从0至1，表示**目标变量**的预测值和实际值之间的相关程度平方的百分比。一个模型的R<sup>2</sup> 值为0还不如直接用**平均值**来预测效果好；而一个R<sup>2</sup> 值为1的模型则可以对目标变量进行完美的预测。从0至1之间的数值，则表示该模型中目标变量中有百分之多少能够用**特征**来解释。_模型也可能出现负值的R<sup>2</sup>，这种情况下模型所做预测有时会比直接计算目标变量的平均值差很多。_

在下方代码的 `performance_metric` 函数中，你要实现：
- 计算 `y_true` 和 `y_predict`的R<sup>2</sup>值，作为对其表现的评判，可参考[`r2_score`](http://scikit-learn.org/stable/modules/generated/sklearn.metrics.r2_score.html)。
- 将他们的表现评分储存到`score`变量中。


### $$R^2 = \frac{\sum_{i=1}{}{(y_{true}^{(i)} -y_{predict}})^2}{\sum_{i=1}{}(y_{true}^{(i)} -\bar{y}_{true})^2} = \frac{\sum_{i=1}{}{(y_{true}^{(i)} -y_{predict}})^2}{\sigma_{y_{true}}^2} $$


```python
# 使用循环的方式
def performance_metric_have_loops(y_true, y_predict):
    """计算并返回预测值相比于预测值的分数"""
    
    score_sum = 0.0
    score_var = 0.0
    for index,item in enumerate(y_true):
        score_sum += (item - y_predict[index]) ** 2  # 计算分子
    for item in y_true:
        score_var += (item - np.mean(y_true)) ** 2  # 计算坟分母
    score = score_sum / score_var
    
    return score
```


```python
# 使用无循环的方式
def performance_metric_no_loops(y_true, y_predict):
    """计算并返回预测值相比于预测值的分数"""
    
    mean_squared_error = np.sum((np.array(y_true) - np.array(y_predict))** 2) / len(y_true) # 直接进行计算MSE

    score = mean_squared_error / np.var(y_true)  # 除以var()计算得出的方差，得出R Square值

    return score
```

### 问题 3 - 拟合程度

假设一个数据集有五个数据且一个模型做出下列目标变量的预测：

| 真实数值 | 预测数值 |
|:---:|:---:|
| 3.0 | 2.5 |
| -0.5 | 0.0 |
| 2.0 | 2.1 |
| 7.0 | 7.8 |
| 4.2 | 5.3 |

*你觉得这个模型已成功地描述了目标变量的变化吗？如果成功，请解释为什么，如果没有，也请给出原因。*  

**提示**：运行下方的代码，使用`performance_metric`函数来计算模型的决定系数。


```python
# 计算这个模型的预测结果的决定系数
score_have_loops = performance_metric_have_loops([3, -0.5, 2, 7, 4.2], [2.5, 0.0, 2.1, 7.8, 5.3])
print("Model has a coefficient of determination(use loops), R^2, of {:.3f}.".format(score_have_loops))

score_no_loops = performance_metric_no_loops([3, -0.5, 2, 7, 4.2], [2.5, 0.0, 2.1, 7.8, 5.3])
print("Model has a coefficient of determination(no loops), R^2, of {:.3f}.".format(score_no_loops))

from sklearn.metrics import r2_score
score_sklearn = r2_score([3, -0.5, 2, 7, 4.2], [2.5, 0.0, 2.1, 7.8, 5.3])
print("Model has a coefficient of determination(method in sklearn,calculated [1 - R Square]), R^2, of {:.3f}.".format(score_sklearn))
```

    Model has a coefficient of determination(use loops), R^2, of 0.077.
    Model has a coefficient of determination(no loops), R^2, of 0.077.
    Model has a coefficient of determination(method in sklearn,calculated [1 - R Square]), R^2, of 0.923.
    

### 问题 3 - 回答:

- $R^2$值越接近1，代表模型目标变量预测的效果越好，上述模型经过我们的计算得出来$R^2$值为0.923左右，很接近与1，表明上述模型已经很成功得描述了目标变量的变化了。

## 第四步. 模型训练
### 编程练习 4：训练回归模型
在这个练习中，你将需要将所学到的内容整合，使用 **gradient descent 算法**训练一个线性回归模型。你可以尝试使用自己构建的多项式特征和 L1、L2 Loss，进行实验后，讨论他们是否对你的模型有效，并通过前面定义的 `performance_metric` 量化他们的提升效果。

在这里，你不能使用现成 package，不能使用额外 data。


## 简单梯度下降


```python
plot_x = np.linspace(-1,6,141) # -1到6分为141均等份儿
plot_y = (plot_x - 2.5) ** 2 - 1

plt.plot(plot_x,plot_y)
plt.show()
```


![png](output_33_0.png)



```python
def dJ(theta): # 在theta处的导数
    return 2 * (theta - 2.5)

def J(theta): # 在theta处的函数值
    return (theta-2.5) ** 2 - 1

theta = 0.0 # 从the等于0开始逼近
epsilon = 1e-8 # 差值的最小值break
eta = 0.1
theta_history = [theta]
while True:
    gradient = dJ(theta)
    last_theta = theta #  暂存上一次的theta值
    theta = theta - eta * gradient
    theta_history.append(theta)
    
    if(abs(J(theta) - J(last_theta)) < epsilon):
        break;
print("theta in min is: {}".format(theta))
print("value in min is: {}".format(J(theta)))

# 可视化出来
plt.plot(plot_x,plot_y) # 画出这些点
plt.plot(np.array(theta_history),J(np.array(theta_history)),color='r',marker='+')
plt.show()

```

    theta in min is: 2.499891109642585
    value in min is: -0.99999998814289
    


![png](output_34_1.png)


## 多元线性回归
$$X_b = \left\lgroup\begin{matrix}1 & X_1^{(1)} & X_2^{(1)} & ... & X_n^{(1)} \cr 1 & X_1^{(2)} & X_2^{(2)} & ... & X_n^{(2)} \cr ... & & & & ...\cr 1 & X_1^{(m)} & X_2^{(m)} & ... & X_n^{(m)} \end{matrix}\right\rgroup , \theta = \left\lgroup\begin{matrix} \theta_0 \cr \theta_1 \cr \theta_2 \cr ... \cr \theta_n \end{matrix}\right\rgroup  ,  \hat{y} = X_b \cdot \theta$$

### 目标：使$J(\theta) = \sum_{i=1}^{m}{(y_i - \hat{y_i})^2} = \sum_{i=1}^{m}{(y^{(i)} - \theta_0 - \theta_1 X_1^{(i)} - \theta_2 X_2^{(i)} - ... - \theta_n X_n^{(i)})^2}$尽可能小

$\bigtriangledown J(\theta) = \left\lgroup\begin{matrix} \frac{\partial J}{\partial \theta_0} \cr \frac{\partial J}{\partial \theta_1} \cr \frac{\partial J}{\partial \theta_2} \cr ... \cr \frac{\partial J}{\partial \theta_n} \end{matrix}\right\rgroup = \left\lgroup\begin{matrix} \sum_{i = 1}^{m}{2(y^{(i)} - X_b^{(i)} \theta) \cdot (-1)} \cr \sum_{i = 1}^{m}{2(y^{(i)} - X_b^{(i)} \theta) \cdot (-X_1^{(i)})} \cr \sum_{i = 1}^{m}{2(y^{(i)} - X_b^{(i)} \theta) \cdot (-X_2^{(i)})} \cr ... \cr \sum_{i = 1}^{m}{2(y^{(i)} - X_b^{(i)} \theta) \cdot (-X_n^{(i)})} \end{matrix}\right\rgroup = 2 \cdot \left\lgroup\begin{matrix} \sum_{i = 1}^{m}{(X_b^{(i)} \theta - y^{(i)} )} \cr \sum_{i = 1}^{m}{(X_b^{(i)} \theta - y^{(i)}) \cdot X_1^{(i)}} \cr \sum_{i = 1}^{m}{(X_b^{(i)} \theta - y^{(i)}) \cdot X_2^{(i)}} \cr ... \cr \sum_{i = 1}^{m}{(X_b^{(i)} \theta - y^{(i)}) \cdot X_n^{(i)}} \end{matrix}\right\rgroup$

目标：使$\frac{1}{m} \sum_{i=1}^{m}{(y^{(i)} - \hat{y}^{(i)})^2}$ 尽可能小,有时取$\frac{1}{2 m} \sum_{i=1}^{m}{(y^{(i)} - \hat{y}^{(i)})^2}$

$\bigtriangledown J(\theta) = \left\lgroup\begin{matrix} \frac{\partial J}{\partial \theta_0} \cr \frac{\partial J}{\partial \theta_1} \cr \frac{\partial J}{\partial \theta_2} \cr ... \cr \frac{\partial J}{\partial \theta_n} \end{matrix}\right\rgroup = \frac{2}{m} \cdot \left\lgroup\begin{matrix} \sum_{i = 1}^{m}{(X_b^{(i)} \theta - y^{(i)} )} \cr \sum_{i = 1}^{m}{(X_b^{(i)} \theta - y^{(i)}) \cdot X_1^{(i)}} \cr \sum_{i = 1}^{m}{(X_b^{(i)} \theta - y^{(i)}) \cdot X_2^{(i)}} \cr ... \cr \sum_{i = 1}^{m}{(X_b^{(i)} \theta - y^{(i)}) \cdot X_n^{(i)}} \end{matrix}\right\rgroup$


```python
# TODO 4

# input: X_b:行向量,theta:列向量 
# output: 差值平方的和
def J(theta,X_b,y): # 损失函数J的值,
    try:
        return np.sum((y - X_b.dot(theta)) ** 2) / len(X_b)  
    except:
        return float('inf')

def dJ(theta,X_b,y):
    res = np.empty(len(theta)) # 开一个theta大小的
    res[0] = np.sum(X_b.dot(theta) - y) # 先求第一项
    for i in range(1,len(theta)):  # 求其他项
        res[i] = (X_b.dot(theta) - y).dot(X_b[:,i])  # 点乘X_b的第i列
    return res * 2 / len(X_b)
    return X_b.T.dot(X_b.dot(theta) - y) * 2 / len(X_b)

# 梯度下降法
def gradient_decent(X_b,y,initial_theta,eta,n_iters = 1e4,epsilon=1e-8):
    theta = initial_theta
    i_iter = 0
    
    while i_iter < n_iters: # 次数限制
        gradient = dJ(theta,X_b,y)-----------
        last_theta = theta
        theta = theta - eta * gradient
        
        if(abs(J(theta,X_b,y) - J(last_theta,X_b,y)) < epsilon):
            break
        i_iter += 1
    
    return theta
```


      File "<ipython-input-16-b378e850dedb>", line 25
        gradient = dJ(theta,X_b,y)-----------
                                             ^
    SyntaxError: invalid syntax
    



```python
X_train.shape
```


```python
y_train.shape
```


```python
# 单元线性回归中的梯度下降
for i in range(3):
    X_train_i = X_train[:,i]  # 获取测试数据的第i列 
    X_b = np.hstack([np.ones((len(X_train),1)),X_train_i.reshape(-1,1)])  # 加上一列1的列向量
    initial_theta = np.ones(X_b.shape[1]) # X_b的列数长度的initial_theta
    eta = 0.002  # 设定学习率

    theta = gradient_decent(X_b,y_train,initial_theta,eta)
    print(theta)
    print("The slope obtained in this training(截距)： {}".format(theta[0]))  # 输出本次的theta
    print("The intercept in this training(斜率)： {}".format(theta[1]))  # 输出本次的theta
    
    plt.title("Linear Regression:{}".format(i))
    plt.scatter(X_train_i,y_train)
    plt.plot(X_train_i,theta[1] * X_train_i + theta[0],color='r')
    plt.show()
```


```python
# 多元线性回归中的梯度下降
X_b = np.hstack([np.ones((len(X_train),1)),X_train]) 
initial_theta = np.ones(X_b.shape[1])
eta = 0.00004

theta = gradient_decent(X_b,y_train,initial_theta,eta)
print(theta)
```


```python
# 封装成函数
def fit_gradient_descent(X_train,y_train,eta=0.01):
    X_b = np.hstack([np.ones((len(X_train),1)),X_train]) 
    initial_theta = np.ones(X_b.shape[1])

    theta = gradient_decent(X_b,y_train,initial_theta,eta)
    return theta
```

### 问题 4 - 回归模型的优化
在最基础的回归模型上，你使用了什么办法来提升模型的效果，最后模型的性能是否得到了提升？如果提升了，请说出提升性能的原理，如果没有，请探究没有生效的原因。

### 问题 4 - 回答：

#### 多元线性回归中损失函数的斜率计算利用的循环计算，可以简化成矩阵的乘法，加快运算速率：

$\bigtriangledown J(\theta) =  \frac2m\cdot \left\lgroup\begin{matrix} \sum_{i=1}^{m}{({X_b^{(i)\theta - y^{(i)}}) \cdot{X_0^{(i)}} }}  \cr \sum_{i=1}^{m}{({X_b^{(i)\theta - y^{(i)}}) \cdot{X_1^{(i)}} }} \cr \sum_{i=1}^{m}{({X_b^{(i)\theta - y^{(i)}}) \cdot{X_2^{(i)}} }} \cr ... \cr \sum_{i=1}^{m}{({X_b^{(i)\theta - y^{(i)}}) \cdot{X_n^{(i)}} }} \end{matrix}\right\rgroup $ 可化简转换为矩阵的乘法
$ = \frac2m\cdot \left[\begin{matrix} X_b^{(1)}\theta - y^{(1)}, & X_b^{(2)}\theta - y^{(2)}, & X_b^{(3)}\theta - y^{(3)}, & ... & X_b^{(m)}\theta - y^{(m)} \end{matrix}\right] \cdot \left[\begin{matrix} X_0^{(1)} & X_1^{(1)} & X_2^{(1)} & ... & X_n^{(1)} \cr X_0^{(2)} & X_1^{(2)} & X_2^{(2)} & ... & X_n^{(2)} \cr X_0^{(3)} & X_1^{(3)} & X_2^{(3)} & ... & X_n^{(3)}\cr ... & ... & ... & ... & ... \cr X_0^{(m)} & X_1^{(m)} & X_2^{(m)} & ... & X_n{(m)} \end{matrix}\right]$
$ = \frac2m \cdot (X_b\theta - y)^{T} \cdot X_b  = \frac2m \cdot X_b^{T} \cdot (X_b\theta - y)$  


```python
def dJ_no_loops(theta,X_b,y):
    return X_b.T.dot(X_b.dot(theta) - y) * 2 / len(X_b)
# 梯度下降法优化算法
def gradient_decent_improve(X_b,y,initial_theta,eta,n_iters = 1e4,epsilon=1e-8):
    theta = initial_theta
    i_iter = 0
    
    while i_iter < n_iters: # 次数限制
        gradient = dJ_no_loops(theta,X_b,y)
        last_theta = theta
        theta = theta - eta * gradient
        
        if(abs(J(theta,X_b,y) - J(last_theta,X_b,y)) < epsilon):
            break
        i_iter += 1
    
    return theta
def fit_gradient_descent_improve(X_train,y_train,eta=0.01):
    X_b = np.hstack([np.ones((len(X_train),1)),X_train]) 
    initial_theta = np.ones(X_b.shape[1])

    theta = gradient_decent_improve(X_b,y_train,initial_theta,eta)
    return theta
```


```python
%time theta_un = fit_gradient_descent(X_train,y_train,eta=0.00004)
%time theta_improve = fit_gradient_descent_improve(X_train,y_train,eta=0.00004)
print(theta_un)
print(theta_improve)
# 可以看出运算速度是有所提升的
```

### scikit-learn中的线性回归


```python
from sklearn.linear_model import LinearRegression # 加载线性回归
lin_reg = LinearRegression()
lin_reg.fit(X_train,y_train)
```


```python
lin_reg.coef_
```


```python
lin_reg.intercept_
```


```python
lin_reg.score(X_test,y_test)
```

## 第六步. 做出预测
当我们用数据训练出一个模型，它现在就可用于对新的数据进行预测。在决策树回归函数中，模型已经学会对新输入的数据*提问*，并返回对**目标变量**的预测值。你可以用这个预测来获取数据未知目标变量的信息，这些数据必须是不包含在训练数据之内的。

### 问题 5 - 预测销售价格
想像你是一个在波士顿地区的房屋经纪人，并期待使用此模型以帮助你的客户评估他们想出售的房屋。你已经从你的三个客户收集到以下的资讯:

| 特征 | 客戶 1 | 客戶 2 | 客戶 3 |
| :---: | :---: | :---: | :---: |
| 房屋内房间总数 | 5 间房间 | 4 间房间 | 8 间房间 |
| 社区贫困指数（％被认为是贫困阶层） | 17% | 32% | 3% |
| 邻近学校的学生-老师比例 | 15：1 | 22：1 | 12：1 |

*你会建议每位客户的房屋销售的价格为多少？从房屋特征的数值判断，这样的价格合理吗？为什么？* 

**提示：**用你在**分析数据**部分计算出来的统计信息来帮助你证明你的答案。

运行下列的代码区域，使用你的模型来为每位客户的房屋价值做出预测。


```python
# 生成三个客户的数据
client_data = [[5, 17, 15], # 客户 1
               [4, 32, 22], # 客户 2
               [8, 3, 12]]  # 客户 3

# 进行预测
client_data = np.hstack([np.ones((len(client_data),1)),client_data])  #  添加一列全1向量
predicted_price = np.array(client_data).dot(theta)  # 点乘theta得出预测的房价
for i, price in enumerate(predicted_price):
    print("Predicted selling price for Client {}'s home: ${:,.2f}".format(i + 1, price))

```

### 问题 5 - 回答：

合理
- 首先客户3的房屋内房间总数最高，社区贫困指数低，并且邻近学校的学生-老师比例高，因此房屋价格应该是最高的。
- 其次客户2的房屋内房间总数最少，社区贫困指数高，并且临近学校的学生-老师比例较低，因此房屋价格应该是最低的。
- 最后客户1不论是从房间总数、社区贫困指数还是学生-老师比例上看，均是其中的中等水平，因此房屋价格应该处于中等水平。

### 编程练习 5
你刚刚预测了三个客户的房子的售价。在这个练习中，你将用你的最优模型在整个测试数据上进行预测, 并计算相对于目标变量的决定系数 R<sup>2</sup>的值**。


```python
X_b.shape
```


```python
theta.shape
```


```python
#TODO 5

# 提示：你可能需要用到 X_test, y_test, performance_metric
# 提示：你需要使用编程练习 4 中得到参数数值进行预测
# 提示：你可能需要参考问题3的代码来计算R^2的值

r2 = 1
X_b = np.hstack([np.ones((len(X_test),1)),X_test]) 
y_test_fit = X_b.dot(theta)
r2 = performance_metric_no_loops(y_test_fit,y_test)

print("Optimal model has R^2 score {:,.2f} on test data".format(r2))
```

### 问题6 - 分析决定系数

你刚刚计算了最优模型在测试集上的决定系数，你会如何评价这个结果？（你也可以尝试使用你的模型对问题 5 中三个客户的房屋价值进行预测，并与你之前的预测值进行对比）

### 问题6 - 回答

- sklearn中的LinearRegression()最优模型测试的最优的$R^2$值是0.76，当前模型计算出的决定系数为0.74，这个结果相对而言是属于较好的结果。
