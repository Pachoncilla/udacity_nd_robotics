//
// Created by cristina villegas on 14.09.20.
//

#include <gtest/gtest.h>
#include "process_image.h"

TEST(calculate_velocities, do_not_move){

  auto actual_velocity = calculate_linear_and_angular_velocity(-1, 100);
  ASSERT_EQ(0.0, actual_velocity[0]);
  ASSERT_EQ(0.0, actual_velocity[1]);
}

TEST(calculate_velocities, turn_left){

  auto actual_velocity = calculate_linear_and_angular_velocity(0, 100);
  ASSERT_EQ(0.5, actual_velocity[0]);
  ASSERT_EQ(0.0, actual_velocity[1]);
}

TEST(calculate_velocities, turn_right){

  auto actual_velocity = calculate_linear_and_angular_velocity(390, 100);
  ASSERT_EQ(0.0, actual_velocity[0]);
  ASSERT_EQ(-0.5, actual_velocity[1]);
}

TEST(calculate_velocities, move_forward){

  auto actual_velocity = calculate_linear_and_angular_velocity(350, 100);
  ASSERT_EQ(0.0, actual_velocity[0]);
  ASSERT_EQ(0.5, actual_velocity[1]);
}

TEST(find_white_index, returns_default_if_no_white_pixel_found){
  sensor_msgs::Image img;
  EXPECT_EQ(0, img.data[0]);

  ASSERT_EQ(-1, find_white_index(img));

}

TEST(find_white_index, returns_first_white_index){
  sensor_msgs::Image img;
  EXPECT_EQ(0, img.data[100]);
  img.data[100] = 255;


  ASSERT_EQ(100, find_white_index(img));

}