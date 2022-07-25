
#include <gtest/gtest.h>

#include <Krampus21/DialogBoxes/YouGotAnItem.hpp>

TEST(Krampus21_DialogBoxes_YouGotAnItemTest, can_be_created_without_blowing_up)
{
   Krampus21::DialogBoxes::YouGotAnItem you_got_an_item;
}



TEST(Krampus21_DialogBoxes_YouGotAnItemTest, get_type__returns_the_expected_value)
{
   Krampus21::DialogBoxes::YouGotAnItem you_got_an_item;
   EXPECT_EQ("YouGotAnItem", you_got_an_item.get_type());
}

