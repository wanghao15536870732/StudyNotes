import pickle as pickle
import numpy as np
import os
from scipy.misc import imread

def load_CIFAR_batch(filename):
    """load single batch of cifar"""
    with open(filename,'rb') as f:
        datadict = pickle.load(f,encoding='iso-8859-1')
        X = datadict['data']
        Y = datadict['labels']
        X = X.reshape(10000,3,32,32).transpose(0,2,3,1).astype('float')
        Y = np.array(Y)
        return X,Y

def load_CIFAR10(ROOT,num):
    """load all of cifar"""
    xs = []
    ys = []
    for b in range(1,num):
        f = os.path.join(ROOT,'data_batch_%d' % (b,))
        X,Y = load_CIFAR_batch(f)
        xs.append(X)
        ys.append(Y)
    Xtr = np.concatenate(xs)  # 对数据进行拼接
    Ytr = np.concatenate(ys)
    del X,Y  # 删除之前的数据
    Xte,Yte = load_CIFAR_batch(os.path.join(ROOT,'test_batch'))
    return Xtr,Ytr,Xte,Yte


def load_models(models_dir):
    models = {}
    for model_file in os.listdir(models_dir):
        with open(os.path.join(models_dir,model_file),'rb') as f:
            try:
                models[model_file] = pickle.load(f)['model']
            except pickle.UnpicklingError:
                continue
    return models
