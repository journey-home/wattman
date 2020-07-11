#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy,os,cv2,rospkg
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

def find_images(image_dir):
    image_list = []   
    for root, dirs, files in os.walk(image_dir):  
        for file in files:  
            if os.path.splitext(file)[1] == '.jpeg':  
                image_list.append(os.path.join(root, file))
    return image_list 


def image_publisher():
	# ROS节点初始化
    rospy.init_node('image_publisher', anonymous=True)

    # 获取 图片路径
    image_list = find_images(rospkg.RosPack().get_path("image_process")[:-17]+"./imgs_dir")
    if(len(image_list) == 0):
        rospy.loginfo("not find image!")

    # 根据图片数量设置 队列长度
    pub = rospy.Publisher('camera/image', Image, queue_size=len(image_list))

	#设置循环的频率
    rate = rospy.Rate(10) 

    while not rospy.is_shutdown():
        for image_path in image_list:
            pub.publish(CvBridge().cv2_to_imgmsg(cv2.imread(image_path),"bgr8"))

		# 按照循环频率延时
        rate.sleep()

if __name__ == '__main__':
    try:
        image_publisher()
    except rospy.ROSInterruptException:
        pass

