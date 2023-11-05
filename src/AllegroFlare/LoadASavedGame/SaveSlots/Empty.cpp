

#include <AllegroFlare/LoadASavedGame/SaveSlots/Empty.hpp>




namespace AllegroFlare
{
namespace LoadASavedGame
{
namespace SaveSlots
{


Empty::Empty(std::string property)
   : AllegroFlare::LoadASavedGame::SaveSlots::Base(AllegroFlare::LoadASavedGame::SaveSlots::Empty::TYPE)
   , property(property)
{
}


Empty::~Empty()
{
}


std::string Empty::get_property() const
{
   return property;
}


bool Empty::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace SaveSlots
} // namespace LoadASavedGame
} // namespace AllegroFlare


