
import cv2
import numpy as np

def move_detect():
    camera = cv2.VideoCapture(0)
    es = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(9,4))  # 构造a=9,b=4的椭圆

    kernel = np.ones((5,5),np.uint8)
    backhround = None

    while True:
        ret,frame = camera.read()
        if backhround is None:
            backhround = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)  # 转为灰度图
            backhround = cv2.GaussianBlur(backhround,(21,21),0)  # 高斯滤波
            continue

        # 对噪声进行平滑处理
        gray_frame = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
        gray_frame = cv2.GaussianBlur(gray_frame, (21, 21), 0)

        diff = cv2.absdiff(backhround,gray_frame)  # 计算背景图与当前图有何区别
        cv2.imshow("diff", diff)
        diff = cv2.threshold(diff,25,255,cv2.THRESH_BINARY)[1]  # 二进制阈值操作
        diff = cv2.dilate(diff,es,iterations=2)  # 膨胀操作
        cv2.imshow("dilate", diff)
        cnts,hierarchy = cv2.findContours(diff.copy(),cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)  # 返回目标的轮廓

        count = 0
        for c in cnts:
            if cv2.contourArea(c) < 1500 or cv2.contourArea(c) > 10000:  # 小面积不计算
                continue
            (x,y,w,h) = cv2.boundingRect(c)  # 计算轮廓的垂直边界最小矩形
            cv2.rectangle(frame,(x,y),(x+w,y+h),(255,255,0),2)
            f = cv2.resize(frame[y:y + h, x:x + w], (200, 200))

            cv2.imwrite('./data/%s.jpg' % str(count), f)
            count += 1
        cv2.imshow("contours",frame)
        if cv2.waitKey(1) == ' ':
            break

    cv2.destroyAllWindows()
    camera.release()

def background_subtractor():
    cap = cv2.VideoCapture(0)
    mog = cv2.createBackgroundSubtractorMOG2()

    while True:
        ret,frame = cap.read()
        fgmask = mog.apply(frame)
        cnts, hierarchy = cv2.findContours(fgmask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)  # 返回目标的轮廓

        count = 0
        for c in cnts:
            if cv2.contourArea(c) < 2000 or cv2.contourArea(c) > 8000:  # 小面积不计算
                continue
            (x, y, w, h) = cv2.boundingRect(c)  # 计算轮廓的垂直边界最小矩形
            cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 255, 0), 2)
            f = cv2.resize(frame[y:y + h, x:x + w], (200, 200))

            cv2.imwrite('./data/%s.jpg' % str(count), f)
            count += 1
        cv2.imshow("contours", frame)
        cv2.imshow("fgmask", fgmask)

        if cv2.waitKey(1) == ' ':
            break
    cap.release()
    cv2.destroyAllWindows()

def background_subtractor_knn():
    camera = cv2.VideoCapture("D:\\Google\\src.mp4")
    bs = cv2.createBackgroundSubtractorKNN(detectShadows=True)

    while True:
        ret,frame = camera.read()
        if ret is False:
            break
        fgmask = bs.apply(frame)  # 获取前景掩码
        th = cv2.threshold(fgmask.copy(),244,255,cv2.THRESH_BINARY)[1]  # 将非纯白色的像素都设为0
        dilated = cv2.dilate(th,cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(3,3)),iterations=3)

        cnts, hierarchy = cv2.findContours(dilated, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)  # 返回目标的轮廓

        for c in cnts:
            if cv2.contourArea(c) < 100:
                continue
            (x, y, w, h) = cv2.boundingRect(c)  # 计算轮廓的垂直边界最小矩形
            cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 255, 0), 2)
        cv2.imshow("mog",fgmask)
        cv2.imshow("thresh",th)
        cv2.imshow("detection",frame)
        if cv2.waitKey(500) == ' ':
            break
    camera.release()
    cv2.destroyAllWindows()

def target_follow():
    camera = cv2.VideoCapture(0)
    ret,frame = camera.read()
    r,h,c,w = 10,200,10,200
    track_window = (c,r,w,h)

    roi = frame[r:r+h,c:c+w]  # 首先定义好感兴趣的区域
    hsv_roi = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)

    mask = cv2.inRange(hsv_roi,np.array((100,30,32)),
                       np.array((180,120,225)))

    roi_hist = cv2.calcHist([hsv_roi],[0],mask,[180],[0,180]) # 获取感兴趣区域的直方图

    term_crit = (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT,10,1)

    while True:
        ret ,frame = camera.read()

        if ret == True:
            hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
            dst = cv2.calcBackProject([hsv],[0],roi_hist,[0,180],1)

            ret,track_window = cv2.meanShift(dst,track_window,term_crit)

            x,y,w,h = track_window
            img2 = cv2.rectangle(frame,(x,y),(x+w,y+h),255,2)
            cv2.imshow('img2',img2)

            k = cv2.waitKey(1) & 0xff
            if k == 27:
                break
        else:
            break
    camera.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    # move_detect()
    background_subtractor()

    # knn移动目标检测
    # background_subtractor_knn()

    # target_follow()
