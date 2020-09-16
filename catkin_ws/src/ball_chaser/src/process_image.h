//
// Created by mcbot on 14.09.20.
//

#ifndef UDACITY_ND_ROBOTICS_PROCESS_IMAGE_H
#define UDACITY_ND_ROBOTICS_PROCESS_IMAGE_H

#include <vector>
#include <sensor_msgs/Image.h>

// the output of this function is an index independent on the image step.
// with this index, the width and the height it is possible to calculate the
// row and column values.
// This simple implementation returns the first white pixel index found
#include <vector>
int find_white_index(const sensor_msgs::Image& img){

  int white_pixel = 255;
  int white_index{-1};

  int sum_columns{};
  int n_pixels{};

  int pixel{0};
  int pixel_depth = img.step / img.width;
  for (int i{0}; i < img.height * img.step; i = i+pixel_depth){
    bool is_white{true};
    for (int d{0}; d < pixel_depth; ++d) {
      is_white &= img.data[i+d] == white_pixel;
    }
    if (is_white) {
      sum_columns += pixel%img.width;
      ++n_pixels;
    }
    ++pixel;
  }

  return n_pixels == 0 ? -1 : sum_columns/n_pixels;
}
std::vector<float> calculate_linear_and_angular_velocity( int column,
                                                        int img_width){
  if (column == -1) {
    std::cout << "Command don't move" << std::endl;
    return {0.0, 0.0};
  }

  if (column <= img_width/4) {
    // move to left

    std::cout << "Command move to the left" << std::endl;
    return {0.0, 0.25};
  }

  if (column <= 3*img_width/4) {
    // move forward
    std::cout << "Command move forward" << std::endl;
    return {0.25, 0.0};
  }

  // move to right
  std::cout << "Command move to the right" << std::endl;
  return {0.0, -0.25};


}
#endif//UDACITY_ND_ROBOTICS_PROCESS_IMAGE_H
