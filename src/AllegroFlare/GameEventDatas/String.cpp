

#include <AllegroFlare/GameEventDatas/String.hpp>




namespace AllegroFlare
{
namespace GameEventDatas
{


String::String(std::string string)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::GameEventDatas::String::TYPE)
   , string(string)
{
}


String::~String()
{
}


std::string String::get_string() const
{
   return string;
}




} // namespace GameEventDatas
} // namespace AllegroFlare


