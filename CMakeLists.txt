cmake_minimum_required (VERSION 3.0)
set(CMAKE_CXX_FLAGS "-std=c++11")
find_package(OpenCV 3.2 REQUIRED)
LINK_LIBRARIES(${OpenCV_LIBS} )
add_executable(ejemplo1 ejemplo1.cpp)
add_executable(ejemplo2 ejemplo2.cpp)
add_executable(ejemplo3 ejemplo3.cpp)


 
