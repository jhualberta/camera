import cv2 as cv
import numpy as np
#from matplotlib import pyplot as plt
img_rgb = cv.imread('camera_P.png')
img_gray = cv.cvtColor(img_rgb, cv.COLOR_BGR2GRAY)
template = cv.imread('pmt.png',0)
w, h = template.shape[::-1]
res = cv.matchTemplate(img_gray,template,cv.TM_CCOEFF_NORMED)
threshold = 0.5
loc = np.where( res >= threshold)

f = open("pt.txt","w") #create add file in write mode.

for pt in zip(*loc[::-1]):
    #cv.rectangle(img_rgb, (pt[0]+w/2, pt[1]+h/2), (pt[0]+w/2, pt[1]+h/2), (0,0,255), 2)
    cv.rectangle(img_rgb, pt, (pt[0] + w, pt[1] + h), (0,0,255), 2)

    f. write(str(pt[0]+w/2-2155)+' '+str(-(pt[1]+h/2)+2434)+'\n')
cv.imwrite('res0.png',img_rgb)

