
#include <gtest/gtest.h>

#include <AllegroFlare/VariableTimeStepper.hpp>


TEST(AllegroFlare_VariableTimeStepperTest, can_be_created_without_blowing_up)
{
   AllegroFlare::VariableTimeStepper stepper;
}


const double TIME_STEP_RESOLUTION_DENOM = 256.0;

TEST(AllegroFlare_VariableTimeStepperTest, step_ahead_to__will_perform_steps_to_the_target_time)
{
   AllegroFlare::VariableTimeStepper stepper;

   // Target time requires 4 steps: floor(0.018 * 256) = 4
   const double target_time = 0.018;
   auto [remaining_time, steps_taken, excess_steps] = stepper.step_ahead_to(target_time);

   EXPECT_EQ(4, steps_taken);
   EXPECT_EQ(0, excess_steps);
   EXPECT_DOUBLE_EQ(target_time - (4.0 / TIME_STEP_RESOLUTION_DENOM), remaining_time);
}


TEST(AllegroFlare_VariableTimeStepperTest, step_ahead_to__will_cap_steps_to_max_allowed_steps)
{
   AllegroFlare::VariableTimeStepper stepper;

   const int max_steps = 5;
   stepper.set_max_allowed_steps(max_steps);
   
   // Target time would ideally require 12 steps: floor(0.05 * 256) = 12
   const double target_time = 0.05;
   auto [remaining_time, steps_taken, excess_steps] = stepper.step_ahead_to(target_time);

   EXPECT_EQ(max_steps, steps_taken);
   EXPECT_EQ(12-max_steps, excess_steps);
   EXPECT_DOUBLE_EQ(target_time - (max_steps / TIME_STEP_RESOLUTION_DENOM), remaining_time);
}


