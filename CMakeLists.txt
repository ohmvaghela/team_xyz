cmake_minimum_required(VERSION 3.0.2)
project(team_xyz)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES team_xyz
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(ConsoleApplication6 src/ConsoleApplication6.cpp)
target_link_libraries(ConsoleApplication6 ${catkin_LIBRARIES} )
add_dependencies(ConsoleApplication6 exo_angle_control)
