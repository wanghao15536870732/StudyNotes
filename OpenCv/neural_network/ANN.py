import numpy as np
import cv2

def ann_mlp_create():
    ann = cv2.ml.ANN_MLP_create()
    ann.setLayerSizes(np.array([9,5,9],dtype=np.uint8))
    ann.setTrainMethod(cv2.ml.ANN_MLP_BACKPROP)

    ann.train(np.array())


