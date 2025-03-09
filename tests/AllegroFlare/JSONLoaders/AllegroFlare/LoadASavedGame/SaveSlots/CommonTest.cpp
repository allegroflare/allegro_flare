
#include <gtest/gtest.h>

#include <AllegroFlare/JSONLoaders/AllegroFlare/LoadASavedGame/SaveSlots/Common.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/LoadASavedGame/SaveSlots/Common.hpp>


TEST(AllegroFlare_JSONLoaders_AllegroFlare_LoadASavedGame_SaveSlots_CommonTest,
   to_json__returns_the_object_as_json_with_the_expected_values)
{
   AllegroFlare::LoadASavedGame::SaveSlots::Common save_slot;
   save_slot.screenshot_of_gameplay_at_save_identifier = "slot_1_screenshot-01.jpg";
   save_slot.location_of_save = "The Front Room";
   save_slot.date_and_time_of_save = "2025/03/08 6:45PM";
   save_slot.time_since_text = "28 minutes ago";

   nlohmann::json j = save_slot;

   std::string expected_values =
R"({
  "date_and_time_of_save": "2025/03/08 6:45PM",
  "location_of_save": "The Front Room",
  "screenshot_of_gameplay_at_save_identifier": "slot_1_screenshot-01.jpg",
  "time_since_text": "28 minutes ago"
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(AllegroFlare_JSONLoaders_AllegroFlare_LoadASavedGame_SaveSlots_CommonTest,
   from_json__loads_json_data_into_the_object)
{
   std::string json =
R"({
  "date_and_time_of_save": "2025/03/08 6:45PM",
  "location_of_save": "The Front Room",
  "screenshot_of_gameplay_at_save_identifier": "slot_1_screenshot-01.jpg",
  "time_since_text": "28 minutes ago"
})";

   AllegroFlare::LoadASavedGame::SaveSlots::Common actual;
   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(actual);

   AllegroFlare::LoadASavedGame::SaveSlots::Common expected;
   expected.screenshot_of_gameplay_at_save_identifier = "slot_1_screenshot-01.jpg";
   expected.location_of_save = "The Front Room";
   expected.date_and_time_of_save = "2025/03/08 6:45PM";
   expected.time_since_text = "28 minutes ago";

   EXPECT_EQ(expected, actual);
}



