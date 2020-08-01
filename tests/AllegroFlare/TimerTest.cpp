

#include <gtest/gtest.h>

#include <AllegroFlare/Timer.hpp>

#include <unistd.h> // for usleep


using namespace AllegroFlare;


int test_milliseconds_accuracy_time = 10;


TEST(AllegroFlare_TimerTest, can_be_created_without_arguments)
{
   Timer timer;
}


TEST(AllegroFlare_TimerTest, get_ellapsed_time_milliseconds__will_be_zero_before_started)
{
   Timer timer;
   ASSERT_EQ(0, timer.get_elapsed_time_milliseconds());
}


TEST(AllegroFlare_TimerTest, get_ellapsed_time_milliseconds__will_return_the_elapsed_time)
{
   Timer timer;
   timer.start();
   usleep(1000);
   ASSERT_EQ(1, timer.get_elapsed_time_milliseconds());

   //EXPECT_THAT(x, AllOf(Ge(1),Le(3)));
}


TEST(AllegroFlare_TimerTest, pause__will_prevent_stop_the_timer_from_incrementing)
{
   Timer timer;
   timer.start();
   usleep(60000);
   timer.pause();

   int ellapsed_time_milliseconds = timer.get_elapsed_time_milliseconds();

   EXPECT_GE(ellapsed_time_milliseconds, 60);

   usleep(20000);

   int after_sleep_ellapsed_time_milliseconds = timer.get_elapsed_time_milliseconds();

   EXPECT_GE(ellapsed_time_milliseconds, after_sleep_ellapsed_time_milliseconds);
}


TEST(AllegroFlare_TimerTest, get_ellapsed_time_microeconds__will_return_the_elapsed_time)
{
   Timer timer;
   timer.start();
   usleep(1000);
   ASSERT_EQ(1, (timer.get_elapsed_time_microseconds() / 1000));

   //EXPECT_THAT(x, AllOf(Ge(1),Le(3)));
}


TEST(AllegroFlare_TimerTest, get_ellapsed_time_nanoseconds__will_return_the_elapsed_time)
{
   Timer timer;
   timer.start();
   usleep(1000);
   ASSERT_EQ(1, (timer.get_elapsed_time_nanoseconds() / 1000000));

   //EXPECT_THAT(x, AllOf(Ge(1),Le(3)));
}


TEST(AllegroFlare_TimerTest, reset__will_clear_the_values_and_stop_the_timer_if_it_is_running)
{
   Timer timer;
   timer.start();
   usleep(1000);
   ASSERT_EQ(1, (timer.get_elapsed_time_nanoseconds() / 1000000));

   timer.reset();

   EXPECT_EQ(0, timer.get_elapsed_time_nanoseconds());
   EXPECT_EQ(false, timer.is_running());
}

