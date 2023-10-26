
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/Scenes/Base.hpp>


class ScenesBaseTestClass : public AllegroFlare::DialogSystem::Scenes::Base
{
public:
   ScenesBaseTestClass()
      : AllegroFlare::DialogSystem::Scenes::Base("ScenesBaseTestClass")
   {}
};


TEST(AllegroFlare_DialogSystem_Scenes_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::Scenes::Base base;
}


TEST(AllegroFlare_DialogSystem_Scenes_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/Scenes/Base",
     AllegroFlare::DialogSystem::Scenes::Base::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_Scenes_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::Scenes::Base base;
   EXPECT_EQ(AllegroFlare::DialogSystem::Scenes::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_DialogSystem_Scenes_BaseTest, derived_classes_will_have_the_expected_type)
{
   ScenesBaseTestClass test_class;
   EXPECT_EQ("ScenesBaseTestClass", test_class.get_type());
}


