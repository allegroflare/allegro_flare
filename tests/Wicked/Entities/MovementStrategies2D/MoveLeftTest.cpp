
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <Wicked/Entities/MovementStrategies2D/MoveLeft.hpp>
#include <AllegroFlare/Logger.hpp>


TEST(Wicked_Entities_MovementStrategies2D_MoveLeftTest, can_be_created_without_blowing_up)
{
   Wicked::Entities::MovementStrategies2D::MoveLeft strategy;
}


TEST(Wicked_Entities_MovementStrategies2D_MoveLeftTest, update__without_an_entity__throws_an_error)
{
   Wicked::Entities::MovementStrategies2D::MoveLeft strategy;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Wicked::Entities::MovementStrategies2D::MoveLeft::update",
      "entity"
   );
   EXPECT_THROW_WITH_MESSAGE(strategy.update(), std::runtime_error, expected_error_message);
}


TEST(Wicked_Entities_MovementStrategies2D_MoveLeftTest, update__will_not_blow_up)
{
   Wicked::Entities::Basic2D basic2d_entity;
   Wicked::Entities::MovementStrategies2D::MoveLeft strategy(&basic2d_entity);
   strategy.update();
}


TEST(Wicked_Entities_MovementStrategies2D_MoveLeftTest, update__will_assign_the_entitys_left_velocity_to_the_speed)
{
   float speed = 7.3f;
   Wicked::Entities::Basic2D basic2d_entity;
   Wicked::Entities::MovementStrategies2D::MoveLeft strategy(&basic2d_entity, speed);

   basic2d_entity.get_velocity_ref().position = AllegroFlare::vec2d(26, -35);
   strategy.update();
   ASSERT_EQ(AllegroFlare::vec2d(-speed, 0), basic2d_entity.get_velocity_ref().position);
}


TEST(Wicked_Entities_MovementStrategies2D_MoveLeftTest, speed__has_the_expected_default_value)
{
   Wicked::Entities::MovementStrategies2D::MoveLeft strategy;
   ASSERT_EQ(5.0f, strategy.get_speed());
}


