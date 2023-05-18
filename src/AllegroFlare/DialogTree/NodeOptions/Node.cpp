

#include <AllegroFlare/DialogTree/NodeOptions/Node.hpp>




namespace AllegroFlare
{
namespace DialogTree
{
namespace NodeOptions
{


Node::Node(std::string property)
   : AllegroFlare::DialogTree::NodeOptions::Base(AllegroFlare::DialogTree::NodeOptions::Node::TYPE)
   , property(property)
{
}


Node::~Node()
{
}


std::string Node::get_property() const
{
   return property;
}


bool Node::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace NodeOptions
} // namespace DialogTree
} // namespace AllegroFlare


