cmake_minimum_required(VERSION 3.4...3.19)
project(_orb_slam3 LANGUAGES CXX)

include(FetchContent)

# pybind11
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.10.3
  OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(pybind11)

find_package(Python 3.8 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

# ORB-SLAM3
# FetchContent_Declare(
# ORB_SLAM3
# GIT_REPOSITORY https://github.com/netdrones/ORB_SLAM3.git
# GIT_TAG 4ad9abb8bc917971dd93ea298aee0f4d7bfa51d7
# OVERRIDE_FIND_PACKAGE
# )

# FetchContent_MakeAvailable(ORB_SLAM3)
find_package(OpenCV 4.4 REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(
  ${OpenCV_INCLUDE_DIRS}
)

pybind11_add_module(
  _orb_slam3
  ${CMAKE_CURRENT_LIST_DIR}/orb_slam3/system.cc
)

target_link_libraries(
  _orb_slam3
  PRIVATE ORB_SLAM3
)
