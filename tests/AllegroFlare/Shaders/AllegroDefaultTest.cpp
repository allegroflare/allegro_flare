
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/AllegroDefault.hpp>


TEST(AllegroFlare_Shaders_AllegroDefaultTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shaders::AllegroDefault allegro_default;
}


TEST(AllegroFlare_Shaders_AllegroDefaultTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Shaders::AllegroDefault shader;
   EXPECT_EQ("AllegroFlare/Shaders/AllegroDefault", shader.get_type());
}


TEST(AllegroFlare_Shaders_AllegroDefaultTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Shaders::AllegroDefault shader;
   EXPECT_EQ(AllegroFlare::Shaders::AllegroDefault::TYPE, shader.get_type());
}


