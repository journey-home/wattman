#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <boost/thread.hpp>

void image_call_back(const sensor_msgs::ImageConstPtr& msg, image_transport::Publisher *pub)
{
  cv::Mat image = cv_bridge::toCvCopy(msg, "bgr8")->image;
  cv::Point2f center( (float)(image.cols/2) , (float) (image.rows/2));
  cv::Mat affine_matrix = getRotationMatrix2D( center, -90.0, 1.0 );
  warpAffine(image, image, affine_matrix, image.size());
  pub->publish(cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg());

  ROS_INFO_STREAM("image_call_back: [" << "in " << "] [thread=" << boost::this_thread::get_id() << "]");
  // ros::Duration(2).sleep(); 
  // ROS_INFO_STREAM("image_call_back: [" << "out " << "] [thread=" << boost::this_thread::get_id() << "]");
}
 
int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_processer");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/rotate_image", 1000);
  ros::AsyncSpinner spinner(0);
  spinner.start();

  image_transport::Subscriber sub1 = it.subscribe("camera/image", 1000, boost::bind(&image_call_back, _1, &pub));

  ros::waitForShutdown();
}