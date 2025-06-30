
#include <gtest/gtest.h>

#include <AllegroFlare/AtomicTimeStepper.hpp>


TEST(AllegroFlare_AtomicTimeStepperTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AtomicTimeStepper atomic_time_stepper;
}


TEST(AllegroFlare_AtomicTimeStepperTest,
   step_n_times__will_process_the_number_of_expected_steps_and_accumulate_total_time)
{
   AllegroFlare::AtomicTimeStepper atomic_time_stepper;
   //timing_core.register_timer_with_event_queue(event_queue);
   //timing_core.start();

   double TIME_STEP_RESOLUTION = 1.0 / 256.0;

   uint64_t expected_time_steps = 12;
   double expected_accumulated_time = TIME_STEP_RESOLUTION * expected_time_steps;

   // Do stuff
   atomic_time_stepper.step_n_times(expected_time_steps);

   EXPECT_EQ(expected_time_steps, atomic_time_stepper.get_total_accumulated_steps());
   EXPECT_EQ(expected_accumulated_time, atomic_time_stepper.get_total_accumulated_time());
}


struct CallbackMetaData
{
   int num_times_callback_called = 0;
   double last_total_accumulated_time = 0;
};


void my_on_step_callback(double step, double total, void* user_data)
{
   auto &callback_meta_data = *static_cast<CallbackMetaData*>(user_data);
   callback_meta_data.num_times_callback_called++;
   callback_meta_data.last_total_accumulated_time = total;
}


TEST(AllegroFlare_AtomicTimeStepperTest, step_n_times__will_call_the_callback)
{
   AllegroFlare::AtomicTimeStepper atomic_time_stepper;
   CallbackMetaData callback_meta_data;
   atomic_time_stepper.set_on_step_func(my_on_step_callback);
   atomic_time_stepper.set_on_step_func_user_data(&callback_meta_data);

   uint64_t expected_time_steps = 12;
   double TIME_STEP_RESOLUTION = 1.0 / 256.0;
   double expected_accumulated_time = TIME_STEP_RESOLUTION * expected_time_steps;

   // Do stuff
   atomic_time_stepper.set_on_step_func(my_on_step_callback);
   atomic_time_stepper.set_on_step_func_user_data(&callback_meta_data);

   atomic_time_stepper.step_n_times(expected_time_steps);

   EXPECT_EQ(expected_time_steps, callback_meta_data.num_times_callback_called);
   EXPECT_EQ(expected_accumulated_time, callback_meta_data.last_total_accumulated_time);
}


