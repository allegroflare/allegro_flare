
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <Wicked/Entities/MovementStrategies2D/StayStill.hpp>


TEST(Wicked_Entities_MovementStrategies2D_StayStillTest, can_be_created_without_blowing_up)
{
   Wicked::Entities::MovementStrategies2D::StayStill strategy;
}


TEST(Wicked_Entities_MovementStrategies2D_StayStillTest, update__without_an_entity__throws_an_error)
{
   Wicked::Entities::MovementStrategies2D::StayStill strategy;
   std::string expected_error_message = "StayStill::update: error: guard \"entity\" not met";
   ASSERT_THROW_WITH_MESSAGE(strategy.update(), std::runtime_error, expected_error_message);
}


TEST(Wicked_Entities_MovementStrategies2D_StayStillTest, update__will_not_blow_up)
{
   Wicked::Entities::Basic2D basic2d_entity;
   Wicked::Entities::MovementStrategies2D::StayStill strategy(&basic2d_entity);
   strategy.update();
}


TEST(Wicked_Entities_MovementStrategies2D_StayStillTest,
   update__will_set_the_entitys_position_velocity_to_zero)
{
   Wicked::Entities::Basic2D basic2d_entity;
   Wicked::Entities::MovementStrategies2D::StayStill strategy(&basic2d_entity);

   basic2d_entity.get_velocity_ref().position = AllegroFlare::vec2d(26, -35);
   strategy.update();
   ASSERT_EQ(AllegroFlare::vec2d(0, 0), basic2d_entity.get_velocity_ref().position);
}


