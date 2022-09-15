
#include <gtest/gtest.h>

#include <Wicked/Entities/Zones/Rectangle2D.hpp>

using AllegroFlare::vec2d;
static const float FLOAT_THRESHOLD = 0.00001f;

TEST(Wicked_Entities_Zones_Rectangle2DTest, can_be_created_without_blowing_up)
{
   Wicked::Entities::Zones::Rectangle2D zone;
}

TEST(Wicked_Entities_Zones_Rectangle2DTest, has_expected_getters_with_expected_default_values)
{
   Wicked::Entities::Zones::Rectangle2D zone;
   EXPECT_EQ(0.0, zone.get_x1());
   EXPECT_EQ(0.0, zone.get_y1());
   EXPECT_EQ(1.0, zone.get_x2());
   EXPECT_EQ(1.0, zone.get_y2());
}

TEST(Wicked_Entities_Zones_Rectangle2DTest, assigns_values_in_the_expected_order_during_construction)
{
   Wicked::Entities::Zones::Rectangle2D zone(1.3, 2.2, 4.0, 5.9);
   EXPECT_NEAR(1.3, zone.get_x1(), FLOAT_THRESHOLD);
   EXPECT_NEAR(2.2, zone.get_y1(), FLOAT_THRESHOLD);
   EXPECT_NEAR(4.0, zone.get_x2(), FLOAT_THRESHOLD);
   EXPECT_NEAR(5.9, zone.get_y2(), FLOAT_THRESHOLD);
}

TEST(Wicked_Entities_Zones_Rectangle2DTest, collides__returns_true_when_the_point_lies_inside_the_zone)
{
   Wicked::Entities::Zones::Rectangle2D zone;
   vec2d point(0.2, 0.5);
   EXPECT_EQ(true, zone.collides(point));
}

TEST(Wicked_Entities_Zones_Rectangle2DTest, collides__returns_false_when_the_point_lies_outside_the_zone_to_the_right)
{
   Wicked::Entities::Zones::Rectangle2D zone;
   vec2d point(0.2+1.0, 0.5);
   EXPECT_EQ(false, zone.collides(point));
}

TEST(Wicked_Entities_Zones_Rectangle2DTest, collides__returns_false_when_the_point_lies_inside_the_zone_to_the_left)
{
   Wicked::Entities::Zones::Rectangle2D zone;
   vec2d point(0.2-1.0, 0.5);
   EXPECT_EQ(false, zone.collides(point));
}

TEST(Wicked_Entities_Zones_Rectangle2DTest, collides__returns_false_when_the_point_lies_outside_the_zone_to_the_back)
{
   Wicked::Entities::Zones::Rectangle2D zone;
   vec2d point(0.2, 0.5+1.0);
   EXPECT_EQ(false, zone.collides(point));
}

TEST(Wicked_Entities_Zones_Rectangle2DTest, collides__returns_false_when_the_point_lies_inside_the_zone_to_the_front)
{
   Wicked::Entities::Zones::Rectangle2D zone;
   vec2d point(0.2, 0.5-1.0);
   EXPECT_EQ(false, zone.collides(point));
}


