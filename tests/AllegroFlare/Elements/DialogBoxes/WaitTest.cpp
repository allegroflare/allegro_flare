
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxes/Wait.hpp>


TEST(AllegroFlare_Elements_DialogBoxes_WaitTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxes::Wait wait;
}


TEST(AllegroFlare_Elements_DialogBoxes_WaitTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/DialogBoxes/Wait",
     AllegroFlare::Elements::DialogBoxes::Wait::TYPE
   );
}


TEST(AllegroFlare_Elements_DialogBoxes_WaitTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::DialogBoxes::Wait wait;
   EXPECT_EQ(AllegroFlare::Elements::DialogBoxes::Wait::TYPE, wait.get_type());
}


