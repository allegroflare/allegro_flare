

#include <AllegroFlare/GameEvent.hpp>




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


bool GameEvent::is_type(std::string possible_type)
{
   return (type == possible_type);
}

bool GameEvent::data_is_type(std::string data_possible_type)
{
   return (data && data->is_type(data_possible_type));
}


} // namespace AllegroFlare


