

#include <AllegroFlare/DialogTree/Nodes/EmitGameEvent.hpp>




namespace AllegroFlare
{
namespace DialogTree
{
namespace Nodes
{


EmitGameEvent::EmitGameEvent(std::string game_event_name)
   : AllegroFlare::DialogTree::Nodes::Base(AllegroFlare::DialogTree::Nodes::EmitGameEvent::TYPE)
   , game_event_name(game_event_name)
{
}


EmitGameEvent::~EmitGameEvent()
{
}


std::string EmitGameEvent::get_game_event_name() const
{
   return game_event_name;
}




} // namespace Nodes
} // namespace DialogTree
} // namespace AllegroFlare


