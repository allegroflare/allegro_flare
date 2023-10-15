
#include <gtest/gtest.h>

#include <AllegroFlare/GameProgressAndStateInfos/Base.hpp>


class GameProgressAndStateInfosBaseTestClass : public AllegroFlare::GameProgressAndStateInfos::Base
{
public:
   GameProgressAndStateInfosBaseTestClass()
      : AllegroFlare::GameProgressAndStateInfos::Base("GameProgressAndStateInfosBaseTestClass")
   {}
};


TEST(AllegroFlare_GameProgressAndStateInfos_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GameProgressAndStateInfos::Base base;
}


TEST(AllegroFlare_GameProgressAndStateInfos_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/GameProgressAndStateInfos/Base",
     AllegroFlare::GameProgressAndStateInfos::Base::TYPE
   );
}


TEST(AllegroFlare_GameProgressAndStateInfos_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GameProgressAndStateInfos::Base base;
   EXPECT_EQ(AllegroFlare::GameProgressAndStateInfos::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_GameProgressAndStateInfos_BaseTest, derived_classes_will_have_the_expected_type)
{
   GameProgressAndStateInfosBaseTestClass test_class;
   EXPECT_EQ("GameProgressAndStateInfosBaseTestClass", test_class.get_type());
}


