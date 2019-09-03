import numpy as np
from math import sqrt
from collections import Counter
from metrics import accuracy_score

def train_test_split(X,y,test_ratio=0.2,seed=None):
    """"将数据X和y按照text_ratio分割成X_train,X_test,y_train,y_test"""

    assert X.shape[0]== y.shape[0],\
        "the size of X must be equal to the size of y"
    assert 0.0 <= test_ratio <= 1.0,\
        "test_ration must be valid"

    if seed:
        np.random.seed(seed)
    shuffled_indexes = np.random.permutation(len(X))

    test_size = int(len(X) * test_ratio)
    test_indexed = shuffled_indexes[:test_size]
    train_indexes = shuffled_indexes[test_size:]

    X_train = X[train_indexes]
    y_train = y[train_indexes]

    X_test = X[test_indexed]
    y_test = y[test_indexed]
    return X_train,y_train,X_test,y_test

def kNN_classify(k,X_train,y_train,x):

    assert 1 <= k <= X_train.shape[0],"K must be valid"
    assert X_train.shape[0] == y_train.shape[0],\
        "the size of X_train must be equal to the size of y_train"
    assert X_train.shape[1] == x.shape[0],\
        "the feature number of x must be equal to X_train"
    distance = []
    for x_train in X_train: # 遍历整个X_train
        d = sqrt(np.sum((x_train - x) ** 2))
        distance.append(d)

    nearest = np.argsort(distance)  # 从小到大排序,并返回索引值

    topKey = [y_train[i] for i in nearest[:k]]  # 取出索引值对应的数字

    votes = Counter(topKey)  # 计算每个数对应出现的次数

    return votes.most_common(1)[0][0]  # 返回出现次数最多的数值


class KNNClassifier:

    def __init__(self,k):
        """初始化kNN分类器"""
        assert k >= 1,"k must be valid"
        self.k = k
        self._X_train = None
        self._y_train = None
    def fit(self,X_train,y_train):
        """"根据训练数据集X_train和y_train训练kNN分类器"""
        assert X_train.shape[0] == y_train.shape[0],\
            "the size of X_train must be equal to the size of y_train"
        assert self.k <= X_train.shape[0],\
            "the size of X_train must at least k."
        self._X_train = X_train
        self._y_train = y_train
        return self

    def predit(self,X_predict):
        assert self._X_train is not None and self._y_train is not None,\
            "must fit before predict!"
        assert X_predict.shape[1] == self._X_train.shape[1],\
            "the feature number of X_predict must be equal to X_train"

        y_predict = [self._predict(x) for x in X_predict]
        return np.array(y_predict)

    def _predict(self,x):
        """给定单个带预测数据x,返回X_predict 的预测结果值"""
        assert x.shape[0] == self._X_train.shape[1],\
            """the feature number of x must be equal to X_train"""
        # kNN的具体算法
        distance = [sqrt(np.sum((x_train - x) ** 2))
                    for x_train in self._X_train]
        nearest = np.argsort(distance)

        topK_y = [self._y_train[i] for i in nearest[:self.k]]

        votes = Counter(topK_y)

        return votes.most_common(1)[0][0]
    def score(self,X_test,y_test): # 参数为test 的值跟真值的
        """根据"测试数据集X_test和y_test确定当前模型的准确度"""
        y_predict = self.predit(X_test)
        return accuracy_score(y_test,y_predict)

if __name__ == '__main__':
    raw_data_X = [[3.393533211, 2.331273381],
                  [3.110073483, 1.781539638],
                  [1.343808831, 3.368360954],
                  [3.582294042, 4.679179110],
                  [2.280362439, 2.866990263],
                  [7.423436942, 4.696522875],
                  [5.745051997, 3.533989803],
                  [9.172168622, 2.511101045],
                  [7.792783481, 3.424088941],
                  [7.939820817, 0.791637231]
                  ]
    raw_data_y = [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]

    X_train = np.array(raw_data_X)
    y_train = np.array(raw_data_y)

    x = np.array([5.093607318, 3.365731514])
    X_predict = x.reshape(1, -1)

    ''' 
    x = np.array([5.093607318, 3.365731514])
    predict_y = kNN_classify(6,X_train,y_train,x)
    print(predict_y)
    '''

    knn_clf = KNNClassifier(k=6)

    knn_clf.fit(X_train,y_train)

    y_predict = knn_clf.predit(X_predict)

    print(y_predict)

    print(y_predict[0])