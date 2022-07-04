

#include <AllegroFlare/GameEvent.hpp>



namespace AllegroFlare
{


GameEvent::GameEvent(std::string name)
   : name(name)
{
}


GameEvent::~GameEvent()
{
}


std::string GameEvent::get_name()
{
   return name;
}


} // namespace AllegroFlare


