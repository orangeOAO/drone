import cv2

cv_image = cv2.imread('output.jpg')

# 确保图像加载成功
if cv_image is None:
    print("图像未加载，请检查文件路径")
    exit()

gray_image = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)
_, binary = cv2.threshold(gray_image, 127, 255, cv2.THRESH_BINARY)

# OpenCV 4.x的API调用
contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

draw_img0 = cv2.drawContours(cv_image.copy(), contours, 0, (0, 255, 255), 3)

cv2.imshow('image', draw_img0)
cv2.waitKey(0)
cv2.destroyAllWindows()
