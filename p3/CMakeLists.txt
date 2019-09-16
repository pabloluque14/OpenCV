CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(cv_tutorial)
FIND_PACKAGE(OpenCV 	REQUIRED )
include_directories ("${OpenCV_INCLUDE_DIRS}")
LINK_LIBRARIES(${OpenCV_LIBS} )
add_executable(augReal augReal.cpp funciones.cpp)


 
