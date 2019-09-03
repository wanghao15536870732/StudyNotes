import cv2
import _pickle as cPickle
import numpy as np
import gzip

def load_data():
    mnist = gzip.open('./data/mnist.pkl.gz','rb')
    train_data,classification_data,test_data = cPickle.load(mnist,encoding='bytes')
    mnist.close()
    return (train_data,classification_data,test_data)

def vectorized_result(j):
    e = np.zeros((10,1))
    e[j] = 1.0
    return e

def wrap_data():
    tr_d,va_d,te_d = load_data()
    training_inputs = [np.reshape(x,(784,1)) for x in tr_d[0]]
    training_results = [vectorized_result(y) for y in tr_d[1]]
    training_data = zip(training_inputs,training_results) # 打包为对应训练集

    validation_inputs = [np.reshape(x,(784,1)) for x in va_d[0]]
    validation_data = zip(validation_inputs,va_d[1])

    test_inputs = [np.reshape(x,(784,1)) for x in te_d[0]]
    test_data = zip(test_inputs,te_d[1])

    return (training_data,validation_data,test_data)

def create_ANN(hidden = 20):
    ann = cv2.ml.ANN_MLP_create()
    ann.setLayerSizes(np.array([784,hidden,10]))
    ann.setTrainMethod(cv2.ml.ANN_MLP_RPROP)
    ann.setActivationFunction(cv2.ml.ANN_MLP_SIGMOID_SYM) # 设置函数为sigmoid函数
    ann.setTermCriteria((cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT,20,1))
    return ann

def train(ann,samples = 10000,epochs = 1):
    tr,val,test = wrap_data()

    for x in range(epochs):
        counter = 0
        for img in tr:
            if(counter > samples):
                break
            # if(counter % 1000 == 0):
            #     print("Epoch %d:Trained %d/%d" % (x,counter,samples))
            counter += 1
            data,digit = img
            ann.train(np.array([data.ravel()],dtype=np.float32),
                      cv2.ml.ROW_SAMPLE,np.array([digit.ravel()],dtype=np.float32))  # 拉平成单行数组
        print("Epoch %d complete" % x)
    return ann,test

# def test(ann,test_data):
#     sample = np.array(test_data[0][0].ravel(),dtype=np.float32).reshape(28,28)
#     cv2.imshow("sample",sample)
#     cv2.waitKey()
#     print(ann.predict(np.array([test_data[0][0].racel()],dtype=np.float32)))

def predict(ann,sample):
    resized = sample.copy()
    rows,cols = resized.shape
    if(rows != 28 or cols != 28) and rows * cols > 0:  # 对大小不同的图像进行统一resize
        resized = cv2.resize(resized,(28,28),interpolation=cv2.INTER_CUBIC)
    return predict(np.array([resized.ravel()],dtype=np.float32))

def inside(r1,r2):  # 判断r1是否在r2内部
    x1,y1,w1,h1 = r1
    x2,y2,w2,h2 = r2
    if(x1 > x2) and (y1 > y2) and (x1+w1 < x2+w2) and (y1+h1 < y2+h2):
        return True
    else:
        return False

def wrap_digit(rect):
    x,y,w,h = rect
    padding = 5
    hcenter = x + w/2
    vcenter = y + h/2
    if(h > w):
        w = h
        x = hcenter - (w/2)
    else:
        h = w
        y = vcenter - (h/2)
    return (x-padding,y-padding,w+padding,h+padding)


if __name__ == '__main__':
    ann,test_data = train(create_ANN(56),2000)
    font = cv2.FONT_HERSHEY_SIMPLEX

    path = './images/numbers.png'
    img = cv2.imread(path,cv2.IMREAD_UNCHANGED)
    bw = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    bw = cv2.GaussianBlur(bw,(7,7),0)
    ret,thbw = cv2.threshold(bw,127,255,cv2.THRESH_BINARY_INV)
    thbw = cv2.erode(thbw,np.ones((2,2),np.uint8),iterations=2)  # 腐蚀操作
    # cntrs ,整个的轮廓，每一行都代表一个轮廓中所有点的坐标
    cntrs,hier = cv2.findContours(thbw.copy(),cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)   # 检测所有轮廓，仅保存轮廓的拐点信息

    rectangles = []

    for c in cntrs:
        r = x,y,w,h = cv2.boundingRect(c)  # 计算轮廓的垂直边界最小矩形
        a = cv2.contourArea(c)  # 计算图像轮廓的面积
        b = (img.shape[0] - 3) * (img.shape[1] - 3)

        is_inside = False

        for q in rectangles:
            if inside(r,q):
                is_inside = True
                break
            if not is_inside:
                if not a == b:  # 不是整个图像
                    rectangles.append(r)

    for r in rectangles:
        x,y,w,h = wrap_digit(r)
        cv2.rectangle(img,(x,y),(x+w,y+h),(0,255,0),2)
        roi = thbw[y:y+h,x:x+w]

        try:
            digit_class = int(predict(ann,roi.copy())[0])
        except:
            continue
        cv2.putText(img,"%d" % digit_class,(x,y - 1),font,1,(0,255,0))

    cv2.imshow("thbw",thbw)
    cv2.imshow("contours",img)
    cv2.imwrite("sample.jpg",img)
    cv2.waitKey()
