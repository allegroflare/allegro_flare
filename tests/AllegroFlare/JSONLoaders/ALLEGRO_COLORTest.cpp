
#include <gtest/gtest.h>

#include <AllegroFlare/JSONLoaders/ALLEGRO_COLOR.hpp>
#include <AllegroFlare/Testing/Comparison/ALLEGRO_COLOR.hpp>


TEST(AllegroFlare_JSONLoaders_ALLEGRO_COLORTest,
   to_json__returns_the_object_as_json_with_the_expected_values)
{
   ALLEGRO_COLOR allegro_color{0.25, 0.5, 0.75, 1.0};
   nlohmann::json j = allegro_color;

   std::string expected_values =
R"({
  "a": 1.0,
  "b": 0.75,
  "g": 0.5,
  "r": 0.25
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(AllegroFlare_JSONLoaders_ALLEGRO_COLORTest,
   from_json__loads_json_data_into_the_object)
{
   ALLEGRO_COLOR allegro_color;

   std::string json =
R"({
  "a": 1.0,
  "b": 0.75,
  "g": 0.5,
  "r": 0.25
})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(allegro_color);

   ALLEGRO_COLOR expected{0.25, 0.5, 0.75, 1.0};

   EXPECT_EQ(expected, allegro_color);
}



