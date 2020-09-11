include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(drive_bot drive_bot.cpp)
target_link_libraries(drive_bot ${catkin_LIBRARIES})
add_dependencies(drive_bot ball_chaser_generate_messages_cpp)