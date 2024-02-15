cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME "deinterlacer")
project(${PROJECT_NAME})

# Find libjpeg
find_package(JPEG REQUIRED)
include_directories(include ${JPEG_INCLUDE_DIR})

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/deinterlace.cpp
    src/jpegObj.cpp)

target_link_libraries(${PROJECT_NAME} ${JPEG_LIBRARIES})
