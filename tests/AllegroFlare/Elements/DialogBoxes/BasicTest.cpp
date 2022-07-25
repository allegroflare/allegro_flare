
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>

TEST(AllegroFlare_Elements_DialogBoxes_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxes::Basic basic;
}

TEST(AllegroFlare_Elements_DialogBoxes_BasicTest, get_type__returns_the_expected_value)
{
   AllegroFlare::Elements::DialogBoxes::Basic basic;
   EXPECT_EQ("Basic", basic.get_type());
}

