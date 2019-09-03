import numpy as np
from math import sqrt

def accuracy_score(y_true,y_predict):
    """计算y_true和y_predict之间的准确率"""
    assert y_true.shape[0] == y_predict.shape[0],\
        "the size of y_true must be equal to the size of y_predict"
    return sum(y_true == y_predict) / len(y_true)

def mean_squared_error(y_true,y_predict):
    """计算y_true和y_predict之间的额MSE"""
    assert len(y_true) == len(y_predict),\
        "the size of y_true must be equal to the size of y_predict"
    # 平方之和
    return np.sum((y_true - y_predict) ** 2) / len(y_true)

def root_mean_squared_error(y_true,y_predict):
    """计算y_true和y_predict之间的RMSE"""
    # 平方之和求平方根
    return sqrt(mean_squared_error(y_true,y_predict))

def mean_absolute_error(y_true,y_predict):
    """计算y_true和y_predict之间的额MAE"""
    assert len(y_true) == len(y_predict),\
        "the size of y_true must be equal to the size of y_predict"
    # 绝对值之和
    return np.sum(np.absolute(y_true - y_predict)) / len(y_true)

def r2_score(y_true,y_predict):
    """计算y_true和y_predict之间的R Square"""

    return 1 - mean_squared_error(y_true,y_predict) / np.var(y_true)
