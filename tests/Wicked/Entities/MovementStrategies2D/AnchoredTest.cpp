
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <Wicked/Entities/MovementStrategies2D/Anchored.hpp>


TEST(Wicked_Entities_MovementStrategies2D_AnchoredTest, can_be_created_without_blowing_up)
{
   Wicked::Entities::MovementStrategies2D::Anchored strategy;
}


TEST(Wicked_Entities_MovementStrategies2D_AnchoredTest, update__without_an_entity__throws_an_error)
{
   Wicked::Entities::MovementStrategies2D::Anchored strategy;
   std::string expected_error_message = "Anchored::update: error: guard \"entity\" not met";
   EXPECT_THROW_WITH_MESSAGE(strategy.update(), std::runtime_error, expected_error_message);
}


TEST(Wicked_Entities_MovementStrategies2D_AnchoredTest, update__will_not_blow_up)
{
   Wicked::Entities::Basic2D basic2d_entity;
   Wicked::Entities::MovementStrategies2D::Anchored strategy(&basic2d_entity);
   strategy.update();
}


TEST(Wicked_Entities_MovementStrategies2D_AnchoredTest,
   update__will_assign_the_entitys_placement_position_to_the_anchor)
{
   AllegroFlare::vec2d anchor = AllegroFlare::vec2d(2.9f, 7.3f);
   Wicked::Entities::Basic2D basic2d_entity;
   Wicked::Entities::MovementStrategies2D::Anchored strategy(&basic2d_entity, anchor);

   strategy.update();
   ASSERT_EQ(AllegroFlare::vec2d(2.9f, 7.3f), basic2d_entity.get_place_ref().position);
}


TEST(Wicked_Entities_MovementStrategies2D_AnchoredTest, update__will_assign_the_entitys_velocity_position_to_zero)
{
   AllegroFlare::vec2d some_velocity_value = AllegroFlare::vec2d(2.9f, 7.3f);
   Wicked::Entities::Basic2D basic2d_entity;
   basic2d_entity.get_velocity_ref().position = some_velocity_value;
   Wicked::Entities::MovementStrategies2D::Anchored strategy(&basic2d_entity);

   strategy.update();
   ASSERT_EQ(AllegroFlare::vec2d(0.0f, 0.0f), basic2d_entity.get_place_ref().position);
}


TEST(Wicked_Entities_MovementStrategies2D_AnchoredTest, anchor__has_the_expected_default_value)
{
   Wicked::Entities::MovementStrategies2D::Anchored strategy;
   ASSERT_EQ(AllegroFlare::vec2d(0.0f, 0.0f), strategy.get_anchor());
}


