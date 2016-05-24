#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "image_pub/Utility.h"
#include <vector>

int main(int argc, char** argv)
  {
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    cv::FileStorage config("/home/jinhwa/catkin_ws/src/image_pub-master/data/config.yml", cv::FileStorage::READ);
    cv_bridge::CvImage cv_image_left, cv_image_right;
    std::string dataPath;
    config["path"] >> dataPath;
    config.release();
    int frame1 = 0;
    std::vector<std::string> filenames_left, filenames_right;
    getFiles(dataPath + "left/", filenames_left);
    getFiles(dataPath + "right/", filenames_right);
    

    
    //cv_image.image = cv::imread(dataPath + "left/" + filenames_left[frame1],0);
   

  ros::Publisher pub_left = nh.advertise<sensor_msgs::Image>("output_ns/image_raw_left", 1);
  ros::Publisher pub_right = nh.advertise<sensor_msgs::Image>("output_ns/image_raw_right",1);
  ros::Rate loop_rate(5);

  while (nh.ok()) 
  {
    cv_image_left.image = cv::imread(dataPath + "left/" + filenames_left[frame1],CV_LOAD_IMAGE_COLOR);
    cv_image_right.image = cv::imread(dataPath + "right/" + filenames_right[frame1], CV_LOAD_IMAGE_COLOR);
     cv_image_left.encoding = "bgr8";
     cv_image_right.encoding = "bgr8";
    sensor_msgs::Image ros_image_left, ros_image_right;
    cv_image_left.toImageMsg(ros_image_left);
    cv_image_right.toImageMsg(ros_image_right);
    pub_left.publish(ros_image_left);
    pub_right.publish(ros_image_right);
    frame1++;
    loop_rate.sleep();
  }

  }
