import numpy as np
from metrics import accuracy_score
# 没有正规放方程解
class LogisticRegression:

    def __init__(self):
        """"初始化Logistic Regression 模型"""
        self.coef_ = None
        self.interception_= None
        self._theta = None

    def _sigmoid(self,t):
        return 1. / (1. + np.exp(-t))

    def fit(self,X_train,y_train,eta=0.01,n_iters=1e4):
        """根据训练数据集X_train,,y_train,使用梯度下降法训练Logstic Regression模型"""
        assert X_train.shape[0] == y_train.shape[0],\
            "the size of X_train must be equal to the size of y_train"

        def J(theta, X_b, y):
            y_hat = self._sigmoid(X_b.dot(theta))
            try:
                return np.sum(y * np.log(y_hat) + (1 - y) * np.log(1 - y_hat)) / len(y)
            except:
                return float('inf')

        def dJ(theta, X_b, y):
            # res = np.empty(len(theta))
            # res[0] = np.sum(X_b.dot(theta) - y)
            # for i in range(1, len(theta)):
            #     res[i] = (X_b.dot(theta) - y).dot(X_b[:, i])
            # return res * 2 / len(X_b)
            return X_b.T.dot(self._sigmoid(X_b.dot(theta)) - y) * 2 / len(X_b)

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

    def predict_proba(self,X_predict):
        """给定带预测数据集X_predict，返回表示X_predict的结果概率向量"""
        assert self.interception_ is not None and self.coef_ is not None,\
            "must fit before predict!"
        assert X_predict.shape[1] == len(self.coef_),\
            "the feature number of X_predict must be equal to X_train"
        X_b = np.hstack([np.ones((len(X_predict),1)),X_predict])

        # 点乘_theta,再套上一层sigmoid函数
        return self._sigmoid(X_b.dot(self._theta))

    def predict(self,X_predict):
        """给定带预测数据集X_predict，返回表示X_predict的结果向量"""
        assert self.interception_ is not None and self.coef_ is not None,\
            "must fit before predict!"
        assert X_predict.shape[1] == len(self.coef_),\
            "the feature number of X_predict must be equal to X_train"
        X_b = np.hstack([np.ones((len(X_predict),1)),X_predict])

        # 点乘_theta
        proba = self.predict_proba(X_predict)
        return np.array(proba >= 0.5,dtype='int')

    def score(self,X_test,y_test):
        """根据测试数据集X_test 和 y_test确定当前模型的准确度"""

        y_predict = self.predict(X_test)

        return accuracy_score(y_test,y_predict)

    def __repr__(self):
        return "LogisticRegression()"
