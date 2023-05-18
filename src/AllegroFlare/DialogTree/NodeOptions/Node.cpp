

#include <AllegroFlare/DialogTree/NodeOptions/Node.hpp>




namespace AllegroFlare
{
namespace DialogTree
{
namespace NodeOptions
{


Node::Node(AllegroFlare::DialogTree::Node* node)
   : AllegroFlare::DialogTree::NodeOptions::Base(AllegroFlare::DialogTree::NodeOptions::Node::TYPE)
   , node(node)
{
}


Node::~Node()
{
}


void Node::set_node(AllegroFlare::DialogTree::Node* node)
{
   this->node = node;
}


AllegroFlare::DialogTree::Node* Node::get_node() const
{
   return node;
}




} // namespace NodeOptions
} // namespace DialogTree
} // namespace AllegroFlare


