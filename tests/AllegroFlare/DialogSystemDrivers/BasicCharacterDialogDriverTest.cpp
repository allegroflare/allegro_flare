
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
   EXPECT_EQ(
      AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE,
      basic_character_dialog_driver.get_type()
   );
}


TEST(AllegroFlare_DialogSystemDrivers_BasicCharacterDialogDriverTest,
   decorate_speaking_character_name__when_a_handle_decorate_speaking_character_name_func_is_present__\
will_return_the_passed_argument_unmodified)
{
   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver basic_character_dialog_driver;
   std::string character_identifier = "JONAS";
   std::string expected_decorated_character_name = character_identifier;
   EXPECT_EQ(
      expected_decorated_character_name,
      basic_character_dialog_driver.decorate_speaking_character_name(character_identifier)
   );
}


TEST(AllegroFlare_DialogSystemDrivers_BasicCharacterDialogDriverTest,
   decorate_speaking_character_name__will_return_the_passed_argument_unmodified)
{
   std::string character_identifier = "JONAS";
   int call_count = 0;
   std::function<std::string(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*, std::string, void*)>
      my_func = [](AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver* d, std::string s, void* i) -> std::string {
         (*(int*)(i))++;
         if (s == "JONAS") return "Jonas";
         return "[decoration-for-character-identifier-not-found]";
      };

   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver basic_character_dialog_driver;
   basic_character_dialog_driver.set_handle_decorate_speaking_character_name_func(
      my_func
   );
   basic_character_dialog_driver.set_handle_decorate_speaking_character_name_func_user_data(&call_count);

   std::string expected_decorated_character_name = "Jonas";
   EXPECT_EQ(
      expected_decorated_character_name,
      basic_character_dialog_driver.decorate_speaking_character_name(character_identifier)
   );
   EXPECT_EQ(1, call_count);
}


