#include<memory>
#include "rclcpp/rclcpp.hpp"
void node_info(rclcpp::Node::SharedPtr node){
    RCLCPP_INFO(node->get_logger(),"Node name is %s",node->get_name());
}

class SimpleNode:public rclcpp::Node{
public:
    SimpleNode(const std::string & node_name):Node(node_name){

    }
};

int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    auto node =std::make_shared<SimpleNode>("simple_Node");
    node_info(node);
    return 0;
}
