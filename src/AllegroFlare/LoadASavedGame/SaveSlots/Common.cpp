

#include <AllegroFlare/LoadASavedGame/SaveSlots/Common.hpp>




namespace AllegroFlare
{
namespace LoadASavedGame
{
namespace SaveSlots
{


Common::Common(std::string screenshot_of_gameplay_at_save_identifier, std::string location_of_save, std::string date_and_time_of_save, std::string time_since_text, std::time_t save_time__seconds_since_epoch)
   : AllegroFlare::LoadASavedGame::SaveSlots::Base(AllegroFlare::LoadASavedGame::SaveSlots::Common::TYPE)
   , screenshot_of_gameplay_at_save_identifier(screenshot_of_gameplay_at_save_identifier)
   , location_of_save(location_of_save)
   , date_and_time_of_save(date_and_time_of_save)
   , time_since_text(time_since_text)
   , save_time__seconds_since_epoch(save_time__seconds_since_epoch)
{
}


Common::~Common()
{
}




} // namespace SaveSlots
} // namespace LoadASavedGame
} // namespace AllegroFlare


