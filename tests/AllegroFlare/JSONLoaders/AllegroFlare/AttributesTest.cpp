
#include <gtest/gtest.h>

#include <AllegroFlare/JSONLoaders/AllegroFlare/Attributes.hpp>


TEST(AllegroFlare_JSONLoaders_AllegroFlare_Attributes, to_json__returns_Attributes_as_json_with_the_expected_values)
{
   AllegroFlare::Attributes attributes;

   nlohmann::json j = attributes;

   std::string expected_values = "null";
//R"({
  //"x": 3.5,
  //"y": 7.0,
  //"z": 1.625
//})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(AllegroFlare_JSONLoaders_AllegroFlare_Attributes, from_json__loads_json_data_into_Attributes)
{
   AllegroFlare::Attributes attributes;

   std::string json = "{}";
//R"({
  //"x": 2.34,
  //"y": 5.8,
  //"z": 2.0
//})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(attributes);

   AllegroFlare::Attributes expected_attributes;

   EXPECT_EQ(expected_attributes, attributes);
}



