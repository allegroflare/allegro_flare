
#include <gtest/gtest.h>

#include <AllegroFlare/JSONLoaders/AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec2D.hpp>


TEST(AllegroFlare_JSONLoaders_AllegroFlare_Vec2DTest,
   to_json__returns_the_object_as_json_with_the_expected_values)
{
   AllegroFlare::Vec2D vec2d(4.0f, 8.25f);
   nlohmann::json j = vec2d;

   std::string expected_values =
R"({
  "x": 4.0,
  "y": 8.25
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(AllegroFlare_JSONLoaders_AllegroFlare_Vec2DTest,
   from_json__loads_json_data_into_the_object)
{
   AllegroFlare::Vec2D vec2d;

   std::string json =
R"({
  "x": 4.0,
  "y": 8.25
})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(vec2d);

   AllegroFlare::Vec2D expected(4.0, 8.25);

   EXPECT_EQ(expected, vec2d);
}



