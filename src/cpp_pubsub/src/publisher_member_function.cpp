// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp" //ros2 system을 가장흔핱 부분을 사용할수있게해주는 include
#include "std_msgs/msg/string.hpp" // data를 퍼블리쉬할때 사용하는것 

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node // 고유의 노드 
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);// 퍼블리셔 이름 및 queuesize 백업 발생시 메시지를 제한하기 위한 필요한 대기열 즉 구독자가 메세지를 소비하지 못하면 쌍이는 임시공간
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback() // 어디에 메세지 데이터가 셋도는지와 메세지가 실제로 발행되는다.RCLCPP_INFO 매크로는  매 발행된 메세지를 프린한다.
  {
    auto message = std_msgs::msg::String();
    message.data = "welcome to Ros2 " + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);// ros2를 초기화 한다.
  rclcpp::spin(std::make_shared<MinimalPublisher>()); //노드에서 데이터를 처치함다 동식에 콜백을 포함한다. 타이머를 통해
  rclcpp::shutdown();
  return 0;
}
