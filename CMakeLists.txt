cmake_minimum_required(VERSION 3.5)
project(MandelBrotSet)
SET(CMAKE_CXX_STANDARD 17)

find_package(CUDA REQUIRED)
add_executable(${CMAKE_PROJECT_NAME} src/src.cpp)

file(GLOB CUDA_LIBS "${CUDA_TOOLKIT_ROOT_DIR}/lib/x64/*")
add_subdirectory(./external/stb_image)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC src ${CUDA_INCLUDE_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${CUDA_LIBS} stb_image)

# message("${CUDA_INCLUDE_DIRS}")
# message("${CUDA_LIBRARIES}")
# message("${ll}")