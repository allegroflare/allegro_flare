
#include <gtest/gtest.h>

#include <Krampus21/DialogBoxes/Basic.hpp>

TEST(Krampus21_DialogBoxes_BasicTest, can_be_created_without_blowing_up)
{
   Krampus21::DialogBoxes::Basic basic;
}

TEST(Krampus21_DialogBoxes_BasicTest, get_type__returns_the_expected_value)
{
   Krampus21::DialogBoxes::Basic basic;
   EXPECT_EQ("Basic", basic.get_type());
}

