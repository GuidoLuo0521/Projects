# 一个 简单 ORC

import cv2
import numpy as np

def ORC_Imread(path):
    return cv2.imread(path)    

def ORC_Resize(mat):
    return cv2.resize(mat,(500,500))    

def ORC_GaussianBlur(mat, ksize = 5):
    return cv2.GaussianBlur(mat, (ksize, ksize), 0)
    
def ORC_ToGrayColor(mat):
    return cv2.cvtColor(mat, cv2.COLOR_RGB2GRAY)

def ORC_Canny(mat):
    return cv2.Canny(mat, 75, 255)

def ORC_Close(mat):
    return cv2.morphologyEx(mat, cv2.MORPH_CLOSE, cv2.getStructuringElement(  cv2.MORPH_RECT, (11, 11)))
    
def ORC_GetArea(mat):
    return cv2.contourArea(mat)
    
# 轮廓检测 绘制最外框的轮廓
def ORC_FindMaxAreaContours(raw, mat):

    # contours 标记的轮廓，以 list 形式存在，每个轮廓中都包含了轮廓像素的坐标向量；
    # hierarchy 表示轮廓的继承关系，一般用不到;d
    contours, hierarchy = cv2.findContours(mat.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

    # 获取最大的一个轮廓，当然这里主意这里可能没检测到
    cnt = sorted(contours, key=ORC_GetArea, reverse=True)[0]

    # 外接图形
    box = cv2.minAreaRect(cnt)
    # 获取点矩形所有点
    rect_points = cv2.boxPoints(box)
    #利用 np 填充所有点
    rect_points = np.int0(rect_points)

    # 绘制最小外接矩形
    return cv2.drawContours(raw, [rect_points], 0, (0, 0, 255), 2)

    # [cnt] 将参数转为数组
    #return cv2.drawContours(raw, [box], -1, (0, 255, 0), 2)


if __name__ == "__main__" :

    # 读取图片
    raw = ORC_Imread("images/image-20210629230839952.png")

    # 重置大小
    raw = ORC_Resize(raw)

    # 高斯滤波
    mat = ORC_GaussianBlur(raw)

    # 变灰度图
    mat = ORC_ToGrayColor(mat)

    # Canny 检测边缘
    mat = ORC_Canny(mat)

    # 闭运算扩展连通区域
    mat = ORC_Close(mat)
    cv2.imshow("pre process", mat)

    
    mat = ORC_FindMaxAreaContours( raw, mat)

    cv2.imshow("comtours", mat)
    cv2.waitKey(0)

    cv2.destroyAllWindows();
