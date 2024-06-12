
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/MoveInDirection.hpp>


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_MoveInDirectionTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::MoveInDirection strategy;
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_MoveInDirectionTest, update__without_an_entity__throws_an_error)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::MoveInDirection strategy;
   std::string expected_error_message = "MoveInDirection::update: error: guard \"entity\" not met";
   EXPECT_THROW_WITH_MESSAGE(strategy.update(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_MoveInDirectionTest, update__will_not_blow_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::MoveInDirection strategy(&basic2d_entity);
   strategy.update();
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_MoveInDirectionTest, update__will_assign_the_entitys_left_velocity_to_the_speed)
{
   AllegroFlare::vec2d direction = AllegroFlare::vec2d(2.9f, 7.3f);
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::MoveInDirection strategy(&basic2d_entity, direction);

   strategy.update();
   ASSERT_EQ(AllegroFlare::vec2d(2.9f, 7.3), basic2d_entity.get_velocity_ref().position);
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_MoveInDirectionTest, speed__has_the_expected_default_value)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::MoveInDirection strategy;
   ASSERT_EQ(AllegroFlare::vec2d(0.0f, 0.0f), strategy.get_direction());
}


