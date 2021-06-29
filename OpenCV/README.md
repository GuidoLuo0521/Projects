# 相机图像轮廓显示

​		一直再看 `OpenCV`的书，还是要做做项目才不觉得无聊，因此，今天做了一个项目来玩玩。

主要就是读取视频的每一帧，做一个高斯滤波，然后找轮廓，然后绘制轮廓，最后显示。

## 效果图

![1624551342194](images/1624551342194.png)

## 代码

[findContoursOnVideo.py](./findContoursOnVideo.py)

~~~python
import cv2
import time
import numpy as np

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if frame is not None:
        frame = cv2.GaussianBlur(frame, (11, 11), 2);

        gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY) 
        ret, binary = cv2.threshold(gray,127,255,cv2.THRESH_BINARY)
        
        contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)  

        newImg = np.zeros((800,800,3), np.uint8)  
        cv2.drawContours(newImg, contours,-1,(0,0,255),3) 
        cv2.imshow("Video", newImg)

        #cv2.drawContours(frame, contours,-1,(0,0,255),3) 
        #cv2.imshow("Video", frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

cap.release()
cv2.destroyAllWindows()
~~~



# <font alien=center>ORC</font>

感谢：https://www.cnblogs.com/wj-1314/p/11975977.html

## 摘要

​		采用`OpenCV`对图片进行文字提取。

​		**Keywords：`OpenCV`，ORC**

## 第一章  引言

​		现代社会，随着成像技术越发的发达，手机，相机等像素的提高，拍摄物体的清晰度越来越清楚，而且网络越发发达，所以，对图片中文字的提取就显得比较迫切。

​	

## 第二章 理论知识

### `OpenCV`

​		`OpenCV`是一个基于BSD许可（开源）发行的跨平台计算机视觉库，可以运行在Linux、Windows、Android和Mac OS操作系统上。它轻量级而且高效——由一系列 C 函数和少量 C++ 类构成 ，同时提供了Python、Ruby、`MATLAB`等语言的接口，实现了图像处理和计算机视觉方面的很多通用算法。

​	



## 第三章 实现步骤

### 文档轮廓提取

![image-20210629230839952](images/image-20210629230839952.png)

​		对于这类图片，因为拍摄的背景和前景较为清楚，但是图片有可能不是水平竖直的，所以，第一步需要对图像进行水平竖直矫正。`OpenCV`中，对于水平竖直的矫正，最简单的当然是 **[仿射变换](https://github.com/GuidoLuo0521/Notes/tree/master/LearnOpenCV)**咯

> [文档](https://www.geeksforgeeks.org/python-opencv-affine-transformation/)
>
> ~~~python
> Syntax: cv2.getPerspectiveTransform(src, dst)
> 
> Parameters:
> src: Coordinates of quadrangle vertices in the source image.
> dst: Coordinates of the corresponding quadrangle vertices in the destination image.
>     
> ###########################
> Syntax: cv2.warpAffine(src, M, dsize, dst, flags, borderMode, borderValue)    
>     
> Parameters:
> src: input image.
> dst: output image that has the size dsize and the same type as src.
> M: transformation matrix.
> dsize: size of the output image.
> flags: combination of interpolation methods (see resize() ) and the optional flag
> WARP_INVERSE_MAP that means that M is the inverse transformation (dst->src).
> borderMode: pixel extrapolation method; when borderMode=BORDER_TRANSPARENT, it means that the pixels in the destination image corresponding to the “outliers” in the source image are not modified by the function.
> borderValue: value used in case of a constant border; by default, it is 0.
> ~~~
>
> ~~~c++
> void cv::warpAffine(
>  	cv::InputArray src, // Input image
>  	cv::OutputArray dst, // Result image
>  	cv::InputArray M, // 2-by-3 transform mtx
>  	cv::Size dsize, // Destination image size
>  	int flags = cv::INTER_LINEAR, // Interpolation, inverse
>  	int borderMode = cv::BORDER_CONSTANT, // Pixel extrapolation
>  	const cv::Scalar& borderValue = cv::Scalar() // For constant borders
> );
> ~~~
>
> ​		
>
> **Example**
>
> ~~~python
> 
> import cv2
> import numpy as np
> from matplotlib import pyplot as plt
>   
>   
> img = cv2.imread('food.jpeg')
> rows, cols, ch = img.shape
>   
> pts1 = np.float32([[50, 50],
>                    [200, 50], 
>                    [50, 200]])
>   
> pts2 = np.float32([[10, 100],
>                    [200, 50], 
>                    [100, 250]])
>   
> M = cv2.getAffineTransform(pts1, pts2)
> dst = cv2.warpAffine(img, M, (cols, rows))
>   
> plt.subplot(121)
> plt.imshow(img)
> plt.title('Input')
>   
> plt.subplot(122)
> plt.imshow(dst)
> plt.title('Output')
>   
> plt.show()
>   
> # Displaying the image
> while(1):
>       
>     cv2.imshow('image', img)
>     if cv2.waitKey(20) & 0xFF == 27:
>         break
>           
> cv2.destroyAllWindows()
> ~~~
>
> **Output：**
>
> ![image-20210629235720190](images/image-20210629235720190.png)

​		当然，这其中最重要的当然要是怎么能找到变换的这个角度啊，变换的 **矩阵**，当然这个步骤也挺简单的：

首先因为这个图片的前背景对比是比较明显的，所以，可以通过二值化后，获取图片轮廓边界；再对轮廓线进行霍夫线检测，然后获取水平和竖直线，进而获取角度，这样就可以算出来变换矩阵了，再就可以将图片拉直了。

​		
