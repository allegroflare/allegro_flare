
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/ReflectOffWalls.hpp>


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_ReflectOffWallsTest,
   can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::ReflectOffWalls strategy;
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_ReflectOffWallsTest,
   update__without_an_entity__throws_an_error)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::ReflectOffWalls strategy;
   EXPECT_THROW_GUARD_ERROR(
      strategy.update(),
      "AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::ReflectOffWalls::update",
      "entity"
   );
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_ReflectOffWallsTest, update__will_not_blow_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::ReflectOffWalls strategy(&basic2d_entity);
   strategy.update();
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_ReflectOffWallsTest,
   update__will_assign_the_entitys_left_velocity_to_the_speed)
{
   //TODO: (also rename method)
   //float speed = 7.3f;
   //AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   //AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::ReflectOffWalls strategy(&basic2d_entity, speed);

   //basic2d_entity.get_velocity_ref().position = AllegroFlare::vec2d(26, -35);
   //strategy.update();
   //ASSERT_EQ(AllegroFlare::vec2d(-speed, 0), basic2d_entity.get_velocity_ref().position);
}


TEST(AllegroFlare_Prototypes_Platforming2D_Entities_MovementStrategies2D_ReflectOffWallsTest,
   speed__has_the_expected_default_value)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::ReflectOffWalls strategy;
   ASSERT_EQ(3.0f, strategy.get_speed());
}


