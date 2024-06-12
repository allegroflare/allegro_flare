
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/HoppingLeft.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/EntityFlagNames.hpp>


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_HoppingLeftTest,
   can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::HoppingLeft strategy;
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_HoppingLeftTest,
   update__without_an_entity__throws_an_error)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::HoppingLeft strategy;
   std::string expected_error_message = "HoppingLeft::update: error: guard \"entity\" not met";
   EXPECT_THROW_WITH_MESSAGE(strategy.update(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_HoppingLeftTest,
   jump_force__has_the_expected_default_value)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::HoppingLeft strategy;
   ASSERT_EQ(5.0f, strategy.get_jump_force());
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_HoppingLeftTest,
   speed__has_the_expected_default_value)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::HoppingLeft strategy;
   ASSERT_EQ(1.0f, strategy.get_speed());
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_HoppingLeftTest, update__will_not_blow_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::HoppingLeft strategy(&basic2d_entity);
   strategy.update();
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_HoppingLeftTest,
   update__if_the_entity_is_on_the_ground__will_set_the_vertical_velocity_to_the_jump_force)
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   float jump_force = 7.3f;
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::HoppingLeft strategy(
      &basic2d_entity,
      jump_force
   );

   basic2d_entity.get_velocity_ref().position = AllegroFlare::vec2d(26, -35);
   basic2d_entity.set(ADJACENT_TO_FLOOR);

   strategy.update();

   EXPECT_EQ(-jump_force, basic2d_entity.get_velocity_ref().position.y);
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_HoppingLeftTest,
   update__if_the_entity_is_on_the_ground__will_remove_the_ADJACENT_TO_FLOOR_flag)
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   float jump_force = 7.3f;
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::HoppingLeft strategy(
      &basic2d_entity,
      jump_force
   );

   basic2d_entity.get_velocity_ref().position = AllegroFlare::vec2d(26, -35);
   basic2d_entity.set(ADJACENT_TO_FLOOR);

   strategy.update();

   EXPECT_EQ(false, basic2d_entity.exists(ADJACENT_TO_FLOOR));
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_HoppingLeftTest,
   update__if_the_entity_is_on_the_ground__set_the_horizontal_velocity_to_zero)
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   float jump_force = 7.3f;
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::HoppingLeft strategy(&basic2d_entity, jump_force);

   basic2d_entity.get_velocity_ref().position = AllegroFlare::vec2d(26, -35);
   basic2d_entity.set(ADJACENT_TO_FLOOR);

   strategy.update();

   EXPECT_EQ(0, basic2d_entity.get_velocity_ref().position.x);
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_HoppingLeftTest,
   update__if_the_entity_is_not_on_the_ground__will_set_the_left_velocity_to_the_speed)
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   float jump_force = 7.3f;
   float speed = 2.6f;
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::HoppingLeft strategy(&basic2d_entity, jump_force, speed);

   basic2d_entity.get_velocity_ref().position = AllegroFlare::vec2d(26, -35);
   ASSERT_EQ(false, basic2d_entity.exists(ADJACENT_TO_FLOOR));

   strategy.update();

   EXPECT_EQ(-speed, basic2d_entity.get_velocity_ref().position.x);
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_HoppingLeftTest,
   update__if_the_entity_is_not_on_the_ground__will_leave_vertical_velocity_unchanged)
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   float jump_force = 7.3f;
   float speed = 2.6f;
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::HoppingLeft strategy(&basic2d_entity, jump_force, speed);

   basic2d_entity.get_velocity_ref().position = AllegroFlare::vec2d(26, -35);
   ASSERT_EQ(false, basic2d_entity.exists(ADJACENT_TO_FLOOR));

   strategy.update();

   EXPECT_EQ(-35, basic2d_entity.get_velocity_ref().position.y);
}


