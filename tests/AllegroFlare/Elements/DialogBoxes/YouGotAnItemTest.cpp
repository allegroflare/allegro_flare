
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxes/YouGotAnItem.hpp>

TEST(AllegroFlare_Elements_DialogBoxes_YouGotAnItemTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxes::YouGotAnItem you_got_an_item;
}



TEST(AllegroFlare_Elements_DialogBoxes_YouGotAnItemTest, get_type__returns_the_expected_value)
{
   AllegroFlare::Elements::DialogBoxes::YouGotAnItem you_got_an_item;
   EXPECT_EQ("YouGotAnItem", you_got_an_item.get_type());
}

