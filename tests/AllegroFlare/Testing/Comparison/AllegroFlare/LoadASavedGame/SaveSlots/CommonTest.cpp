
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/LoadASavedGame/SaveSlots/Common.hpp>


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_LoadASavedGame_SaveSlots_CommonTest,
   PrintTo__with_an_AllegroFlare_Common__will_output_as_expected)
{
   std::stringstream ss;
   AllegroFlare::LoadASavedGame::SaveSlots::Common object;

   PrintTo(object, &ss);

   std::string expected_output = "AllegroFlare::LoadASavedGame::SaveSlots::Common("
      "\"screenshot_of_gameplay_at_save_identifier\": \"" + object.screenshot_of_gameplay_at_save_identifier + "\", "
      "\"location_of_save\": \"" + object.location_of_save + "\", "
      "\"date_and_time_of_save\": \"" + object.date_and_time_of_save + "\", "
      "\"save_time__seconds_since_epoch\": \"0\", "
      "\"time_since_text\": \"" + object.time_since_text + "\", "
      ")";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_LoadASavedGame_SaveSlots_CommonTest,
   equality_operator__works_with_google_test_EXPECT_statement)
{
   AllegroFlare::LoadASavedGame::SaveSlots::Common object;
   AllegroFlare::LoadASavedGame::SaveSlots::Common other_object;

   EXPECT_EQ(object, other_object);
}


