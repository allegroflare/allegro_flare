

#include <AllegroFlare/LoadASavedGame/SaveSlots/Basic.hpp>




namespace AllegroFlare
{
namespace LoadASavedGame
{
namespace SaveSlots
{


Basic::Basic(std::string save_name)
   : AllegroFlare::LoadASavedGame::SaveSlots::Base(AllegroFlare::LoadASavedGame::SaveSlots::Basic::TYPE)
   , save_name(save_name)
{
}


Basic::~Basic()
{
}


void Basic::set_save_name(std::string save_name)
{
   this->save_name = save_name;
}


std::string Basic::get_save_name() const
{
   return save_name;
}




} // namespace SaveSlots
} // namespace LoadASavedGame
} // namespace AllegroFlare


