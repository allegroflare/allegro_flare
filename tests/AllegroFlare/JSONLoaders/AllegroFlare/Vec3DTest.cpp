
#include <gtest/gtest.h>

#include <AllegroFlare/JSONLoaders/AllegroFlare/Vec3D.hpp>


TEST(AllegroFlare_JSONLoaders_AllegroFlare_Vec3D, to_json__returns_vec3d_as_json_with_the_expected_values)
{
   // NOTE: these test floating point values were chosen because they are not represented
   // as long numbers when converted to outputs (e.g. "1.7f" would appear as "1.6999999...")
   AllegroFlare::Vec3D vec3d(3.5f, 7.0f, 1.625f);

   nlohmann::json j = vec3d;

   std::string expected_values =
R"({
  "x": 3.5,
  "y": 7.0,
  "z": 1.625
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(AllegroFlare_JSONLoaders_AllegroFlare_Vec3D, from_json__loads_json_data_into_a_vec3d)
{
   AllegroFlare::Vec3D vec3d;

   std::string json =
R"({
  "x": 2.34,
  "y": 5.8,
  "z": 2.0
})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);

   parsed_json.get_to(vec3d);

   EXPECT_EQ(2.34f, vec3d.x);
   EXPECT_EQ(5.8f, vec3d.y);
   EXPECT_EQ(2.0f, vec3d.z);
}



