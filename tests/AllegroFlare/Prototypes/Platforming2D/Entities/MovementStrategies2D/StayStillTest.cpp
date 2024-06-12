
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/StayStill.hpp>


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_StayStillTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::StayStill strategy;
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_StayStillTest, update__without_an_entity__throws_an_error)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::StayStill strategy;
   std::string expected_error_message = "StayStill::update: error: guard \"entity\" not met";
   EXPECT_THROW_WITH_MESSAGE(strategy.update(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_StayStillTest, update__will_not_blow_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::StayStill strategy(&basic2d_entity);
   strategy.update();
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_StayStillTest,
   update__will_set_the_entitys_position_velocity_to_zero)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::StayStill strategy(&basic2d_entity);

   basic2d_entity.get_velocity_ref().position = AllegroFlare::vec2d(26, -35);
   strategy.update();
   ASSERT_EQ(AllegroFlare::vec2d(0, 0), basic2d_entity.get_velocity_ref().position);
}


