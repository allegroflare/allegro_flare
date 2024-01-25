
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/Backgrounds/Basic3D.hpp>


TEST(AllegroFlare_Elements_Backgrounds_Basic3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Backgrounds::Basic3D basic3d;
}


TEST(AllegroFlare_Elements_Backgrounds_Basic3DTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/Backgrounds/Basic3D",
     AllegroFlare::Elements::Backgrounds::Basic3D::TYPE
   );
}


TEST(AllegroFlare_Elements_Backgrounds_Basic3DTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::Backgrounds::Basic3D basic3d;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::Basic3D::TYPE, basic3d.get_type());
}


