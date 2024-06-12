
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/BackAndForthHorizontal.hpp>


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_BackAndForthHorizontalTest,
   can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::BackAndForthHorizontal strategy;
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_BackAndForthHorizontalTest,
   update__without_an_entity__throws_an_error)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::BackAndForthHorizontal strategy;
   std::string expected_error_message = "BackAndForthHorizontal::update: error: guard \"entity\" not met";
   EXPECT_THROW_WITH_MESSAGE(strategy.update(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_BackAndForthHorizontalTest,
   update__will_not_blow_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::BackAndForthHorizontal strategy(
      &basic2d_entity
   );
   strategy.update();
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_BackAndForthHorizontalTest,
   update__will_assign_the_entitys_left_velocity_to_the_travel_speed)
{
   float travel_speed = 7.3f;
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::BackAndForthHorizontal strategy(
      &basic2d_entity,
      travel_speed
   );

   basic2d_entity.get_velocity_ref().position = AllegroFlare::vec2d(26, -35);
   strategy.update();
   ASSERT_EQ(AllegroFlare::vec2d(travel_speed, 0), basic2d_entity.get_velocity_ref().position);
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_BackAndForthHorizontalTest,
   travel_speed__has_the_expected_default_value)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::BackAndForthHorizontal strategy;
   ASSERT_EQ(4.0f, strategy.get_travel_speed());
}


