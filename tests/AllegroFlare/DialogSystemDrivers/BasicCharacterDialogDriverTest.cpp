
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver.hpp>


TEST(AllegroFlare_DialogSystemDrivers_BasicCharacterDialogDriverTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver basic_character_dialog_driver;
}


TEST(AllegroFlare_DialogSystemDrivers_BasicCharacterDialogDriverTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver",
     AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE
   );
}


TEST(AllegroFlare_DialogSystemDrivers_BasicCharacterDialogDriverTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver basic_character_dialog_driver;
   EXPECT_EQ(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE, basic_character_dialog_driver.get_type());
}


TEST(AllegroFlare_DialogSystemDrivers_BasicCharacterDialogDriverTest,
   decorate_speaking_character_name__will_return_the_passed_argument_unmodified)
{
   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver basic_character_dialog_driver;
   std::string character_name = "JONAS";
   EXPECT_EQ(character_name, basic_character_dialog_driver.decorate_speaking_character_name(character_name));
}


