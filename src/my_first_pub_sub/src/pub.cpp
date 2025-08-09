#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "custom_interface/msg/num.hpp"


using namespace std::chrono_literals;

class MinimalPublisher :public rclcpp::Node{
    public:
        MinimalPublisher():Node("publisher"){
            publisher_ = this->create_publisher<custom_interface::msg::Num>("topic",10);
            timer_=this->create_wall_timer(1000ms,std::bind(&MinimalPublisher::timer_callback,this));

    }
    private:
        void timer_callback(){
            auto message = custom_interface::msg::Num();
            message.num = this->count++;
            RCLCPP_INFO(this->get_logger(), "Publishing: '%ld'", message.num);
            publisher_->publish(message);
        }
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<custom_interface::msg::Num>::SharedPtr publisher_;
        size_t count;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}