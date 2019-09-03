import cv2
from scipy import ndimage
import numpy as np

kernel_3x3 = np.array([[-1,-1,-1],
                       [-1,8,-1],
                       [-1,-1,-1]])

kernel_5x5 = np.array([[-1,-1,-1,-1,-1],
                       [-1,1,2,1,-1],
                       [-1,2,4,2,-1],
                       [-1,1,2,1,-1],
                       [-1,-1,-1,-1,-1]])

def gaussian_blur(path):
    img = cv2.imread(path,0)  # 转为灰度图格式

    k3 = ndimage.convolve(img,kernel_3x3)
    k5 = ndimage.convolve(img,kernel_5x5)

    blurred = cv2.GaussianBlur(img,(11,11),0)
    g_hpf = img - blurred

    cv2.imshow("3x3",k3)
    cv2.imshow("5x5",k5)
    cv2.imshow("g_hpf",g_hpf)
    cv2.imshow("blurred",blurred)

    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == '__main__':
    path = 'D:\\Desktop\\lena.jpg'
    gaussian_blur(path)

