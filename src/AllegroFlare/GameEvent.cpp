

#include <AllegroFlare/GameEvent.hpp>

#include <iostream>


namespace AllegroFlare
{


GameEvent::GameEvent(std::string type, AllegroFlare::GameEventDatas::Base* data)
   : type(type)
   , data(data)
{
}


GameEvent::~GameEvent()
{
}


void GameEvent::set_data(AllegroFlare::GameEventDatas::Base* data)
{
   this->data = data;
}


std::string GameEvent::get_type() const
{
   return type;
}


AllegroFlare::GameEventDatas::Base* GameEvent::get_data() const
{
   return data;
}


std::string GameEvent::get_name()
{
   // TODO: update all dependent classes to use "get_type" instead
   std::cout << "[AllegroFlare::GameEvent::get_name]: warning: \"get_name()\" is depreciated. "
             << "Use \"get_type()\" which is identical in use."
             << std::endl;
   return type;
}

bool GameEvent::is_type(std::string possible_type)
{
   return (type == possible_type);
}


} // namespace AllegroFlare


