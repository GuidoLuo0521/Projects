# 一个 简单 ORC

import cv2
import numpy as np

def ORC_Imread(path):
    return cv2.imread(path)    

def ORC_Resize(mat):
    return cv2.resize(mat,(500,500))    

#######################  滤波  #################################
# 低通滤波
def ORC_Blur(mat, ksize = 5):
    return cv2.blur(mat, (ksize, ksize))

# 方波滤波器
def ORC_BoxFilter(mat, ksize = 5):
    return cv2.boxFilter(mat, -1, (ksize, ksize))
 
# 高斯滤波
def ORC_GaussianBlur(mat, ksize = 5):
    return cv2.GaussianBlur(mat, (ksize, ksize), 0)

# 中值滤波
def ORC_MedianBlur(mat, ksize = 5):
    return cv2.medianBlur(mat, ksize)



##########################################################
    
def ORC_ToGrayColor(mat):
    return cv2.cvtColor(mat, cv2.COLOR_RGB2GRAY)

def ORC_Canny(mat):
    return cv2.Canny(mat, 75, 255)

def ORC_Close(mat):
    return cv2.morphologyEx(mat, cv2.MORPH_CLOSE, cv2.getStructuringElement(  cv2.MORPH_RECT, (11, 11)))
    
def ORC_GetArea(mat):
    return cv2.contourArea(mat)
    
# 轮廓检测 绘制最外框的轮廓
def ORC_FindMaxAreaContoursAngle(mat):

    # contours 标记的轮廓，以 list 形式存在，每个轮廓中都包含了轮廓像素的坐标向量；
    # hierarchy 表示轮廓的继承关系，一般用不到;d
    contours, hierarchy = cv2.findContours(mat.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

    # 获取最大的一个轮廓，当然这里注意这里可能没检测到
    cnt = sorted(contours, key=ORC_GetArea, reverse=True)[0]

    # 得到最小外接矩形的（中心(x,y), (宽,高), 旋转角度）
    box = cv2.minAreaRect(cnt)
    angle = box[2]

    # 获取最小外接矩形的4个顶点坐标
    rect_points = cv2.boxPoints(box)

    #利用 np 填充所有点
    rect_points = np.int0(rect_points)

    # 绘制最小外接矩形
    #return [cv2.drawContours(raw, [rect_points], 0, (0, 0, 255), 2), angle]
    return angle



def ORC_RotateImage( mat, angle ):
    # 获取矩形中心
    h, w , c= mat.shape
    center= (w//2, h//2)

    # 获取旋转矩阵
    M = cv2.getRotationMatrix2D(center, angle, 1.0)

    # 仿射变换
    return cv2.warpAffine(mat, M, (w, h), flags=cv2.INTER_CUBIC, borderMode=cv2.BORDER_REPLICATE)


if __name__ == "__main__" :

    # 读取图片
    raw = ORC_Imread("images/image-20210629230839952.png")
    #raw = ORC_Imread("images/Snipaste_2021-07-01_23-12-45.png")
    cv2.imshow("raw", raw)

    # 重置大小
    #raw = ORC_Resize(raw)

    ## 滤波
    #mat = ORC_Blur(raw)
    #mat = ORC_BoxFilter(raw)
    mat = ORC_GaussianBlur(raw)
    #mat = ORC_MedianBlur(raw)
    #cv2.imshow("ORC_MedianBlur", mat)

    # 变灰度图
    mat = ORC_ToGrayColor(mat)
    #cv2.imshow("ORC_ToGrayColor", mat)

    # Canny 检测边缘
    mat = ORC_Canny(mat)
    #cv2.imshow("ORC_Canny", mat)

    # 闭运算扩展连通区域
    mat = ORC_Close(mat)
    #cv2.imshow("ORC_Close", mat)

    # 获取最大矩形旋转角度
    angle = ORC_FindMaxAreaContoursAngle(mat)

    # 旋转图形
    mat = ORC_RotateImage(raw, angle)

    cv2.imshow("Image", mat)
    cv2.waitKey(0)

    cv2.destroyAllWindows();
