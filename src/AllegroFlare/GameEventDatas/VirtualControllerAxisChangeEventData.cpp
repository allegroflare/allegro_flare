

#include <AllegroFlare/GameEventDatas/VirtualControllerAxisChangeEventData.hpp>




namespace AllegroFlare
{
namespace GameEventDatas
{


VirtualControllerAxisChangeEventData::VirtualControllerAxisChangeEventData(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_stick, int virtual_controller_axis, float virtual_controller_position)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::GameEventDatas::VirtualControllerAxisChangeEventData::TYPE)
   , player(player)
   , virtual_controller(virtual_controller)
   , virtual_controller_stick(virtual_controller_stick)
   , virtual_controller_axis(virtual_controller_axis)
   , virtual_controller_position(virtual_controller_position)
{
}


VirtualControllerAxisChangeEventData::~VirtualControllerAxisChangeEventData()
{
}


void VirtualControllerAxisChangeEventData::set_player(AllegroFlare::Player* player)
{
   this->player = player;
}


void VirtualControllerAxisChangeEventData::set_virtual_controller(AllegroFlare::VirtualControllers::Base* virtual_controller)
{
   this->virtual_controller = virtual_controller;
}


void VirtualControllerAxisChangeEventData::set_virtual_controller_stick(int virtual_controller_stick)
{
   this->virtual_controller_stick = virtual_controller_stick;
}


void VirtualControllerAxisChangeEventData::set_virtual_controller_axis(int virtual_controller_axis)
{
   this->virtual_controller_axis = virtual_controller_axis;
}


void VirtualControllerAxisChangeEventData::set_virtual_controller_position(float virtual_controller_position)
{
   this->virtual_controller_position = virtual_controller_position;
}


AllegroFlare::Player* VirtualControllerAxisChangeEventData::get_player() const
{
   return player;
}


AllegroFlare::VirtualControllers::Base* VirtualControllerAxisChangeEventData::get_virtual_controller() const
{
   return virtual_controller;
}


int VirtualControllerAxisChangeEventData::get_virtual_controller_stick() const
{
   return virtual_controller_stick;
}


int VirtualControllerAxisChangeEventData::get_virtual_controller_axis() const
{
   return virtual_controller_axis;
}


float VirtualControllerAxisChangeEventData::get_virtual_controller_position() const
{
   return virtual_controller_position;
}




} // namespace GameEventDatas
} // namespace AllegroFlare


