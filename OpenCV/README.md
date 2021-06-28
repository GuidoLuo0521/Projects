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





