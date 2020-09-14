//
// Created by cristina villegas on 11.09.20.
//

#include "ros/ros.h"
#include "process_image.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/Image.h>

ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
  ROS_INFO_STREAM("Sending the movement commands to the robot");

  ball_chaser::DriveToTarget srv;
  srv.request.linear_x = lin_x;
  srv.request.angular_z = ang_z;

  if (!client.call(srv))
    ROS_ERROR("Failed to call service command_robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image& img)
{

  // Loop through each pixel in the image and check if there's a bright white one
  // Then, identify if this pixel falls in the left, mid, or right side of the image
  // Depending on the white ball position, call the drive_bot function and pass velocities to it
  // Request a stop when there's no white ball seen by the camera

  int white_index = find_white_index(img);
  auto velocity = calculate_linear_and_angular_velocity(white_index, img.width);
  drive_robot(velocity[0], velocity[1]);

}

int main(int argc, char** argv){

  // initialize the node and create a handle for it
  ros::init(argc, argv, "process_image");
  ros::NodeHandle n;

  // the node is a client of the service to move the robot
  client = n.serviceClient<ball_chaser::DriveToTarget>
          ("/ball_chaser/command_robot");

  // the node subscribes to the rgb_camera/image_raw topic
  ros::Subscriber image_subscriber = n.subscribe("/camera/rgb/image_raw", 10,
                                                 process_image_callback);
  
  ros::spin();

  return 0;
}