import cv2
import cv2.cv as cv
import numpy as np

img = cv2.imread("camera_P.png")
gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
circles = cv2.HoughCircles(gray,cv.CV_HOUGH_GRADIENT, 1, 10)
