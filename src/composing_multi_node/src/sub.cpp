#include <memory>
#include <rclcpp_components/register_node_macro.hpp>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "custom_interface/msg/num.hpp"
using std::placeholders::_1;

class MinimalSubscriber :public rclcpp::Node{
public:
   MinimalSubscriber(const rclcpp::NodeOptions & options = rclcpp::NodeOptions()):Node("MinimalSub",options){
        subscription = this->create_subscription<custom_interface::msg::Num>("topic",10,std::bind(&MinimalSubscriber::topic_callback,this,_1));
    }
private:
    void topic_callback(const custom_interface::msg::Num & num)const {
        RCLCPP_INFO(this->get_logger(), "I heard: '%d'", num.num);
    }
rclcpp::Subscription<custom_interface::msg::Num>::SharedPtr subscription;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}

RCLCPP_COMPONENTS_REGISTER_NODE(MinimalSubscriber);