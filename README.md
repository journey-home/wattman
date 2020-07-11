# wattman
wattman编程题

要求：
1. 用ros实现两个ros node ，其中 image_publisher node负责将文件./imgs_dir里面的所有图片，publish出去，然后image_processer node负责将图片顺时针旋转90°后pushlish出去。
2. image_publisher 采用python 实现， image_processer采用c++实现并需要支持多线程来处理数据，以提整体的性能。
3. ./imgs_dir里面可能包含多层子文件夹。
4. 需要将代码上传到github上。

系统环境
    ubuntu 16 
    ROS Kinetic Kame
下载
    git clone https://github.com/journey-home/wattman

编译
    cd wattman;
    catkin_make;
启动
    1. master 节点
        cd wattman;source devel/setup.sh;
        roscore 
    2. image_publisher
        cd wattman;source devel/setup.sh;
        rosrun image_process image_publisher_node.py 
    3. image_processer
        cd wattman;source devel/setup.sh;
        rosrun image_process image_processer_node
查看
    rosrun rviz rviz 
    add 选择 by tobic
        camera/image   为原图像
        camera/rotate_image  为处理后图像