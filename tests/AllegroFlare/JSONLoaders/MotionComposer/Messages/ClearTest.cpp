
#include <gtest/gtest.h>

#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/Clear.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/MotionComposer/Messages/Clear.hpp>


TEST(AllegroFlare_JSONLoaders_MotionComposer_Messages_ClearTest,
   to_json__returns_the_object_as_json_with_the_expected_values)
{
   AllegroFlare::MotionComposer::Messages::Clear clear;
   nlohmann::json j = clear;

   std::string expected_values = "null";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(AllegroFlare_JSONLoaders_MotionComposer_Messages_ClearTest,
   from_json__loads_json_data_into_the_object)
{
   AllegroFlare::MotionComposer::Messages::Clear clear;

   std::string json = R"({})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(clear);

   AllegroFlare::MotionComposer::Messages::Clear expected;

   EXPECT_EQ(expected,clear);
}



