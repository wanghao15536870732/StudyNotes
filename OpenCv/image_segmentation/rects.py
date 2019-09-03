import numpy as np
import cv2
from cv2 import utils


def copyRect(src, dst, srcRect, dstRect, mask=None, interpolation=cv2.INTER_LINEAR):

    x0, y0, w0, h0 = srcRect
    x1, y1, w1, h1 = dstRect

    if mask is None:
        dst[y1:y1 + h1, x1:x1 + w1] = \
            cv2.resize(src[y0:y0 + h0, x0:x0 + w0], (w1, h1), interpolation=interpolation)
    else:
        if not utils.isGray(src):
            mask = mask.repeat(3).reshape(h0, w0, 3)
        dst[y1:y1 + h1, x1:x1 + w1] = np.where(cv2.resize(mask, (w1, h1),
                                                          interpolation=cv2.INTER_NEAREST),
                                               cv2.resize(src[y0:y0 + h0, x0:x0 + w0], (w1, h1),
                                                          interpolation=interpolation),
                                               dst[y1:y1 + h1, x1:x1 + w1])
