
#include <gtest/gtest.h>

#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/TogglePlayback.hpp>



TEST(AllegroFlare_JSONLoaders_MotionComposer_Messages_TogglePlaybackTest,
   to_json__returns_the_object_as_json_with_the_expected_values)
{
   AllegroFlare::MotionComposer::Messages::TogglePlayback toggle_playback;
   nlohmann::json j = toggle_playback;

   std::string expected_values = "null";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(AllegroFlare_JSONLoaders_MotionComposer_Messages_TogglePlaybackTest,
   from_json__loads_json_data_into_the_object)
{
   AllegroFlare::MotionComposer::Messages::TogglePlayback toggle_playback;

   std::string json = "{}";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(toggle_playback);

   AllegroFlare::MotionComposer::Messages::TogglePlayback expected;

   // TODO: add comparison
   //EXPECT_EQ(expected, toggle_playback);
}



