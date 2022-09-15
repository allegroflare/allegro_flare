
#include <gtest/gtest.h>

#include <Wicked/Entities/Zones/Base3D.hpp>


TEST(Wicked_Entities_Zones_Base3DTest, can_be_created_without_blowing_up)
{
   Wicked::Entities::Zones::Base3D base;
}


TEST(Wicked_Entities_Zones_Base3DTest, collides__by_default_returns_false)
{
   Wicked::Entities::Zones::Base3D base;
   EXPECT_EQ(false, base.collides());
}


