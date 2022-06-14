
#include <gtest/gtest.h>

#include <AllegroFlare/JSONLoaders/AllegroFlare/Camera3D.hpp>


TEST(AllegroFlare_JSONLoaders_AllegroFlare_Camera3DTest, can_be_created_without_blowing_up)
{
   //AllegroFlare::JSONLoaders::AllegroFlare::Camera3D camera3d;
}



TEST(AllegroFlare_JSONLoaders_AllegroFlare_Camera3D, to_json__produces_the_expected_json_for_position)
{
   // NOTE: these test floating point values were chosen because they are not represented
   // as long numbers when converted to outputs (e.g. "1.7f" would appear as "1.6999999...")
   AllegroFlare::Camera3D camera3d;
   camera3d.position = {3.5, 7.0, 1.625};

   nlohmann::json j = camera3d;

   std::string expected_position_values =
R"({
  "x": 3.5,
  "y": 7.0,
  "z": 1.625
})";

   std::string actual_position_values = j["position"].dump(2);
   EXPECT_EQ(expected_position_values, actual_position_values);
}



TEST(AllegroFlare_JSONLoaders_AllegroFlare_Vec3D, from_json__loads_json_data_into_a_vec3d)
{
   AllegroFlare::Camera3D camera3d;

   std::string json =
R"({
  "position": {
    "x": 2.34,
    "y": 5.8,
    "z": 2.0
  },
  "stepout": {
    "x": -2.0,
    "y": -5.0,
    "z": 0.0
  },
  "spin": 123.0,
  "tilt": 4.5,
  "zoom": 67.8
})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);

   parsed_json.get_to(camera3d);

   AllegroFlare::vec3d expected_position = {2.34, 5.8, 2.0};
   AllegroFlare::vec3d expected_stepout = {-2.0, -5.0, 0.0};  // TODO <- change these test values
   float expected_spin = 123.0f;
   float expected_tilt = 4.5f;
   float expected_zoom = 67.8f;

   EXPECT_EQ(expected_position, camera3d.position);
   EXPECT_EQ(expected_stepout, camera3d.stepout);
   EXPECT_EQ(expected_spin, camera3d.spin);
   EXPECT_EQ(expected_tilt, camera3d.tilt);
   EXPECT_EQ(expected_zoom, camera3d.zoom);
}



