
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/Platforming2D/Entities/BossZone.hpp>


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_BossZoneTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::BossZone boss_zone;
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_BossZoneTest, DISABLED__TYPE__has_the_expected_value)
{
   // TODO: Fix this test
   EXPECT_STREQ(
     "AllegroFlare/Prototypes/Platforming2D/Entities/BossZone",
     AllegroFlare::Prototypes::Platforming2D::Entities::BossZone::TYPE
   );
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_BossZoneTest, DISABLED__type__has_the_expected_value_matching_TYPE)
{
   // TODO: Fix this test
   AllegroFlare::Prototypes::Platforming2D::Entities::BossZone boss_zone;
   EXPECT_EQ(AllegroFlare::Prototypes::Platforming2D::Entities::BossZone::TYPE, boss_zone.get_type());
}


