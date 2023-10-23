
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystemDrivers/Base.hpp>


class DialogSystemDriversBaseTestClass : public AllegroFlare::DialogSystemDrivers::Base
{
public:
   DialogSystemDriversBaseTestClass()
      : AllegroFlare::DialogSystemDrivers::Base("DialogSystemDriversBaseTestClass")
   {}
};


TEST(AllegroFlare_DialogSystemDrivers_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystemDrivers::Base base;
}


TEST(AllegroFlare_DialogSystemDrivers_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystemDrivers/Base",
     AllegroFlare::DialogSystemDrivers::Base::TYPE
   );
}


TEST(AllegroFlare_DialogSystemDrivers_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystemDrivers::Base base;
   EXPECT_EQ(AllegroFlare::DialogSystemDrivers::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_DialogSystemDrivers_BaseTest, derived_classes_will_have_the_expected_type)
{
   DialogSystemDriversBaseTestClass test_class;
   EXPECT_EQ("DialogSystemDriversBaseTestClass", test_class.get_type());
}


