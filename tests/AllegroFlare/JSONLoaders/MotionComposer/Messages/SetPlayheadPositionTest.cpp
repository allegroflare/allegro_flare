
#include <gtest/gtest.h>

#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/SetPlayheadPosition.hpp>


TEST(AllegroFlare_JSONLoaders_MotionComposer_Messages_SetPlayheadPositionTest,
   to_json__returns_vec3d_as_json_with_the_expected_values)
{
   AllegroFlare::MotionComposer::Messages::SetPlayheadPosition set_playhead_position(4.0f);

   nlohmann::json j = set_playhead_position;

   std::string expected_values =
R"({
  "position": 4.0
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(AllegroFlare_JSONLoaders_MotionComposer_Messages_SetPlayheadPositionTest,
   from_json__loads_json_data_into_a_vec3d)
{
   AllegroFlare::MotionComposer::Messages::SetPlayheadPosition set_playhead_position;

   std::string json =
R"({
  "position": 1.5
})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(set_playhead_position);

   AllegroFlare::MotionComposer::Messages::SetPlayheadPosition expected(1.5);

   // TODO: add comparison
   //EXPECT_EQ(expected, set_playhead_position);
}



