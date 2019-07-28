import numpy

def createMedianMask(disparityMap,validDepthMask,rect = None):
    if rect is not None:
        x,y,w,h = rect
        disparityMap = disparityMap[y:y+h,x:x+w]  # 将图像分割出来
    median = numpy.median(disparityMap)  # 得到中值
    # validDepthMask == 0 或者 abs(disparityMap - median) < 12 的时候返回1.0
    # 最终将图像分为1，0 掩模
    return numpy.where((validDepthMask == 0) | (abs(disparityMap - median) < 12),1.0,0.0)