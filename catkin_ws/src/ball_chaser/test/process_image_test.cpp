//
// Created by cristina villegas on 14.09.20.
//


#include <gtest/gtest.h>
#include "process_image.h"
#include "sensor_msgs/image_encodings.h"
#include "sensor_msgs/fill_image.h"

namespace robot_test {
  constexpr int image_width{100};
  constexpr int column_on_left = 5;
  constexpr int column_on_right = 90;
  constexpr int column_in_front = 50;

  TEST(calculate_velocities, do_not_move) {

    auto actual_velocity =
            calculate_linear_and_angular_velocity(-1, image_width);
    ASSERT_EQ(0.0, actual_velocity[0]);
    ASSERT_EQ(0.0, actual_velocity[1]);
  }

  TEST(calculate_velocities, turn_left) {

    auto actual_velocity =
            calculate_linear_and_angular_velocity(column_on_left, image_width);
    ASSERT_EQ(0.0, actual_velocity[0]);
    ASSERT_EQ(0.25, actual_velocity[1]);
  }

  TEST(calculate_velocities, turn_right) {

    auto actual_velocity =
            calculate_linear_and_angular_velocity(column_on_right, image_width);
    ASSERT_EQ(0.0, actual_velocity[0]);
    ASSERT_EQ(-0.25, actual_velocity[1]);
  }

  TEST(calculate_velocities, move_forward) {

    auto actual_velocity = calculate_linear_and_angular_velocity(column_in_front, image_width);
    ASSERT_EQ(0.25, actual_velocity[0]);
    ASSERT_EQ(0.0, actual_velocity[1]);
  }

  TEST(find_white_index, returns_default_if_no_white_pixel_found) {
    sensor_msgs::Image img;
    int image_data[240 * 320];
    for (int i = 0; i < 240 * 320; ++i) { image_data[i] = 0; }
    sensor_msgs::fillImage(img, sensor_msgs::image_encodings::MONO8, 240, 320,
                           320, &image_data);

    EXPECT_EQ(0, img.data[0]);

    ASSERT_EQ(-1, find_white_index(img));
  }

  TEST(find_white_index, DISABLED_returns_first_white_index) {
    sensor_msgs::Image img;
    int image_data[240 * 320];
    for (int i = 0; i < 240 * 320; ++i) { image_data[i] = 0; }
    image_data[3] = 255;
    image_data[4] = 255;
    image_data[5] = 255;
    sensor_msgs::fillImage(img, sensor_msgs::image_encodings::MONO8, 240, 320,
                           320, &image_data);


    ASSERT_EQ(1, find_white_index(img));
  }

}