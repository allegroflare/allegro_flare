
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d;
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d;
   EXPECT_EQ("Entities/Basic2D", basic2d.get_type());
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d;
   EXPECT_EQ(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::TYPE, basic2d.get_type());
}


