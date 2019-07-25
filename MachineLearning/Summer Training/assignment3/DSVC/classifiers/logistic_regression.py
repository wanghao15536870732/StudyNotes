import numpy as np
import matplotlib.pyplot as plt
import random
import math


class LogisticRegression(object):

    def __init__(self):
        self.w = None
        self.theta = None

    def sigmoid(self, x):
        res = 1.0 / (1.0 + np.exp(-x))
        return np.clip(res, 1e-8, 1 - (1e-8))  # 规定最大值和最小值

    def loss(self, X_batch, y_batch):
        """
        Compute the loss function and its derivative.
        Subclasses will override this.
        Inputs:
        - X_batch: A numpy array of shape (N, D) containing a minibatch of N
        data points; each point has dimension D.
        - y_batch: A numpy array of shape (N,) containing labels for the minibatch.
        Returns: A tuple containing:
        - loss as a single float
        - gradient with respect to self.W; an array of the same shape as W
        """

        #########################################################################
        # TODO:                                                                 #
        # calculate the loss and the derivative                                 #
        #########################################################################

        #  计算loss,
        # 这里的w就相当于我们的theta,计算我们sigmoid函数的参数值
        loss = 0
        n = X_batch.dot(self.w)  # 计算 参数 𝜃 ⋅ 𝑥   ,self.w.shape ->  (D,)
        p = self.sigmoid(n)  # 计算sigmoid函数
        m = X_batch.shape[0]  # n求出样本的数量m
        loss = -(y_batch.T.dot(np.log(p)) + (1.0 - y_batch.T).dot(np.log(1.0 - p))) / m

        # 计算loss的导数值
        # gradient an array of the same shape as W
        gradient = np.empty_like(self.w)  # shape  (D,)
        gradient = - (X_batch.T.dot(y_batch - p)) / m  # (D,N)⋅(N,) -> (D,)

        return loss, gradient
        #########################################################################
        #                       END OF YOUR CODE                                #
        #########################################################################

    def train(self, X, y, learning_rate=1e-3, num_iters=100,
              batch_size=200, verbose=True):

        """
        Train this linear classifier using stochastic gradient descent.
        Inputs:
        - X: A numpy array of shape (N, D) containing training data; there are N
         training samples each of dimension D.
        - y: A numpy array of shape (N,) containing training labels;
        - learning_rate: (float) learning rate for optimization.
        - num_iters: (integer) number of steps to take when optimizing
        - batch_size: (integer) number of training examples to use at each step.
        - verbose: (boolean) If true, print progress during optimization.
        Outputs:
        A list containing the value of the loss function at each training iteration.
        """
        num_train, dim = X.shape

        if self.w is None:
            self.w = 0.001 * np.random.randn(dim)

        loss_history = []

        for it in range(num_iters):
            X_batch = None
            y_batch = None

            #########################################################################
            # TODO:                                                                 #
            # Sample batch_size elements from the training data and their           #
            # corresponding labels to use in this round of gradient descent.        #
            # Store the data in X_batch and their corresponding labels in           #
            # y_batch; after sampling X_batch should have shape (batch_size, dim)   #
            # and y_batch should have shape (batch_size,)                           #
            #                                                                       #
            # Hint: Use np.random.choice to generate indices. Sampling with         #
            # replacement is faster than sampling without replacement.              #
            #########################################################################
            array_a = np.arange(num_train)  # 创建一个训练个数大小的数组，即[0,1,2,3,...num_train - 1]
            random_index = np.random.choice(array_a, batch_size)  # 从num_train中随机选出batch_size大小的随机数
            X_batch = X[random_index]
            y_batch = y[random_index]
            #########################################################################
            #                       END OF YOUR CODE                                #
            #########################################################################

            # evaluate loss and gradient
            loss, grad = self.loss(X_batch, y_batch)
            loss_history.append(loss)

            # perform parameter update
            #########################################################################
            # TODO:                                                                 #
            # Update the weights using the gradient and the learning rate.          #
            #########################################################################
            self.w = self.w - learning_rate * grad
            #########################################################################
            #                       END OF YOUR CODE                                #
            #########################################################################

            if verbose and it % 100 == 0:
                print('iteration %d / %d: loss %f' % (it, num_iters, loss))

        return loss_history

    def predict(self, X):
        """
        Use the trained weights of this linear classifier to predict labels for
        data points.
        Inputs:
        - X: N x D array of training data. Each column is a D-dimensional point.
        Returns:
        - y_pred: Predicted labels for the data in X. y_pred is a 1-dimensional
        array of length N, and each element is an integer giving the predicted
        class.
        """
        y_pred = np.zeros(X.shape[0])  # y_pred is a 1-dimensional array of length N
        ###########################################################################
        # TODO:                                                                   #
        # Implement this method. Store the predicted labels in y_pred.            #
        ###########################################################################
        xx = X.dot(self.w)  # (N,D) ⋅ (D,) -> (N,)
        y_pred = self.sigmoid(xx)  # 求出sigmoid函数值
        for i in range(X.shape[0]):
            if y_pred[i] >= 0.50:
                y_pred[i] = 1
            else:
                y_pred[i] = 0

        ###########################################################################
        #                           END OF YOUR CODE                              #
        ###########################################################################
        return y_pred

    def one_vs_all(self, X, y, learning_rate=1e-3, num_iters=100,
                   batch_size=200, verbose=True):
        """
        Train this linear classifier using stochastic gradient descent.
        Inputs:
        - X: A numpy array of shape (N, D) containing training data; there are N
         training samples each of dimension D.
        - y: A numpy array of shape (N,) containing training labels;
        - learning_rate: (float) learning rate for optimization.
        - num_iters: (integer) number of steps to take when optimizing
        - batch_size: (integer) number of training examples to use at each step.
        - verbose: (boolean) If true, print progress during optimization.
        """
        self.theta = np.zeros((X.shape[1],10))

        for it in range(10):
            y_train_it = []  # 保存化为二分类的标签值
            for jt in y:  # 化为二分类，即其中的一类为正类，其余均为负类
                if jt == it:
                    y_train_it.append(1)
                else:
                    y_train_it.append(0)
            self.w = None  # 每次都要求清空
            self.train(X, np.array(y_train_it), learning_rate, num_iters, batch_size, verbose)  # 每次都进行二分类
            self.theta[:,it] = self.w  # 第i列保存第i列的权重

    def on_vs_all_predict(self,X):
        labels = self.sigmoid(X.dot(self.theta))  # 结果是保存着归为每个数字的概率
        y_pred = np.argmax(labels,axis=1)  # 返回每行的最大位置的下标
        return y_pred


