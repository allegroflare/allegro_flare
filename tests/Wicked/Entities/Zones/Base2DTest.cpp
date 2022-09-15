
#include <gtest/gtest.h>

#include <Wicked/Entities/Zones/Base2D.hpp>


TEST(Wicked_Entities_Zones_Base2DTest, can_be_created_without_blowing_up)
{
   Wicked::Entities::Zones::Base2D base2d_zone;
}


TEST(Wicked_Entities_Zones_Base2DTest, collides__by_default_returns_false)
{
   Wicked::Entities::Zones::Base2D base2d_zone;
   EXPECT_EQ(false, base2d_zone.collides());
}


