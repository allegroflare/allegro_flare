
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/CustomComparison.hpp>


#include <Wicked/Entities/MovementStrategies2D/Tracking.hpp>


TEST(Wicked_Entities_MovementStrategies2D_TrackingTest, can_be_created_without_blowing_up)
{
   Wicked::Entities::MovementStrategies2D::Tracking strategy;
}


TEST(Wicked_Entities_MovementStrategies2D_TrackingTest, update__without_an_entity__throws_an_error)
{
   Wicked::Entities::MovementStrategies2D::Tracking strategy;
   std::string expected_error_message = "Tracking::update: error: guard \"entity\" not met";
   ASSERT_THROW_WITH_MESSAGE(strategy.update(), std::runtime_error, expected_error_message);
}


TEST(Wicked_Entities_MovementStrategies2D_TrackingTest, update__without_a_tracked_entity__throws_an_error)
{
   Wicked::Entities::Basic2D basic2d_entity;
   Wicked::Entities::MovementStrategies2D::Tracking strategy(&basic2d_entity);
   std::string expected_error_message = "Tracking::update: error: guard \"tracked_entity\" not met";
   ASSERT_THROW_WITH_MESSAGE(strategy.update(), std::runtime_error, expected_error_message);
}


TEST(Wicked_Entities_MovementStrategies2D_TrackingTest, update__will_not_blow_up)
{
   Wicked::Entities::Basic2D basic2d_entity;
   Wicked::Entities::Basic2D tracked_basic2d_entity;
   Wicked::Entities::MovementStrategies2D::Tracking strategy(&basic2d_entity, &tracked_basic2d_entity);
   strategy.update();
}


TEST(Wicked_Entities_MovementStrategies2D_TrackingTest,
   update__will_set_the_entity_velocity_towards_the_tracked_entity_position_with_a_magnitude_equal_to_the_speed_TEST_1)
{
   float speed = 2.0f;
   Wicked::Entities::Basic2D basic2d_entity;
   Wicked::Entities::Basic2D tracked_basic2d_entity;
   Wicked::Entities::MovementStrategies2D::Tracking strategy(&basic2d_entity, &tracked_basic2d_entity, speed);

   tracked_basic2d_entity.get_place_ref().position = AllegroFlare::vec2d(3, 2);
   basic2d_entity.get_place_ref().position = AllegroFlare::vec2d(-5, -4);
   strategy.set_speed(speed);
   
   strategy.update();

   AllegroFlare::vec2d expected_entity_velocity = AllegroFlare::vec2d(0.8f * speed, 0.6f * speed);
   AllegroFlare::vec2d actual_entity_velocity = basic2d_entity.get_velocity_ref().position;

   ASSERT_EQ(2.0f, actual_entity_velocity.get_magnitude());

   ASSERT_EQ(expected_entity_velocity, actual_entity_velocity);
}


TEST(Wicked_Entities_MovementStrategies2D_TrackingTest, speed__has_the_expected_default_value)
{
   Wicked::Entities::MovementStrategies2D::Tracking strategy;
   ASSERT_EQ(0.5f, strategy.get_speed());
}


