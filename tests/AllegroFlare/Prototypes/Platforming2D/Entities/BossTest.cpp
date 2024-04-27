
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/Platforming2D/Entities/Boss.hpp>


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_BossTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Boss boss;
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_BossTest, DISABLED__TYPE__has_the_expected_value)
{
   // TODO: Fix this test
   EXPECT_STREQ(
     "AllegroFlare/Prototypes/Platforming2D/Entities/Boss",
     AllegroFlare::Prototypes::Platforming2D::Entities::Boss::TYPE
   );
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_BossTest, DISABLED__type__has_the_expected_value_matching_TYPE)
{
   // TODO: Fix this test
   AllegroFlare::Prototypes::Platforming2D::Entities::Boss boss;
   EXPECT_EQ(AllegroFlare::Prototypes::Platforming2D::Entities::Boss::TYPE, boss.get_type());
}


