
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/Chapters/Base.hpp>


class ChaptersBaseTestClass : public AllegroFlare::DialogSystem::Chapters::Base
{
public:
   ChaptersBaseTestClass()
      : AllegroFlare::DialogSystem::Chapters::Base("ChaptersBaseTestClass")
   {}
};


TEST(AllegroFlare_DialogSystem_Chapters_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::Chapters::Base base;
}


TEST(AllegroFlare_DialogSystem_Chapters_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/Chapters/Base",
     AllegroFlare::DialogSystem::Chapters::Base::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_Chapters_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::Chapters::Base base;
   EXPECT_EQ(AllegroFlare::DialogSystem::Chapters::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_DialogSystem_Chapters_BaseTest, derived_classes_will_have_the_expected_type)
{
   ChaptersBaseTestClass test_class;
   EXPECT_EQ("ChaptersBaseTestClass", test_class.get_type());
}


