
#include <gtest/gtest.h>

#include <AllegroFlare/JSONLoaders/AllegroFlare/Vec2B.hpp>
//#include <AllegroFlare/Testing/Comparison/AllegroFlare/JSONLoaders/AllegroFlare/Vec2B.hpp>


TEST(AllegroFlare_JSONLoaders_AllegroFlare_Vec2BTest,
   to_json__returns_the_object_as_json_with_the_expected_values)
{
   AllegroFlare::Vec2B vec2b(true, false);
   nlohmann::json j = vec2b;

   std::string expected_values =
R"({
  "x": true,
  "y": false
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(AllegroFlare_JSONLoaders_AllegroFlare_Vec2BTest,
   from_json__loads_json_data_into_the_object)
{
   AllegroFlare::Vec2B vec2b;

   std::string json =
R"({
  "x": true,
  "y": false
})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(vec2b);

   AllegroFlare::Vec2B expected(true);

   // TODO: Add/use comparison operators on the Vec2B class and use here
   EXPECT_EQ(expected.get_x(), vec2b.get_x());
   EXPECT_EQ(expected.get_y(), vec2b.get_y());
}


