import numpy as np
from metrics import r2_score

class LinearRegression:

    def __init__(self):
        """"初始化Linear Regression 模型"""
        self.coef_ = None
        self.interception_= None
        self._theta = None

    def fit_normal(self,X_train,y_train):
        """根据训练数据集X_train,y_train训练Linear Regression模型"""
        assert X_train.shape[0] == y_train.shape[0],\
            "the size of X_train must be equal to the size of y_train"

        # 横向上的添加
        X_b = np.hstack([np.ones((len(X_train),1)),X_train])
        self._theta = np.linalg.inv(X_b.T.dot(X_b)).dot(X_b.T).dot(y_train)

        self.interception_ = self._theta[0]

        self.coef_ = self._theta[1:]

        return self

    def fit_gd(self,X_train,y_train,eta=0.01,n_iters=1e4):
        """根据训练书记X_train,,y_train,使用梯度下降法训练Linear Regression模型"""
        assert X_train.shape[0]== y_train.shape[0],\
            "the size of X_train must be equal to the size of y_train"

        def J(theta, X_b, y):
            try:
                return np.sum((y - X_b.dot(theta)) ** 2) / len(X_b)
            except:
                return float('inf')

        def dJ(theta, X_b, y):
            # res = np.empty(len(theta))
            # res[0] = np.sum(X_b.dot(theta) - y)
            # for i in range(1, len(theta)):
            #     res[i] = (X_b.dot(theta) - y).dot(X_b[:, i])
            # return res * 2 / len(X_b)
            return X_b.T.dot(X_b.dot(theta) - y) * 2 / len(X_b)

        def gradient_decent(X_b, y, initial_theta, eta, n_iters=1e4, epsilon=1e-8):
            theta = initial_theta
            cur_iter = 0

            while cur_iter < n_iters:
                gradient = dJ(theta, X_b, y)
                last_theta = theta
                theta = theta - eta * gradient

                if (abs(J(theta, X_b, y) - J(last_theta, X_b, y)) < epsilon):
                    break
                cur_iter += 1

            return theta

        X_b = np.hstack([np.ones((len(X_train), 1)), X_train])
        initial_theta = np.ones(X_b.shape[1])
        self._theta = gradient_decent(X_b,y_train,initial_theta,eta,n_iters)

        self.interception_ = self._theta[0]
        self.coef_ = self._theta[1:]

        return self

    def fit_sgd(self,X_train,y_train,n_iters=5,t0=5,t1=50):
        """根据训练数据集X_train,y_train,使用梯度下降法训练Linear Regression 模型"""
        assert X_train.shape[0] == y_train.shape[0],\
            "the size of X_train must be equal to the size of y_train"
        assert n_iters >= 1,\
            "the number of traversals is at least 1"

        def dJ_sgd(theta,X_b_i,y_i): #  计算当前梯度
            return X_b_i.T.dot(X_b_i.dot(theta) - y_i)

        def sgd(X_b,y_i,initial_theta,n_iters,t0=5,t1=50):

            def learning_rate(t):
                return t0 / (t + t1)

            theta = initial_theta
            m = len(X_b)

            for cur_iter in range(n_iters): # 遍历整个数据的次数
                indexes = np.random.permutation(m)  # 成成新的随机索引
                X_b_new = X_b[indexes] # 保存新的随即数据
                y_new = y_i[indexes]
                for i in range(m): # 遍历整个数据
                    # rand_i = np.random.randint(m) # 生成随机数
                    gradient = dJ_sgd(theta,X_b_new[i],y_new[i]) # 计算梯度
                    theta = theta - learning_rate(cur_iter * m + i) * gradient # 计算新的theta

            return theta

        X_b = np.hstack([np.ones((len(X_train), 1)), X_train])
        initial_theta = np.zeros(X_b.shape[1])  # 初始化全0向量
        self._theta = sgd(X_b, y_train, initial_theta, n_iters,t0,t1)

        self.interception_ = self._theta[0] # 斜率
        self.coef_  =self._theta[1:] # 截距
        return self

    def predict(self,X_predict):
        assert self.interception_ is not None and self.coef_ is not None,\
            "must fit before predict!"
        assert X_predict.shape[1] == len(self.coef_),\
            "the feature number of X_predict must be equal to X_train"
        X_b = np.hstack([np.ones((len(X_predict),1)),X_predict])

        # 点乘_theta
        return X_b.dot(self._theta)

    def score(self,X_test,y_test):
        """根据测试数据集X_test 和 y_test确定当前模型的准确度"""

        y_predict = self.predict(X_test)

        return r2_score(y_test,y_predict)

    def __repr__(self):
        return "LinearRegression()"
