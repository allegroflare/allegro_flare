

#include <AllegroFlare/JSONLoaders/AllegroFlare/LoadASavedGame/SaveSlots/Common.hpp>


namespace AllegroFlare::LoadASavedGame::SaveSlots
{


void to_json(nlohmann::json& j, const Common& v)
{
   j = nlohmann::json{
      { "screenshot_of_gameplay_at_save_identifier", v.screenshot_of_gameplay_at_save_identifier },
      { "location_of_save", v.location_of_save},
      { "date_and_time_of_save", v.date_and_time_of_save },
      { "time_since_text", v.time_since_text },
   };
}

void from_json(const nlohmann::json& j, Common& v)
{
   j.at("screenshot_of_gameplay_at_save_identifier").get_to(v.screenshot_of_gameplay_at_save_identifier);
   j.at("location_of_save").get_to(v.location_of_save);
   j.at("date_and_time_of_save").get_to(v.date_and_time_of_save);
   j.at("time_since_text").get_to(v.time_since_text);
}


} // namespace AllegroFlare::LoadASavedGame::SaveSlots



