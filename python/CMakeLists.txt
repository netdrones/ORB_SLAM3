cmake_minimum_required(VERSION 3.4...3.19)
project(orb_slam3 LANGUAGES CXX)

include(FetchContent)

# pybind11
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.10.3
)

FetchContent_MakeAvailable(pybind11)

find_package(Python 3.8 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11)

# ORB-SLAM3
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(
  ${OpenCV_INCLUDE_DIRS}
)

pybind11_add_module(
  orb_slam3
  ${CMAKE_CURRENT_LIST_DIR}/orb_slam3/orb_slam3.cc
)
target_link_libraries(
  orb_slam3
  PRIVATE ORB_SLAM3
)
