cmake_minimum_required(VERSION 3.8)
project(tutorial_interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Num.msg"
  "msg/Sphere.msg"
  "srv/AddThreeInts.srv"
  DEPENDENCIES geometry_msgs # Add packages that above messages depend on, in this case geometry_msgs for Sphere.msg
)

find_package(rclcpp REQUIRED)

# pub/sub
# add_executable(talker src/publisher_member_function.cpp)
# ament_target_dependencies(talker rclcpp tutorial_interfaces) # CHANGE
# add_executable(listener src/subscriber_member_function.cpp)
# ament_target_dependencies(listener rclcpp tutorial_interfaces) # CHANGE
# install(TARGETS
# talker
# listener
# DESTINATION lib/${PROJECT_NAME})

# add three ints
# add_executable(server src/add_two_ints_server.cpp)
# ament_target_dependencies(server
# rclcpp tutorial_interfaces) # CHANGE
# add_executable(client src/add_two_ints_client.cpp)
# ament_target_dependencies(client
# rclcpp tutorial_interfaces) # CHANGE
# install(TARGETS
# server
# client
# DESTINATION lib/${PROJECT_NAME})
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)

  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)

  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
