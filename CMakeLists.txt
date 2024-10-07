cmake_minimum_required(VERSION 3.29)
project(ImageResizerForDiscord)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 23)

# Find OpenCV package
set(OpenCV_DIR "C:/tools/opencv/build/x64/vc16/lib")
find_package(OpenCV REQUIRED)

# Include directories for OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Add your source files
add_executable(ImageResizerForDiscord main.cpp)

# Link OpenCV libraries
target_link_libraries(ImageResizerForDiscord ${OpenCV_LIBS})
