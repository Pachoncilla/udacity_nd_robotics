//
// Created by cristina villegas on 10.09.20.
//

#include "ball_chaser/DriveToTarget.h"
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

ros::Publisher wheel_command_publisher;

bool handle_drive_request (ball_chaser::DriveToTarget::Request& request,
                          ball_chaser::DriveToTarget::Response& response){

  ROS_INFO("handler called");
  geometry_msgs::Twist velocity;
  velocity.linear.x = request.linear_x;
  velocity.angular.z = request.angular_z;

  wheel_command_publisher.publish(velocity);

  response.msg_feedback = "Angular velocities set - linear x: " +
                            std::to_string(request.linear_x) + " ,angular z: " +
                                                  std::to_string(request.angular_z);

    ROS_INFO_STREAM(response.msg_feedback);
    return true;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "drive_bot");
    ros::NodeHandle n;
  wheel_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot",
                                                    handle_drive_request);

    ROS_INFO("Ready to send velocity commands");

    ros::spin();
    return 0;
}
