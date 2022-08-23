
#include <gtest/gtest.h>

#include <AllegroFlare/JSONLoaders/AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>


TEST(AllegroFlare_JSONLoaders_AllegroFlare_MotionComposer_Messages_AddActor2DTest,
   to_json__returns_the_object_as_json_with_the_expected_values)
{
   AllegroFlare::MotionComposer::Messages::AddActor2D add_actor2d;
   nlohmann::json j = add_actor2d;

   std::string expected_values = "null";
R"({
  "position": 4.0
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(AllegroFlare_JSONLoaders_AllegroFlare_MotionComposer_Messages_AddActor2DTest,
   from_json__loads_json_data_into_the_object)
{
   AllegroFlare::MotionComposer::Messages::AddActor2D add_actor2d;

   std::string json =
R"({
  "position": 1.5
})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(add_actor2d);

   AllegroFlare::MotionComposer::Messages::AddActor2D expected;

   EXPECT_EQ(expected, add_actor2d);
}



