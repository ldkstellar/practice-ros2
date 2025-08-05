#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    // if (argc!=3)
    // {
    //     RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"usage: add_two_ints_client XY");
    //     return 1;
    // }


    std::shared_ptr<rclcpp::Node> node = std::make_shared<rclcpp::Node>("add_two_ints_client");
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client = node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();


    //atoll string covert to long long int
    while (true)
    {
        std::string a,b;
        std::cout<<"숫자를 입력하세요"<<std::endl;
        std::cin >>a>>b;

            

        /* code */
        request->a = atoll(a.c_str());
        request->b = atoll(b.c_str());
    
        // true if the service is ready and the timeout is not over, 
        while (!client->wait_for_service(1s))
        {
            if (!rclcpp::ok()) // not given shared ptr
            {
                RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"Interrupted while waiting for the service. Exiting.");
                return 0;
    
            }
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
        }
    
        auto result = client->async_send_request(request);
    
        // Wait for the result.
      if (rclcpp::spin_until_future_complete(node, result) ==
        rclcpp::FutureReturnCode::SUCCESS)
      {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->sum);
      } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
      }
    }
    

  rclcpp::shutdown();
    return 0;
}
