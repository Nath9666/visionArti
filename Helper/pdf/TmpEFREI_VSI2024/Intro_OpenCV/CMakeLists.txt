cmake_minimum_required(VERSION 2.8)
project( ImageProc )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(bin/1.DisplayImage  src/1.DisplayImage.cpp)
target_link_libraries(bin/1.DisplayImage ${OpenCV_LIBS} )

add_executable(bin/2.LissagesImage  src/2.LissagesImage.cpp)
target_link_libraries(bin/2.LissagesImage ${OpenCV_LIBS} )

add_executable(bin/3.InRange  src/3.InRange.cpp)
target_link_libraries(bin/3.InRange ${OpenCV_LIBS} )

add_executable(bin/4.InRangeHSV  src/4.InRangeHSV.cpp)
target_link_libraries(bin/4.InRangeHSV ${OpenCV_LIBS} )

add_executable(bin/6.DisplayVideoBlur  src/6.DisplayVideoBlur.cpp)
target_link_libraries(bin/6.DisplayVideoBlur ${OpenCV_LIBS} )

add_executable(bin/7.DisplayVideoInRangeBW  src/7.DisplayVideoInRangeBW.cpp)
target_link_libraries(bin/7.DisplayVideoInRangeBW ${OpenCV_LIBS} )


add_executable(bin/8.DisplayVideoInRangeHSV  src/8.DisplayVideoInRangeHSV.cpp)
target_link_libraries(bin/8.DisplayVideoInRangeHSV ${OpenCV_LIBS} )

add_executable(bin/9.HatThrAt  src/9.HatThrAt.cpp)
target_link_libraries(bin/9.HatThrAt ${OpenCV_LIBS} )

add_executable(bin/TestEdOpenCV  src/TestEdOpenCV.cpp src/DSCCvUtilities.cpp src/EdLibMeanFiltering.cpp)
target_link_libraries(bin/TestEdOpenCV ${OpenCV_LIBS} )

add_executable(bin/TestVideoEdOpenCV  src/TestVideoEdOpenCV.cpp src/DSCCvUtilities.cpp src/EdLibMeanFiltering.cpp)
target_link_libraries(bin/TestVideoEdOpenCV ${OpenCV_LIBS} )




