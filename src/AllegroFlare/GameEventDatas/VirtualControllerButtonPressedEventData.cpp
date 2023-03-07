

#include <AllegroFlare/GameEventDatas/VirtualControllerButtonPressedEventData.hpp>




namespace AllegroFlare
{
namespace GameEventDatas
{


VirtualControllerButtonPressedEventData::VirtualControllerButtonPressedEventData(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::GameEventDatas::VirtualControllerButtonPressedEventData::TYPE)
   , player(player)
   , virtual_controller(virtual_controller)
   , virtual_controller_button_num(virtual_controller_button_num)
{
}


VirtualControllerButtonPressedEventData::~VirtualControllerButtonPressedEventData()
{
}


void VirtualControllerButtonPressedEventData::set_player(AllegroFlare::Player* player)
{
   this->player = player;
}


void VirtualControllerButtonPressedEventData::set_virtual_controller(AllegroFlare::VirtualControllers::Base* virtual_controller)
{
   this->virtual_controller = virtual_controller;
}


void VirtualControllerButtonPressedEventData::set_virtual_controller_button_num(int virtual_controller_button_num)
{
   this->virtual_controller_button_num = virtual_controller_button_num;
}


AllegroFlare::Player* VirtualControllerButtonPressedEventData::get_player() const
{
   return player;
}


AllegroFlare::VirtualControllers::Base* VirtualControllerButtonPressedEventData::get_virtual_controller() const
{
   return virtual_controller;
}


int VirtualControllerButtonPressedEventData::get_virtual_controller_button_num() const
{
   return virtual_controller_button_num;
}




} // namespace GameEventDatas
} // namespace AllegroFlare


