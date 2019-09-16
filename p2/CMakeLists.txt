CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(cv_tutorial)
FIND_PACKAGE(OpenCV 	REQUIRED )
include_directories ("${OpenCV_INCLUDE_DIRS}")
include_directories(${CMAKE_SOURCE_DIR}/tclap-1.2.1/include ${OpenCV_INCLUDE_DIRS})
LINK_LIBRARIES(${OpenCV_LIBS} )
add_executable(unsharp unsharp.cpp unsharpFunctions.cpp)


 
