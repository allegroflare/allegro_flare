

#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/EnterRoom.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{
namespace ScriptEventDatas
{


EnterRoom::EnterRoom(std::string room_dictionary_name_to_enter)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::EnterRoom::TYPE)
   , room_dictionary_name_to_enter(room_dictionary_name_to_enter)
{
}


EnterRoom::~EnterRoom()
{
}


void EnterRoom::set_room_dictionary_name_to_enter(std::string room_dictionary_name_to_enter)
{
   this->room_dictionary_name_to_enter = room_dictionary_name_to_enter;
}


std::string EnterRoom::get_room_dictionary_name_to_enter() const
{
   return room_dictionary_name_to_enter;
}




} // namespace ScriptEventDatas
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


