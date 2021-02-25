from builtins import range
import numpy as np
from random import shuffle
from past.builtins import xrange


def svm_loss_naive(W, X, y, reg):
    """
    Structured SVM loss function, naive implementation (with loops).

    Inputs have dimension D, there are C classes, and we operate on minibatches
    of N examples.

    Inputs:
    - W: A numpy array of shape (D, C) containing weights.
    - X: A numpy array of shape (N, D) containing a minibatch of data.
    - y: A numpy array of shape (N,) containing training labels; y[i] = c means
      that X[i] has label c, where 0 <= c < C.
    - reg: (float) regularization strength

    Returns a tuple of:
    - loss as single float
    - gradient with respect to weights W; an array of same shape as W
    """
    dW = np.zeros(W.shape)  # initialize the gradient as zero

    # compute the loss and the gradient
    num_classes = W.shape[1]
    num_train = X.shape[0]
    loss = 0.0
    for i in range(num_train):
        scores = X[i].dot(W)  # (,D)⋅(D,C) -> (,C)
        correct_class_score = scores[y[i]]  # 取出下标为y[i]的值
        for j in range(num_classes):
            if j == y[i]:  # 相当于margin[:,y[i]] = 0.0
                continue
            margin = scores[j] - correct_class_score + 1  # note delta = 1
            if margin > 0:
                loss += margin
                dW[:, y[i]] += -X[i].T
                dW[:, j] += X[i].T

    # Right now the loss is a sum over all training examples, but we want it
    # to be an average instead so we divide by num_train.
    loss /= num_train
    dW /= num_train

    # Add regularization to the loss.
    loss += reg * np.sum(W * W)
    # Add regularization to the gradient.
    dW += 2 * reg * W # reg * np.sum(W * W)的导数

    #############################################################################
    # TODO:                                                                     #
    # Compute the gradient of the loss function and store it dW.                #
    # Rather than first computing the loss and then computing the derivative,   #
    # it may be simpler to compute the derivative at the same time that the     #
    # loss is being computed. As a result you may need to modify some of the    #
    # code above to compute the gradient.                                       #
    #############################################################################

    return loss, dW


def svm_loss_vectorized(W, X, y, reg):
    """
    Structured SVM loss function, vectorized implementation.

    Inputs and outputs are the same as svm_loss_naive.
    """
    loss = 0.0
    dW = np.zeros(W.shape)  # initialize the gradient as zero

    #############################################################################
    # TODO:                                                                     #
    # Implement a vectorized version of the structured SVM loss, storing the    #
    # result in loss.                                                           #
    #############################################################################
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    num_classes = W.shape[1]  # D
    num_train = X.shape[0]  # N
    scores = X.dot(W)  # (N,D) (D,C) -> (N,C)

    correct_class_score = scores[np.arange(num_train), y]  # 每行取出与y向量对应的下标值 (,N)
    correct_class_score = np.reshape(correct_class_score, (num_train, 1))
    margin_vectorized = scores - correct_class_score + 1.0  # 自动转为列向量相减  (N,C)

    margin_vectorized[margin_vectorized <= 0] = 0.0  # max() = 0 ,赋值0
    margin_vectorized[np.arange(num_train), y] = 0.0  # 剔除j = y[i]的情况

    loss += np.sum(margin_vectorized) / num_train
    loss += reg * np.sum(W * W)

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    #############################################################################
    # TODO:                                                                     #
    # Implement a vectorized version of the gradient for the structured SVM     #
    # loss, storing the result in dW.                                           #
    #                                                                           #
    # Hint: Instead of computing the gradient from scratch, it may be easier    #
    # to reuse some of the intermediate values that you used to compute the     #
    # loss.                                                                     #
    #############################################################################
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # 既然dW的求法是在一个零矩阵上加上对应的Xi（j<>yi），或者
    # 减去若干个 Xi（j == yi),那么我们可以复用 margins 并通过计算其与X的积来得到最终结果

    margin_vectorized[margin_vectorized > 0] = 1.0  # 通过示性函数保留 > 0 的位置
    margin_vectorized_n = - np.sum(margin_vectorized, axis=1)  # j = yi位置应该减去的Xi个数
    margin_vectorized[np.arange(num_train), y] = margin_vectorized_n  # 计算处每个位置上，最终会叠加几倍的X[i]
    dW += X.T.dot(margin_vectorized) / num_train
    dW += 2 * reg * W  # 加上最后的导数值

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return loss, dW
