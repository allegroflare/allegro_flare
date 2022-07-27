

#include <AllegroFlare/GameEvent.hpp>



namespace AllegroFlare
{


GameEvent::GameEvent(std::string name, AllegroFlare::GameEventDatas::Base* data)
   : name(name)
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


std::string GameEvent::get_name()
{
   return name;
}


AllegroFlare::GameEventDatas::Base* GameEvent::get_data()
{
   return data;
}


void GameEvent::todo()
{
   // rename "name" to "type"
}

bool GameEvent::is_type(std::string possible_type)
{
   return (name == possible_type);
}
} // namespace AllegroFlare


