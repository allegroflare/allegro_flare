
#include <gtest/gtest.h>

#include <AllegroFlare/JSONLoaders/AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>


TEST(AllegroFlare_JSONLoaders_AllegroFlare_MotionComposer_Messages_AddActor2DTest,
   to_json__returns_the_object_as_json_with_the_expected_values)
{
   AllegroFlare::MotionComposer::Messages::AddActor2D add_actor2d("actor32", "a-bitmap.png", "script-lines");
   nlohmann::json j = add_actor2d;

   std::string expected_values =
R"({
  "bitmap_identifier": "a-bitmap.png",
  "identifier": "actor32",
  "script": "script-lines"
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(AllegroFlare_JSONLoaders_AllegroFlare_MotionComposer_Messages_AddActor2DTest,
   from_json__loads_json_data_into_the_object)
{
   std::string json =
R"({
  "bitmap_identifier": "a-bitmap.png",
  "identifier": "actor567",
  "script": "foobar-script"
})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);

   AllegroFlare::MotionComposer::Messages::AddActor2D expected("actor567", "a-bitmap.png", "foobar-script");
   AllegroFlare::MotionComposer::Messages::AddActor2D actual;
   parsed_json.get_to(actual);

   EXPECT_EQ(expected, actual);
}



