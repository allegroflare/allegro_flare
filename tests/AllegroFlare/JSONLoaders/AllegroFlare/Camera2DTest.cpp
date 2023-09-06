
#include <gtest/gtest.h>

#include <AllegroFlare/JSONLoaders/AllegroFlare/Camera2D.hpp>
//#include <AllegroFlare/Testing/Comparison/AllegroFlare/JSONLoaders/AllegroFlare/Camera2D.hpp>


TEST(AllegroFlare_JSONLoaders_AllegroFlare_Camera2DTest,
   to_json__returns_the_object_as_json_with_the_expected_values)
{
   AllegroFlare::Camera2D camera2d;

   camera2d.position = { 1.0, 2.0 };
   camera2d.size = { 4.0, 8.0 };
   camera2d.align = { 16.0, 32.0 };
   camera2d.scale = { 0.5, 0.25 };
   camera2d.anchor = { -0.5, -0.25 };
   camera2d.flip = { true, false };
   camera2d.rotation = 0.125;

   nlohmann::json j = camera2d;

   std::string expected_values =
R"({
  "align": {
    "x": 16.0,
    "y": 32.0
  },
  "anchor": {
    "x": -0.5,
    "y": -0.25
  },
  "flip": {
    "x": -0.5,
    "y": -0.25
  },
  "position": {
    "x": 1.0,
    "y": 2.0
  },
  "rotation": 0.125,
  "scale": {
    "x": 0.5,
    "y": 0.25
  },
  "size": {
    "x": 4.0,
    "y": 8.0
  }
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(AllegroFlare_JSONLoaders_AllegroFlare_Camera2DTest,
   from_json__loads_json_data_into_the_object)
{
   //AllegroFlare::Camera2D camera2d;

   //std::string json =
//R"({
  //"position": 1.5
//})";

   //nlohmann::json parsed_json = nlohmann::json::parse(json);
   //parsed_json.get_to(camera2d);

   //AllegroFlare::JSONLoaders::AllegroFlare::Camera2D expected(1.5);

   //// TODO: add comparison
   //EXPECT_EQ(expected, camera2d);
}



