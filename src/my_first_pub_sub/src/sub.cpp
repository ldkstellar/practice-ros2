#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "custom_interface/msg/num.hpp"
using std::placeholders::_1;

class MinimalSubscriber :public rclcpp::Node{
public:
    MinimalSubscriber():Node("MinimalSub"){
        subscription = this->create_subscription<std_msgs::msg::String>("topic",10,std::bind(&MinimalSubscriber::topic_callback,this,_1));

    }
private:
void topic_callback(const std_msgs::msg::String & msg)const {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
}
rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription;

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}