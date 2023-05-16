

#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>




namespace AllegroFlare
{
namespace DialogTree
{
namespace NodeOptions
{


GoToNode::GoToNode(std::string target_node_name)
   : AllegroFlare::DialogTree::NodeOptions::Base(AllegroFlare::DialogTree::NodeOptions::GoToNode::TYPE)
   , target_node_name(target_node_name)
{
}


GoToNode::~GoToNode()
{
}


void GoToNode::set_target_node_name(std::string target_node_name)
{
   this->target_node_name = target_node_name;
}


std::string GoToNode::get_target_node_name() const
{
   return target_node_name;
}




} // namespace NodeOptions
} // namespace DialogTree
} // namespace AllegroFlare


