

#include <AllegroFlare/RouteEventDatas/ActivateScreen.hpp>




namespace AllegroFlare
{
namespace RouteEventDatas
{


ActivateScreen::ActivateScreen(std::string screen_identifier)
   : AllegroFlare::RouteEventDatas::Base(AllegroFlare::RouteEventDatas::ActivateScreen::TYPE)
   , screen_identifier(screen_identifier)
{
}


ActivateScreen::~ActivateScreen()
{
}


void ActivateScreen::set_screen_identifier(std::string screen_identifier)
{
   this->screen_identifier = screen_identifier;
}


std::string ActivateScreen::get_screen_identifier() const
{
   return screen_identifier;
}




} // namespace RouteEventDatas
} // namespace AllegroFlare


