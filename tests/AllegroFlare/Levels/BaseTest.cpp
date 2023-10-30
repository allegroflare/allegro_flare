
#include <gtest/gtest.h>

#include <AllegroFlare/Levels/Base.hpp>


class LevelsBaseTestClass : public AllegroFlare::Levels::Base
{
public:
   LevelsBaseTestClass()
      : AllegroFlare::Levels::Base("LevelsBaseTestClass")
   {}
};


TEST(AllegroFlare_Levels_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Levels::Base base;
}


TEST(AllegroFlare_Levels_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Levels/Base",
     AllegroFlare::Levels::Base::TYPE
   );
}


TEST(AllegroFlare_Levels_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Levels::Base base;
   EXPECT_EQ(AllegroFlare::Levels::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_Levels_BaseTest, derived_classes_will_have_the_expected_type)
{
   LevelsBaseTestClass test_class;
   EXPECT_EQ("LevelsBaseTestClass", test_class.get_type());
}


