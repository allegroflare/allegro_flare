

#include <AllegroFlare/DialogTree/Nodes/EmitGameEvent.hpp>




namespace AllegroFlare
{
namespace DialogTree
{
namespace Nodes
{


EmitGameEvent::EmitGameEvent(std::string game_event_name, std::string immediate_next_node_identifier)
   : AllegroFlare::DialogTree::Nodes::Base(AllegroFlare::DialogTree::Nodes::EmitGameEvent::TYPE)
   , game_event_name(game_event_name)
   , immediate_next_node_identifier(immediate_next_node_identifier)
{
}


EmitGameEvent::~EmitGameEvent()
{
}


std::string EmitGameEvent::get_game_event_name() const
{
   return game_event_name;
}


std::string EmitGameEvent::get_immediate_next_node_identifier() const
{
   return immediate_next_node_identifier;
}




} // namespace Nodes
} // namespace DialogTree
} // namespace AllegroFlare


