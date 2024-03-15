
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/Subscreen/Panes/Base.hpp>


class PanesBaseTestClass : public AllegroFlare::Screens::Subscreen::Panes::Base
{
public:
   PanesBaseTestClass()
      : AllegroFlare::Screens::Subscreen::Panes::Base("PanesBaseTestClass")
   {}
};


TEST(AllegroFlare_Screens_Subscreen_Panes_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Subscreen::Panes::Base base;
}


TEST(AllegroFlare_Screens_Subscreen_Panes_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Screens/Subscreen/Panes/Base",
     AllegroFlare::Screens::Subscreen::Panes::Base::TYPE
   );
}


TEST(AllegroFlare_Screens_Subscreen_Panes_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Screens::Subscreen::Panes::Base base;
   EXPECT_EQ(AllegroFlare::Screens::Subscreen::Panes::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_Screens_Subscreen_Panes_BaseTest, derived_classes_will_have_the_expected_type)
{
   PanesBaseTestClass test_class;
   EXPECT_EQ("PanesBaseTestClass", test_class.get_type());
}


