
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
   camera2d.scale = { 0.5, 0.25 }; // NOTE: These values will be overridden by the values calculated from "set_zoom"
   camera2d.anchor = { -0.5, -0.25 };
   camera2d.flip = { true, false };
   camera2d.rotation = 0.125;
   camera2d.set_width_num_units(456);
   camera2d.set_height_num_units(789);
   camera2d.set_zoom({ 1.0, 2.0 });

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
    "x": true,
    "y": false
  },
  "height_num_units": 789,
  "position": {
    "x": 1.0,
    "y": 2.0
  },
  "rotation": 0.125,
  "scale": {
    "x": 1.0,
    "y": 0.5
  },
  "size": {
    "x": 4.0,
    "y": 8.0
  },
  "width_num_units": 456,
  "zoom": {
    "x": 1.0,
    "y": 2.0
  }
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(AllegroFlare_JSONLoaders_AllegroFlare_Camera2DTest,
   from_json__loads_json_data_into_the_object)
{
   AllegroFlare::Camera2D camera2d;

   std::string json =
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
    "x": true,
    "y": false
  },
  "height_num_units": 456,
  "position": {
    "x": 1.0,
    "y": 2.0
  },
  "rotation": 0.125,
  "scale": {
    "x": 1.0,
    "y": 0.5
  },
  "size": {
    "x": 4.0,
    "y": 8.0
  },
  "width_num_units": 789,
  "zoom": {
    "x": 1.0,
    "y": 2.0
  }
})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(camera2d);

   AllegroFlare::Camera2D expected_camera2d;
   expected_camera2d.position = { 1.0, 2.0 };
   expected_camera2d.size = { 4.0, 8.0 };
   expected_camera2d.align = { 16.0, 32.0 };
   expected_camera2d.scale = { 1.0, 0.5 };
   expected_camera2d.anchor = { -0.5, -0.25 };
   expected_camera2d.flip = { true, false };
   expected_camera2d.rotation = 0.125;
   expected_camera2d.set_width_num_units(789);
   expected_camera2d.set_height_num_units(456);

   // TODO: Add comparison operator for Camera2D and use in this test
   EXPECT_EQ(expected_camera2d.position, camera2d.position);
   EXPECT_EQ(expected_camera2d.size, camera2d.size);
   EXPECT_EQ(expected_camera2d.align, camera2d.align);
   EXPECT_EQ(expected_camera2d.scale, camera2d.scale);
   EXPECT_EQ(expected_camera2d.anchor, camera2d.anchor);
   EXPECT_EQ(expected_camera2d.flip.get_x(), camera2d.flip.get_x());
   EXPECT_EQ(expected_camera2d.flip.get_y(), camera2d.flip.get_y());
   EXPECT_EQ(expected_camera2d.rotation, camera2d.rotation);
   EXPECT_EQ(expected_camera2d.get_width_num_units(), camera2d.get_width_num_units());
   EXPECT_EQ(expected_camera2d.get_height_num_units(), camera2d.get_height_num_units());
}



