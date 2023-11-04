
#include <gtest/gtest.h>

#include <AllegroFlare/LoadASavedGame/SaveSlots/Base.hpp>


class SaveSlotsBaseTestClass : public AllegroFlare::LoadASavedGame::SaveSlots::Base
{
public:
   SaveSlotsBaseTestClass()
      : AllegroFlare::LoadASavedGame::SaveSlots::Base("SaveSlotsBaseTestClass")
   {}
};


TEST(AllegroFlare_LoadASavedGame_SaveSlots_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::LoadASavedGame::SaveSlots::Base base;
}


TEST(AllegroFlare_LoadASavedGame_SaveSlots_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/LoadASavedGame/SaveSlots/Base",
     AllegroFlare::LoadASavedGame::SaveSlots::Base::TYPE
   );
}


TEST(AllegroFlare_LoadASavedGame_SaveSlots_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::LoadASavedGame::SaveSlots::Base base;
   EXPECT_EQ(AllegroFlare::LoadASavedGame::SaveSlots::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_LoadASavedGame_SaveSlots_BaseTest, derived_classes_will_have_the_expected_type)
{
   SaveSlotsBaseTestClass test_class;
   EXPECT_EQ("SaveSlotsBaseTestClass", test_class.get_type());
}


