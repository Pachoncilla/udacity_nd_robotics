add_executable(process_image_test process_image_test.cpp)
target_include_directories(process_image_test PUBLIC ../src)
target_link_libraries(process_image_test gtest_main gtest)

add_test(NAME process_image_test
        COMMAND process_image_test)