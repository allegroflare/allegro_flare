
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/Characters/Base.hpp>


class CharactersBaseTestClass : public AllegroFlare::DialogSystem::Characters::Base
{
public:
   CharactersBaseTestClass()
      : AllegroFlare::DialogSystem::Characters::Base("CharactersBaseTestClass")
   {}
};


TEST(AllegroFlare_DialogSystem_Characters_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::Characters::Base base;
}


TEST(AllegroFlare_DialogSystem_Characters_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/Characters/Base",
     AllegroFlare::DialogSystem::Characters::Base::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_Characters_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::Characters::Base base;
   EXPECT_EQ(AllegroFlare::DialogSystem::Characters::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_DialogSystem_Characters_BaseTest, derived_classes_will_have_the_expected_type)
{
   CharactersBaseTestClass test_class;
   EXPECT_EQ("CharactersBaseTestClass", test_class.get_type());
}


