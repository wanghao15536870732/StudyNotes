import numpy as np

class StandardScaler:

    def __init__(self):
        self.mean_ = None
        self.scale_ = None

    def fir(self,X):
        """根据训练数据集X获取数据的均值跟方差"""
        assert  X.ndim == 2,"The dimension of X must be 2"

        self.mean_ = np.array([np.mean((X[:,i]) for i in range(X.shape[1]))])
        self.scale_ = np.array([np.std((X[:,i]) for i in range(X.shape[1]))])

        return self

    def transfrom(self,X):
        """根据训练数据集X获取数据的均值跟方差"""
        assert X.ndim == 2, "The dimension of X must be 2"
        assert self.mean_ is not None and self.scale_ is not None,\
            "must fit before transform!"
        assert X.shape[1] == len(self.mean_),\
            "the feature number of X must be equal to mean_ and std_"

        resX= np.empty(shape=X.shape,dtype=float)

        # 循环进行均值归一化
        for col in range(X.shape[1]):
            resX[:,col] = (X[:,col] - self.mean_[col]) / self.scale_[col]

        return resX