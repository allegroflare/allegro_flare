

#include <AllegroFlare/RouteEventDatas/StartLevel.hpp>




namespace AllegroFlare
{
namespace RouteEventDatas
{


StartLevel::StartLevel(std::string level_identifier)
   : AllegroFlare::RouteEventDatas::Base(AllegroFlare::RouteEventDatas::StartLevel::TYPE)
   , level_identifier(level_identifier)
{
}


StartLevel::~StartLevel()
{
}


void StartLevel::set_level_identifier(std::string level_identifier)
{
   this->level_identifier = level_identifier;
}


std::string StartLevel::get_level_identifier() const
{
   return level_identifier;
}




} // namespace RouteEventDatas
} // namespace AllegroFlare


