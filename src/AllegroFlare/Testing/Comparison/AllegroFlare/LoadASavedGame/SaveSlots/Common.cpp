

#include <AllegroFlare/Testing/Comparison/AllegroFlare/LoadASavedGame/SaveSlots/Common.hpp>


namespace AllegroFlare::LoadASavedGame::SaveSlots
{


bool operator==(const Common& object, const Common& other_object)
{
   if (object.screenshot_of_gameplay_at_save_identifier != other_object.screenshot_of_gameplay_at_save_identifier) return false;
   if (object.location_of_save != other_object.location_of_save) return false;
   if (object.date_and_time_of_save != other_object.date_and_time_of_save) return false;
   if (object.time_since_text != other_object.time_since_text) return false;
   if (object.save_time__seconds_since_epoch != other_object.save_time__seconds_since_epoch) return false;
   return true;
}


void PrintTo(const Common& object, ::std::ostream* os)
{
   *os << "AllegroFlare::LoadASavedGame::SaveSlots::Common("
       << "\"screenshot_of_gameplay_at_save_identifier\": \"" + object.screenshot_of_gameplay_at_save_identifier + "\", "
       << "\"location_of_save\": \"" + object.location_of_save + "\", "
       << "\"date_and_time_of_save\": \"" + object.date_and_time_of_save + "\", "
       << "\"save_time__seconds_since_epoch\": \"" + std::to_string(object.save_time__seconds_since_epoch) + "\", "
       << "\"time_since_text\": \"" + object.time_since_text + "\", "
   << ")";
}


}


