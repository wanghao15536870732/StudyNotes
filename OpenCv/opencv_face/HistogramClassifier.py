import cv2
from cv2 import face
import sys
import numpy as np

face_cascade = cv2.CascadeClassifier('./cascades/haarcascade_frontalface_default.xml')
smile_cascade = cv2.CascadeClassifier('./cascades/haarcascade_smile.xml')
eye_cascade = cv2.CascadeClassifier('./cascades/haarcascade_eye.xml')


# 静态人脸检测
def detect(filename):
    img = cv2.imread(filename)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  # 人脸检测需要灰度图像
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    for (x, y, w, h) in faces:
        img = cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 0), 2)
    cv2.namedWindow("Face Detected!!")
    cv2.imshow('Face Detected!!', img)
    cv2.imwrite('./face.jpg', img)
    cv2.waitKey(0)


# 静态人脸检测 & 图片裁剪
def detect(filename):
    for dirname, dirnames, filenames in cv2.os.walk(filename):
        for name in filenames:
            subject_path = cv2.os.path.join(filename, name)
            print(subject_path)
            count = 0
            img = cv2.imread(subject_path)
            gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  # 人脸检测需要灰度图像
            faces = face_cascade.detectMultiScale(gray, 1.3, 5)
            for (x, y, w, h) in faces:
                img = cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 0), 2)
                f = cv2.resize(gray[y:y + h, x:x + w], (200, 200))
                cv2.imwrite('./data/houyue/%s.jpg' % str(count), f)
                count += 1


# 视频人脸识别
def detect_video():
    camera = cv2.VideoCapture(0)
    while (True):
        ret, frame = camera.read()
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)  # 人脸检测需要灰度图像
        faces = face_cascade.detectMultiScale(gray, 1.3, 5)
        for (x, y, w, h) in faces:
            img = cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
            roi_gray = gray[y:y + h, x:x + w]
            eyes = eye_cascade.detectMultiScale(roi_gray, 1.03, 5, 0, (40, 40))
            for (ex, ey, ew, eh) in eyes:
                cv2.rectangle(img, (ex, ey), (ex + ew, ey + eh), (0, 255, 0), 2)
        cv2.imshow("camera", frame)
        if cv2.waitKey(1000) & 0xff == ord("q"):
            break


# 人脸裁剪分割
def generate():
    camera = cv2.VideoCapture(0)
    count = 0
    while True:
        ret, frame = camera.read()
        # if frame is None:
        #     break
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        faces = face_cascade.detectMultiScale(gray, 1.1, 5)

        for (x, y, w, h) in faces:
            cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)

            f = cv2.resize(gray[y:y + h, x:x + w], (200, 200))

            cv2.imwrite('./data/wanghao/%s.jpg' % str(count), f)

            count += 1
        cv2.imshow("camera", frame)
        if cv2.waitKey(1000) & 0xff == ord("q"):
            break
    camera.release()
    cv2.destroyAllWindows()


def read_images(path, sz=None):
    c = 0
    X, y = [], []
    for dirname, dirnames, filenames in cv2.os.walk(path):  # 返回根目录、文件夹列表、文件夹以外的文件
        for subdirname in dirnames:  # 遍历文件夹列表
            subject_path = cv2.os.path.join(dirname, subdirname)  # 加上内层文件路径

            for filename in cv2.os.listdir(subject_path):  # 再遍历内层文件
                try:
                    if (filename == ".directory"):
                        continue
                    filepath = cv2.os.path.join(subject_path, filename)
                    im = cv2.imread(cv2.os.path.join(subject_path, filename), cv2.IMREAD_GRAYSCALE)

                    if (sz is not None):
                        im = cv2.resize(im, (200, 200))
                    X.append(np.asarray(im, dtype=np.uint8))
                    y.append(c)

                except IOError:
                    print("I/O error({0}):{1}".format(IOError.errno, IOError.strerror))

                except:
                    print("Unexpected error:", sys.exc_info()[0])
                    raise

            c = c + 1
    return [X, y]


def face_rec(path, out_dir):
    count = 0
    names = ['houyue', 'wanghao']
    [X, y] = read_images(path)
    y = np.asarray(y, dtype=np.int32)

    model = face.EigenFaceRecognizer_create()

    model.train(np.asarray(X), np.asarray(y))
    camera = cv2.VideoCapture(0)

    while True:
        read, img = camera.read()
        faces = face_cascade.detectMultiScale(img, 1.1, 5)

        for (x, y, w, h) in faces:
            cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 0), 2)
            gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
            roi = gray[x:x + w, y:y + h]

            try:
                roi = cv2.resize(roi, (200, 200), interpolation=cv2.INTER_LINEAR)
                params = model.predict(roi)

                print("Label:%s,Confidence:%.2f" % (names[params[0]], params[1]))
                cv2.putText(img, names[params[0]], (x, y - 20),
                            cv2.FONT_HERSHEY_SIMPLEX, 1, 255, 2)
            except:
                continue
        cv2.imshow('camera', img)
        cv2.imwrite(out_dir + '/%s.jpg' % str(count), img)
        if cv2.waitKey(1000) & 0xff == ord("q"):
            break
        count += 1
    cv2.destroyAllWindows()


def face_rec_img(path, filename):
    names = ['houyue', 'wanghao']
    [X, y] = read_images(path)
    y = np.asarray(y, dtype=np.int32)

    model = face.EigenFaceRecognizer_create()

    model.train(np.asarray(X), np.asarray(y))

    for dirname, dirnames, filenames in cv2.os.walk(filename):
        for name in filenames:
            subject_path = cv2.os.path.join(filename, name)
            img = cv2.imread(subject_path)
            faces = face_cascade.detectMultiScale(img, 1.1, 5)

            for (x, y, w, h) in faces:
                cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 0), 2)
                gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
                roi = gray[x:x + w, y:y + h]

                try:
                    roi = cv2.resize(roi, (200, 200), interpolation=cv2.INTER_LINEAR)
                    params = model.predict(roi)

                    print("Label:%s,Confidence:%.2f" % (names[params[0]], params[1]))
                    cv2.putText(img, names[params[0]], (x, y - 20),
                                cv2.FONT_HERSHEY_SIMPLEX, 1, 255, 2)
                except:
                    continue
            cv2.imwrite(subject_path, img)
    cv2.destroyAllWindows()


# 显示图片，跟训练数据集
def show_pic(path):
    [X, y] = read_images(path)
    for i in range(len(X)):
        cv2.imshow("1", X[i])
        cv2.waitKey(100)
    print([X, y])


if __name__ == '__main__':
    train_path = './data'
    predict_path = './result'
    local_img_path = 'D:\\Desktop\\picture\\img'

    # 本地批量图片人脸裁剪
    # detect(local_img_path)

    # 摄像头动态人脸检测
    # detect_video()

    # 摄像头人脸裁剪保存到本地
    # generate()

    # 显示训练数据集
    # show_pic(train_path)

    # 训练人脸识别,,通过摄像头进行预测
    face_rec(train_path,predict_path)

    # 本地图片识别
    # face_rec_img('./data',local_img_path)
