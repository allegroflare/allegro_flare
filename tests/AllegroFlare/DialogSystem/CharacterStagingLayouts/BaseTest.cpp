
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Base.hpp>


class CharacterStagingLayoutsBaseTestClass : public AllegroFlare::DialogSystem::CharacterStagingLayouts::Base
{
public:
   CharacterStagingLayoutsBaseTestClass()
      : AllegroFlare::DialogSystem::CharacterStagingLayouts::Base("CharacterStagingLayoutsBaseTestClass")
   {}
};


TEST(AllegroFlare_DialogSystem_CharacterStagingLayouts_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::CharacterStagingLayouts::Base base;
}


TEST(AllegroFlare_DialogSystem_CharacterStagingLayouts_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/CharacterStagingLayouts/Base",
     AllegroFlare::DialogSystem::CharacterStagingLayouts::Base::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_CharacterStagingLayouts_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::CharacterStagingLayouts::Base base;
   EXPECT_EQ(AllegroFlare::DialogSystem::CharacterStagingLayouts::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_DialogSystem_CharacterStagingLayouts_BaseTest, derived_classes_will_have_the_expected_type)
{
   CharacterStagingLayoutsBaseTestClass test_class;
   EXPECT_EQ("CharacterStagingLayoutsBaseTestClass", test_class.get_type());
}


