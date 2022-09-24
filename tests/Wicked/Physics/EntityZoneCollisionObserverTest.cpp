
#include <gtest/gtest.h>

#include <Wicked/Physics/EntityZoneCollisionObserver.hpp>
#include <Wicked/Entities/Zones/Rectangle3D.hpp>

using AllegroFlare::vec3d;


// TODO: fix tests and remove DISABLED so that they use actual entities


TEST(Wicked_Physics_EntityZoneCollisionObserverTest, can_be_created_without_blowing_up)
{
   Wicked::Physics::EntityZoneCollisionObserver entity_zone_collision_observer;
}

TEST(Wicked_Physics_EntityZoneCollisionObserverTest,
   get_collided__can_be_called_with_defaults_and_does_not_blow_up)
{
   Wicked::Physics::EntityZoneCollisionObserver entity_zone_collision_observer;
   entity_zone_collision_observer.get_collided();
   SUCCEED();
}

TEST(Wicked_Physics_EntityZoneCollisionObserverTest,
   get_collided__returns_entities_and_zones_that_are_colliding)
{
   std::vector<Wicked::Entities::Basic3D*> entities = {
      new Wicked::Entities::Basic3D(), //(nullptr, nullptr, "", { 0.5, 0.5, 0.5 })
   };
   std::vector<Wicked::Entities::Zones::Base3D*> zones = {
      new Wicked::Entities::Zones::Rectangle3D(0, 0, 0, 1, 1, 1),
   };
   entities[0]->get_place_ref().position = AllegroFlare::vec3d{ 0.5, 0.5, 0.5 };

   Wicked::Physics::EntityZoneCollisionObserver entity_zone_collision_observer;

   std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> expected_collided = {
      { entities[0], zones[0] },
   };
   std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> actual_collided =
      entity_zone_collision_observer.get_collided(entities, zones);

   ASSERT_EQ(expected_collided, actual_collided);

   for (auto &entity : entities) delete entity;
   for (auto &zone : zones) delete zone;
}


TEST(Wicked_Physics_EntityZoneCollisionObserverTest,
   get_collided__does_not_return_entities_and_zones_that_are_not_colliding)
{
   std::vector<Wicked::Entities::Basic3D*> entities = {
      new Wicked::Entities::Basic3D(), //(nullptr, nullptr, "", { 1.5, -1.5, 0.5 })
   };
   std::vector<Wicked::Entities::Zones::Base3D*> zones = {
      new Wicked::Entities::Zones::Rectangle3D(0, 0, 0, 1, 1, 1)
   };
   entities[0]->get_place_ref().position = AllegroFlare::vec3d{ 1.5, -1.5, 0.5 };

   Wicked::Physics::EntityZoneCollisionObserver entity_zone_collision_observer;

   std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> expected_collided = {};
   std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> actual_collided =
      entity_zone_collision_observer.get_collided(entities, zones);

   ASSERT_EQ(expected_collided, actual_collided);

   for (auto &entity : entities) delete entity;
   for (auto &zone : zones) delete zone;
}


TEST(Wicked_Physics_EntityZoneCollisionObserverTest,
   DISABLED__observe_start_state__will_store_collisions_for_the_passed_entities_and_zones__as_the_starting_state)
{
   std::vector<Wicked::Entities::Basic3D*> entities = {
      new Wicked::Entities::Basic3D(), //(nullptr, nullptr, "", { 0.5, 0.5, 0.5 })
   };
   std::vector<Wicked::Entities::Zones::Base3D*> zones = {
      new Wicked::Entities::Zones::Rectangle3D(0, 0, 0, 1, 1, 1)
   };
   entities[0]->get_place_ref().position = AllegroFlare::vec3d{ 0.5, 0.5, 0.5 };

   Wicked::Physics::EntityZoneCollisionObserver entity_zone_collision_observer;
   entity_zone_collision_observer.observe_start_state(entities, zones);

   std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> expected_collided = {
      { entities[0], zones[0] },
   };
   std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> actual_collided =
      entity_zone_collision_observer.get_collisions_at_start();

   ASSERT_EQ(expected_collided, actual_collided);

   for (auto &entity : entities) delete entity;
   for (auto &zone : zones) delete zone;
}


TEST(Wicked_Physics_EntityZoneCollisionObserverTest,
   observe_end_state__will_store_collisions_for_the_passed_entities_and_zones__as_the_ending_state)
{
   std::vector<Wicked::Entities::Basic3D*> entities = {
      new Wicked::Entities::Basic3D(), //(nullptr, nullptr, "", { 1.5, 1.5, 1.5 }),
      new Wicked::Entities::Basic3D(), //(nullptr, nullptr, "", { 0.5, 0.5, 0.5 }),
   };
   std::vector<Wicked::Entities::Zones::Base3D*> zones = {
      new Wicked::Entities::Zones::Rectangle3D(1, 1, 1, 2, 2, 2),
      new Wicked::Entities::Zones::Rectangle3D(0, 0, 0, 1, 1, 1),
   };
   entities[0]->get_place_ref().position = AllegroFlare::vec3d{ 1.5, 1.5, 1.5 };
   entities[1]->get_place_ref().position = AllegroFlare::vec3d{ 0.5, 0.5, 0.5 };

   Wicked::Physics::EntityZoneCollisionObserver entity_zone_collision_observer;
   entity_zone_collision_observer.observe_end_state(entities, zones);

   std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> expected_collided = {
      { entities[0], zones[0] },
      { entities[1], zones[1] },
   };
   std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> actual_collided =
      entity_zone_collision_observer.get_collisions_at_end();

   ASSERT_EQ(expected_collided, actual_collided);

   for (auto &entity : entities) delete entity;
   for (auto &zone : zones) delete zone;
}


TEST(Wicked_Physics_EntityZoneCollisionObserverTest,
   collisions_added__returns_the_new_collisions_that_occurred_between_the_start_and_end_state)
{
   std::vector<Wicked::Entities::Basic3D*> entities = {
      new Wicked::Entities::Basic3D(), //(nullptr, nullptr, "", { -0.5, -0.5, -0.5 }),
   };
   std::vector<Wicked::Entities::Zones::Base3D*> zones = {
      new Wicked::Entities::Zones::Rectangle3D(0, 0, 0, 1, 1, 1),
   };
   entities[0]->get_place_ref().position = AllegroFlare::vec3d{ -0.5, -0.5, -0.5 };

   Wicked::Physics::EntityZoneCollisionObserver entity_zone_collision_observer;
   entity_zone_collision_observer.observe_start_state(entities, zones);
   entities[0]->get_place_ref().position += AllegroFlare::vec3d{1.0, 1.0, 1.0};
   entity_zone_collision_observer.observe_end_state(entities, zones);

   std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> expected_collisions_added =
   {
      { entities[0], zones[0] },
   };
   std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> actual_collisions_added =
      entity_zone_collision_observer.collisions_added();

   ASSERT_EQ(expected_collisions_added, actual_collisions_added);

   for (auto &entity : entities) delete entity;
   for (auto &zone : zones) delete zone;
}


TEST(Wicked_Physics_EntityZoneCollisionObserverTest,
   collisions_removed__returns_the_new_collisions_that_occurred_between_the_start_and_end_state)
{
   std::vector<Wicked::Entities::Basic3D*> entities = {
      new Wicked::Entities::Basic3D(), //(nullptr, nullptr, "", { 0.5, 0.5, 0.5 }),
   };
   std::vector<Wicked::Entities::Zones::Base3D*> zones = {
      new Wicked::Entities::Zones::Rectangle3D(0, 0, 0, 1, 1, 1),
   };
   entities[0]->get_place_ref().position = AllegroFlare::vec3d{ 0.5, 0.5, 0.5 };

   Wicked::Physics::EntityZoneCollisionObserver entity_zone_collision_observer;
   entity_zone_collision_observer.observe_start_state(entities, zones);
   entities[0]->get_place_ref().position += vec3d(1.0, 1.0, 1.0);
   entity_zone_collision_observer.observe_end_state(entities, zones);

   std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> expected_collisions_removed=
   {
      { entities[0], zones[0] },
   };
   std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> actual_collisions_removed =
      entity_zone_collision_observer.collisions_removed();

   ASSERT_EQ(expected_collisions_removed, actual_collisions_removed);

   for (auto &entity : entities) delete entity;
   for (auto &zone : zones) delete zone;
}


TEST(Wicked_Physics_EntityZoneCollisionObserverTest, complex_example)
{
   typedef std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> t;

   std::vector<Wicked::Entities::Basic3D*> entities = {
      new Wicked::Entities::Basic3D(), //(nullptr, nullptr, "", { 0.5, 0.5, 0.5 }),
   };
   std::vector<Wicked::Entities::Zones::Base3D*> zones = {
      new Wicked::Entities::Zones::Rectangle3D(0, 0, 0, 1, 1, 1),
      new Wicked::Entities::Zones::Rectangle3D(1, 1, 1, 2, 2, 2),
   };
   entities[0]->get_place_ref().position = AllegroFlare::vec3d{ 0.5, 0.5, 0.5 };

   Wicked::Physics::EntityZoneCollisionObserver entity_zone_collision_observer;
   // observe the "before" state
   entity_zone_collision_observer.observe_start_state(entities, zones);

   // change the state of the world
   entities[0]->get_place_ref().position += vec3d(1.0, 1.0, 1.0);

   // observe the "after" state
   entity_zone_collision_observer.observe_end_state(entities, zones);

   // check our expectations
   t expected_collisions_added = { { entities[0], zones[1] } };
   t actual_collisions_added = entity_zone_collision_observer.collisions_added();
   t expected_collisions_removed = { { entities[0], zones[0] }, };
   t actual_collisions_removed = entity_zone_collision_observer.collisions_removed();

   ASSERT_EQ(expected_collisions_added, actual_collisions_added);
   ASSERT_EQ(expected_collisions_removed, actual_collisions_removed);

   for (auto &entity : entities) delete entity;
   for (auto &zone : zones) delete zone;
}


