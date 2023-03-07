

#include <AllegroFlare/GameEventDatas/VirtualControllerButtonReleasedEventData.hpp>




namespace AllegroFlare
{
namespace GameEventDatas
{


VirtualControllerButtonReleasedEventData::VirtualControllerButtonReleasedEventData(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::GameEventDatas::VirtualControllerButtonReleasedEventData::TYPE)
   , player(player)
   , virtual_controller(virtual_controller)
   , virtual_controller_button_num(virtual_controller_button_num)
{
}


VirtualControllerButtonReleasedEventData::~VirtualControllerButtonReleasedEventData()
{
}


void VirtualControllerButtonReleasedEventData::set_player(AllegroFlare::Player* player)
{
   this->player = player;
}


void VirtualControllerButtonReleasedEventData::set_virtual_controller(AllegroFlare::VirtualControllers::Base* virtual_controller)
{
   this->virtual_controller = virtual_controller;
}


void VirtualControllerButtonReleasedEventData::set_virtual_controller_button_num(int virtual_controller_button_num)
{
   this->virtual_controller_button_num = virtual_controller_button_num;
}


AllegroFlare::Player* VirtualControllerButtonReleasedEventData::get_player() const
{
   return player;
}


AllegroFlare::VirtualControllers::Base* VirtualControllerButtonReleasedEventData::get_virtual_controller() const
{
   return virtual_controller;
}


int VirtualControllerButtonReleasedEventData::get_virtual_controller_button_num() const
{
   return virtual_controller_button_num;
}




} // namespace GameEventDatas
} // namespace AllegroFlare


