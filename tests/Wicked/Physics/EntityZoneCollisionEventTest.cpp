
#include <gtest/gtest.h>

#include <Wicked/Physics/EntityZoneCollisionEvent.hpp>


TEST(Wicked_Physics_EntityZoneCollisionEventTest, can_be_created_without_blowing_up)
{
   Wicked::Physics::EntityZoneCollisionEvent entity_zone_collision_event2d;
}


TEST(LabyrinthOfLore_Physics_EntityZoneCollisionEventTest, has_expected_getters_with_expected_defaults)
{
   Wicked::Physics::EntityZoneCollisionEvent entity_zone_collision_event2d;
   EXPECT_EQ(-1, entity_zone_collision_event2d.get_zone_id());
   EXPECT_EQ(nullptr, entity_zone_collision_event2d.get_entity());
   EXPECT_EQ(Wicked::Physics::COLLISION_EVENT_NONE, entity_zone_collision_event2d.get_event_type());
}


