

#include <AllegroFlare/GameEventDatas/ScreenActivated.hpp>




namespace AllegroFlare
{
namespace GameEventDatas
{


ScreenActivated::ScreenActivated(std::string screen_identifier)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::GameEventDatas::ScreenActivated::TYPE)
   , screen_identifier(screen_identifier)
{
}


ScreenActivated::~ScreenActivated()
{
}


std::string ScreenActivated::get_screen_identifier() const
{
   return screen_identifier;
}




} // namespace GameEventDatas
} // namespace AllegroFlare


