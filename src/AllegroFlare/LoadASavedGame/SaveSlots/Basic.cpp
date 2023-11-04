

#include <AllegroFlare/LoadASavedGame/SaveSlots/Basic.hpp>




namespace AllegroFlare
{
namespace LoadASavedGame
{
namespace SaveSlots
{


Basic::Basic(std::string property)
   : AllegroFlare::LoadASavedGame::SaveSlots::Base(AllegroFlare::LoadASavedGame::SaveSlots::Basic::TYPE)
   , property(property)
{
}


Basic::~Basic()
{
}


std::string Basic::get_property() const
{
   return property;
}


bool Basic::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace SaveSlots
} // namespace LoadASavedGame
} // namespace AllegroFlare


