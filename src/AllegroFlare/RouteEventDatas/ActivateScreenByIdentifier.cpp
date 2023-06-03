

#include <AllegroFlare/RouteEventDatas/ActivateScreenByIdentifier.hpp>




namespace AllegroFlare
{
namespace RouteEventDatas
{


ActivateScreenByIdentifier::ActivateScreenByIdentifier(std::string screen_identifier)
   : AllegroFlare::RouteEventDatas::Base(AllegroFlare::RouteEventDatas::ActivateScreenByIdentifier::TYPE)
   , screen_identifier(screen_identifier)
{
}


ActivateScreenByIdentifier::~ActivateScreenByIdentifier()
{
}


void ActivateScreenByIdentifier::set_screen_identifier(std::string screen_identifier)
{
   this->screen_identifier = screen_identifier;
}


std::string ActivateScreenByIdentifier::get_screen_identifier() const
{
   return screen_identifier;
}




} // namespace RouteEventDatas
} // namespace AllegroFlare


