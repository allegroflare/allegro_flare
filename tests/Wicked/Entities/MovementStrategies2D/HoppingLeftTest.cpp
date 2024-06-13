
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <Wicked/Entities/MovementStrategies2D/HoppingLeft.hpp>
#include <AllegroFlare/Logger.hpp>


TEST(Wicked_Entities_MovementStrategies2D_HoppingLeftTest, can_be_created_without_blowing_up)
{
   Wicked::Entities::MovementStrategies2D::HoppingLeft strategy;
}


TEST(Wicked_Entities_MovementStrategies2D_HoppingLeftTest, update__without_an_entity__throws_an_error)
{
   Wicked::Entities::MovementStrategies2D::HoppingLeft strategy;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Wicked::Entities::MovementStrategies2D::HoppingLeft::update",
      "entity"
   );
   EXPECT_THROW_WITH_MESSAGE(strategy.update(), std::runtime_error, expected_error_message);
}


TEST(Wicked_Entities_MovementStrategies2D_HoppingLeftTest, jump_force__has_the_expected_default_value)
{
   Wicked::Entities::MovementStrategies2D::HoppingLeft strategy;
   ASSERT_EQ(5.0f, strategy.get_jump_force());
}


TEST(Wicked_Entities_MovementStrategies2D_HoppingLeftTest, speed__has_the_expected_default_value)
{
   Wicked::Entities::MovementStrategies2D::HoppingLeft strategy;
   ASSERT_EQ(1.0f, strategy.get_speed());
}


TEST(Wicked_Entities_MovementStrategies2D_HoppingLeftTest, update__will_not_blow_up)
{
   Wicked::Entities::Basic2D basic2d_entity;
   Wicked::Entities::MovementStrategies2D::HoppingLeft strategy(&basic2d_entity);
   strategy.update();
}


TEST(Wicked_Entities_MovementStrategies2D_HoppingLeftTest,
   update__if_the_entity_is_on_the_ground__will_set_the_vertical_velocity_to_the_jump_force)
{
   float jump_force = 7.3f;
   Wicked::Entities::Basic2D basic2d_entity;
   Wicked::Entities::MovementStrategies2D::HoppingLeft strategy(&basic2d_entity, jump_force);

   basic2d_entity.get_velocity_ref().position = AllegroFlare::vec2d(26, -35);
   basic2d_entity.set("on_ground");

   strategy.update();

   EXPECT_EQ(-jump_force, basic2d_entity.get_velocity_ref().position.y);
}


TEST(Wicked_Entities_MovementStrategies2D_HoppingLeftTest,
   update__if_the_entity_is_on_the_ground__will_remove_the_on_ground_flag)
{
   float jump_force = 7.3f;
   Wicked::Entities::Basic2D basic2d_entity;
   Wicked::Entities::MovementStrategies2D::HoppingLeft strategy(&basic2d_entity, jump_force);

   basic2d_entity.get_velocity_ref().position = AllegroFlare::vec2d(26, -35);
   basic2d_entity.set("on_ground");

   strategy.update();

   EXPECT_EQ(false, basic2d_entity.exists("on_ground"));
}


TEST(Wicked_Entities_MovementStrategies2D_HoppingLeftTest,
   update__if_the_entity_is_on_the_ground__set_the_horizontal_velocity_to_zero)
{
   float jump_force = 7.3f;
   Wicked::Entities::Basic2D basic2d_entity;
   Wicked::Entities::MovementStrategies2D::HoppingLeft strategy(&basic2d_entity, jump_force);

   basic2d_entity.get_velocity_ref().position = AllegroFlare::vec2d(26, -35);
   basic2d_entity.set("on_ground");

   strategy.update();

   EXPECT_EQ(0, basic2d_entity.get_velocity_ref().position.x);
}


TEST(Wicked_Entities_MovementStrategies2D_HoppingLeftTest,
   update__if_the_entity_is_not_on_the_ground__will_set_the_left_velocity_to_the_speed)
{
   float jump_force = 7.3f;
   float speed = 2.6f;
   Wicked::Entities::Basic2D basic2d_entity;
   Wicked::Entities::MovementStrategies2D::HoppingLeft strategy(&basic2d_entity, jump_force, speed);

   basic2d_entity.get_velocity_ref().position = AllegroFlare::vec2d(26, -35);
   ASSERT_EQ(false, basic2d_entity.exists("on_ground"));

   strategy.update();

   EXPECT_EQ(-speed, basic2d_entity.get_velocity_ref().position.x);
}


TEST(Wicked_Entities_MovementStrategies2D_HoppingLeftTest,
   update__if_the_entity_is_not_on_the_ground__will_leave_vertical_velocity_unchanged)
{
   float jump_force = 7.3f;
   float speed = 2.6f;
   Wicked::Entities::Basic2D basic2d_entity;
   Wicked::Entities::MovementStrategies2D::HoppingLeft strategy(&basic2d_entity, jump_force, speed);

   basic2d_entity.get_velocity_ref().position = AllegroFlare::vec2d(26, -35);
   ASSERT_EQ(false, basic2d_entity.exists("on_ground"));

   strategy.update();

   EXPECT_EQ(-35, basic2d_entity.get_velocity_ref().position.y);
}


