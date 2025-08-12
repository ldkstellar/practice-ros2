#include<memory>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_lifecycle/lifecycle_node.hpp"

void node_info(std::shared_ptr<rclcpp::node_interfaces::NodeBaseInterface>base_interface,std::shared_ptr<rclcpp::node_interfaces::NodeLoggingInterface> logging_interface){
    RCLCPP_INFO(logging_interface->get_logger(),"Node name: %s",base_interface->get_name());
}
class SimpleNode:public rclcpp::Node{
public:
    SimpleNode(const std::string &node_name):Node(node_name){

    }
};

class LifeCycleTalker :public rclcpp_lifecycle::LifecycleNode{
    public:
    explicit LifeCycleTalker(const std::string & node_name, bool intra_process_comms = false):LifecycleNode(node_name,rclcpp::NodeOptions().use_intra_process_comms(intra_process_comms)){

    }
};

int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    rclcpp::executors::SingleThreadedExecutor exe;
    auto node = std::make_shared<SimpleNode>("Simple_node");
    auto lc_node = std::make_shared<LifeCycleTalker>("Simple_LifeCycle_Node");
    node_info(node->get_node_base_interface(),node->get_node_logging_interface());
    node_info(lc_node->get_node_base_interface(),lc_node->get_node_logging_interface());
    
    return 0;
}
