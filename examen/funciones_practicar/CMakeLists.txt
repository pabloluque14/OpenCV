cmake_minimum_required (VERSION 3.0)
project (videoseg)
set(CMAKE_CXX_FLAGS "-std=c++11")
find_package(OpenCV 3.2 REQUIRED)


LINK_LIBRARIES(${OpenCV_LIBS})
add_executable(main.cpp funciones_p5.cpp)
