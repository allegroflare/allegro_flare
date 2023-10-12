

#include <AllegroFlare/DialogTree/Nodes/Wait.hpp>




namespace AllegroFlare
{
namespace DialogTree
{
namespace Nodes
{


Wait::Wait(float duration_sec, std::string next_node_identifier)
   : AllegroFlare::DialogTree::Nodes::Base(AllegroFlare::DialogTree::Nodes::Wait::TYPE)
   , duration_sec(duration_sec)
   , next_node_identifier(next_node_identifier)
{
}


Wait::~Wait()
{
}


void Wait::set_next_node_identifier(std::string next_node_identifier)
{
   this->next_node_identifier = next_node_identifier;
}


float Wait::get_duration_sec() const
{
   return duration_sec;
}


std::string Wait::get_next_node_identifier() const
{
   return next_node_identifier;
}




} // namespace Nodes
} // namespace DialogTree
} // namespace AllegroFlare


