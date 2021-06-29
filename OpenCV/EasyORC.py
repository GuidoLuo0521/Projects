# 一个 简单 ORC

import cv2

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
    
# 轮廓检测 绘制最外框的轮廓
def ORC_FindContours(raw, mat):
    contours, hierarchy = cv2.findContours(mat.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
    cnts = sorted(contours, key=cv2.contourArea, reverse=True)[:5]

    # 遍历轮廓
    for c in cnts:
        # 计算轮廓近似
        peri = cv2.arcLength(c, True)
        # c表示输入的点集，epsilon表示从原始轮廓到近似轮廓的最大距离，它是一个准确度参数
        approx = cv2.approxPolyDP(c, 0.02*peri, True)
 
        # 4个点的时候就拿出来
        if len(approx) == 4:
            screenCnt = approx
            break

    return cv2.drawContours(raw, [screenCnt], -1, (0, 255, 0), 2)



if __name__ == "__main__" :

    # 读取图片
    mat = ORC_Imread("images/image-20210629230839952.png")

    # 重置大小
    mat = ORC_Resize(mat)

    # 高斯滤波
    mat = ORC_GaussianBlur(mat)

    # 变灰度图
    mat = ORC_ToGrayColor(mat)

    # Canny 检测边缘
    mat = ORC_Canny(mat)

    # 闭运算扩展连通区域
    mat = ORC_Close(mat)
    cv2.imshow("pre process", mat)

    mat = ORC_FindContours(ORC_Imread("images/image-20210629230839952.png"), mat)

    cv2.imshow("comtours", mat)
    cv2.waitKey(0)

    cv2.destroyAllWindows();
