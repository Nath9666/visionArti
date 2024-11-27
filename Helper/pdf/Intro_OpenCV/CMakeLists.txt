cmake_minimum_required(VERSION 2.8)
project( ImageProc )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(bin/1.DisplayImage  src/1.DisplayImage.cpp)
target_link_libraries(bin/1.DisplayImage ${OpenCV_LIBS} )
