//
// Created by mcbot on 14.09.20.
//

#ifndef UDACITY_ND_ROBOTICS_PROCESS_IMAGE_H
#define UDACITY_ND_ROBOTICS_PROCESS_IMAGE_H

#include <vector>
#include <sensor_msgs/Image.h>

int find_white_index(const sensor_msgs::Image& img){

  int white_pixel = 255;
  int white_index{-1};

  int pixel{0};
  for (int i{0}; i < img.height * img.step; i = i+3){
    if (img.data[i] == white_pixel && img.data[i+1] == white_pixel &&
        img.data[i+2] == white_pixel) {
      white_index = pixel;
    }
    ++pixel;
  }

  return white_index;
}
std::vector<float> calculate_linear_and_angular_velocity( int index,
                                                        int img_width){
  if (index == -1) {
    std::cout << "Command don't move" << std::endl;
    return {0.0, 0.0};
  }

  int col = index % img_width;
  if (col <= img_width/4) {
    // move to left

    std::cout << "Command move to the left" << std::endl;
    return {0.0, 0.5};
  }

  if (col <= 3*img_width/4) {
    // move forward
    std::cout << "Command move forward" << std::endl;
    return {0.5, 0.0};
  }

  // move to right
  std::cout << "Command move to the right" << std::endl;
  return {0.0, -0.5};


}
#endif//UDACITY_ND_ROBOTICS_PROCESS_IMAGE_H
