cmake_minimum_required(VERSION 2.8)
project( ImageProc )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(TomeIII_bin/DisplayImage  TomeIII_src/DisplayImage.cpp)
target_link_libraries(TomeIII_bin/DisplayImage ${OpenCV_LIBS} )

add_executable(TomeIII_bin/LissagesImage  TomeIII_src/LissagesImage.cpp)
target_link_libraries(TomeIII_bin/LissagesImage ${OpenCV_LIBS} )

add_executable(TomeIII_bin/InRange  TomeIII_src/InRange.cpp)
target_link_libraries(TomeIII_bin/InRange ${OpenCV_LIBS} )

add_executable(TomeIII_bin/HatThrAt  TomeIII_src/HatThrAt.cpp)
target_link_libraries(TomeIII_bin/HatThrAt ${OpenCV_LIBS} )

add_executable(TomeIII_bin/ColorClassAt  TomeIII_src/ColorClassAt.cpp)
target_link_libraries(TomeIII_bin/ColorClassAt ${OpenCV_LIBS} )

add_executable(TomeIII_bin/CVEdMeanFiltering  TomeIII_src/CVEdMeanFiltering.cpp TomeIII_src/EdLibMeanFiltering.cpp TomeIII_src/DSCCvUtilities.cpp)
target_link_libraries(TomeIII_bin/CVEdMeanFiltering ${OpenCV_LIBS} )

add_executable(TomeIII_bin/DisplayVideo  TomeIII_src/DisplayVideo.cpp)
target_link_libraries(TomeIII_bin/DisplayVideo ${OpenCV_LIBS} )

add_executable(TomeIII_bin/DisplayVideoBlur  TomeIII_src/DisplayVideoBlur.cpp)
target_link_libraries(TomeIII_bin/DisplayVideoBlur ${OpenCV_LIBS} )

add_executable(TomeIII_bin/DisplayVideoInRangeBW  TomeIII_src/DisplayVideoInRangeBW.cpp)
target_link_libraries(TomeIII_bin/DisplayVideoInRangeBW ${OpenCV_LIBS} )

add_executable(TomeIII_bin/DisplayVideoMeanFilteringBW  TomeIII_src/DisplayVideoMeanFilteringBW.cpp TomeIII_src/EdLibMeanFiltering.cpp TomeIII_src/DSCCvUtilities.cpp)
target_link_libraries(TomeIII_bin/DisplayVideoMeanFilteringBW ${OpenCV_LIBS})

add_executable(TomeIII_bin/DisplayVideoInRangeHSV  TomeIII_src/DisplayVideoInRangeHSV.cpp)
target_link_libraries(TomeIII_bin/DisplayVideoInRangeHSV ${OpenCV_LIBS} )

add_executable(TomeIII_bin/CVCannyCtrAppPoly_Priv TomeIII_src/CVCannyCtrAppPoly_Priv.cpp)
target_link_libraries(TomeIII_bin/CVCannyCtrAppPoly_Priv ${OpenCV_LIBS} )

add_executable(TomeIII_bin/InRangeBlobXXX  TomeIII_src/InRangeBlobXXX.cpp)
target_link_libraries(TomeIII_bin/InRangeBlobXXX ${OpenCV_LIBS} )

add_executable(TomeIII_bin/CVVid_InRangeHSV  TomeIII_src/CVVid_InRangeHSV.cpp)
target_link_libraries(TomeIII_bin/CVVid_InRangeHSV ${OpenCV_LIBS} )

add_executable(TomeIII_bin/HoughLine  TomeIII_src/HoughLine.cpp)
target_link_libraries(TomeIII_bin/HoughLine ${OpenCV_LIBS} )

add_executable(TomeIII_bin/HoughCircle  TomeIII_src/HoughCircle.cpp)
target_link_libraries(TomeIII_bin/HoughCircle ${OpenCV_LIBS} )

add_executable(TomeIII_bin/DetectVisage  TomeIII_src/DetectVisage.cpp)
target_link_libraries(TomeIII_bin/DetectVisage ${OpenCV_LIBS} )

add_executable(TomeIII_bin/CVVid_DetectVisage  TomeIII_src/CVVid_DetectVisage.cpp)
target_link_libraries(TomeIII_bin/CVVid_DetectVisage ${OpenCV_LIBS} )













