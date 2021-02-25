# *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

pass

# *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
from .layers import *
from .fast_layers import *


def affine_relu_forward(x, w, b):
    """
    Convenience layer that perorms an affine transform followed by a ReLU

    Inputs:
    - x: Input to the affine layer
    - w, b: Weights for the affine layer

    Returns a tuple of:
    - out: Output from the ReLU
    - cache: Object to give to the backward pass
    """
    a, fc_cache = affine_forward(x, w, b)
    out, relu_cache = relu_forward(a)
    cache = (fc_cache, relu_cache)
    return out, cache


def affine_relu_backward(dout, cache):
    """
    Backward pass for the affine-relu convenience layer
    """
    fc_cache, relu_cache = cache
    da = relu_backward(dout, relu_cache)
    dx, dw, db = affine_backward(da, fc_cache)
    return dx, dw, db


def affine_batchnorm_relu_forward(x, W, b, gamma, beta, bn_params):
    """
        Convenience layer that performs an affine transform, batch normalization,
        and ReLU.
        Inputs:
        - x: Array of shape (N, D1); input to the affine layer
        - w, b: Arrays of shape (D2, D2) and (D2,) giving the weight and bias for
          the affine transform.
        - gamma, beta: Arrays of shape (D2,) and (D2,) giving scale and shift
          parameters for batch normalization.
        - bn_param: Dictionary of parameters for batch normalization.
        Returns:
        - out: Output from ReLU, of shape (N, D2)
        - cache: Object to give to the backward pass.
    """
    # affine
    x, cache_affine = affine_forward(x, W, b)
    # batchnorm
    x, cache_batch = batchnorm_forward(x, gamma, beta, bn_params)
    # relu
    x, cache_relu = relu_forward(x)
    return x, (cache_affine, cache_batch, cache_relu)


def affine_batchnorm_relu_backward(dout, cache):
    cache_affine, cache_batch, cache_relu = cache
    # relu
    dx = relu_backward(dout, cache_relu)
    dx, dgamma, dbeta = batchnorm_backward(dx, cache_batch)
    dx, dw, db = affine_backward(dx, cache_affine)
    return dx, dw, db, dgamma, dbeta


def affine_layernorm_relu_forward(x, W, b, gamma, beta, ln_params):
    # affine
    x, cache_affine = affine_forward(x, W, b)
    # batchnorm
    x, cache_layer = layernorm_forward(x, gamma, beta, ln_params)
    # relu
    x, cache_relu = relu_forward(x)
    return x, (cache_affine, cache_layer, cache_relu)


def affine_layernorm_relu_backward(dout, cache):
    cache_affine, cache_layer, cache_relu = cache
    # relu
    dx = relu_backward(dout, cache_relu)
    dx, dgamma, dbeta = layernorm_backward(dx, cache_layer)
    dx, dw, db = affine_backward(dx, cache_affine)
    return dx, dw, db, dgamma, dbeta


def conv_relu_forward(x, w, b, conv_param):
    """
    A convenience layer that performs a convolution followed by a ReLU.

    Inputs:
    - x: Input to the convolutional layer
    - w, b, conv_param: Weights and parameters for the convolutional layer

    Returns a tuple of:
    - out: Output from the ReLU
    - cache: Object to give to the backward pass
    """
    a, conv_cache = conv_forward_fast(x, w, b, conv_param)
    out, relu_cache = relu_forward(a)
    cache = (conv_cache, relu_cache)
    return out, cache


def conv_relu_backward(dout, cache):
    """
    Backward pass for the conv-relu convenience layer.
    """
    conv_cache, relu_cache = cache
    da = relu_backward(dout, relu_cache)
    dx, dw, db = conv_backward_fast(da, conv_cache)
    return dx, dw, db


def conv_bn_relu_forward(x, w, b, gamma, beta, conv_param, bn_param):
    a, conv_cache = conv_forward_fast(x, w, b, conv_param)
    an, bn_cache = spatial_batchnorm_forward(a, gamma, beta, bn_param)
    out, relu_cache = relu_forward(an)
    cache = (conv_cache, bn_cache, relu_cache)
    return out, cache


def conv_bn_relu_backward(dout, cache):
    conv_cache, bn_cache, relu_cache = cache
    dan = relu_backward(dout, relu_cache)
    da, dgamma, dbeta = spatial_batchnorm_backward(dan, bn_cache)
    dx, dw, db = conv_backward_fast(da, conv_cache)
    return dx, dw, db, dgamma, dbeta


def conv_relu_pool_forward(x, w, b, conv_param, pool_param):
    """
    Convenience layer that performs a convolution, a ReLU, and a pool.

    Inputs:
    - x: Input to the convolutional layer
    - w, b, conv_param: Weights and parameters for the convolutional layer
    - pool_param: Parameters for the pooling layer

    Returns a tuple of:
    - out: Output from the pooling layer
    - cache: Object to give to the backward pass
    """
    a, conv_cache = conv_forward_fast(x, w, b, conv_param)
    s, relu_cache = relu_forward(a)
    out, pool_cache = max_pool_forward_fast(s, pool_param)
    cache = (conv_cache, relu_cache, pool_cache)
    return out, cache


def conv_relu_pool_backward(dout, cache):
    """
    Backward pass for the conv-relu-pool convenience layer
    """
    conv_cache, relu_cache, pool_cache = cache
    ds = max_pool_backward_fast(dout, pool_cache)
    da = relu_backward(ds, relu_cache)
    dx, dw, db = conv_backward_fast(da, conv_cache)
    return dx, dw, db
