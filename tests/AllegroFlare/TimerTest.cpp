

#include <gtest/gtest.h>

#include <AllegroFlare/Timer.hpp>

#include <unistd.h> // for usleep


using namespace AllegroFlare;


int test_milliseconds_accuracy_time = 10;


TEST(AllegroFlare_TimerTest, can_be_created_without_arguments)
{
   Timer timer;
}


TEST(AllegroFlare_TimerTest, get_ellapsed_time_msec__will_be_zero_before_started)
{
   Timer timer;
   ASSERT_EQ(0, timer.get_elapsed_time_msec());
}


TEST(AllegroFlare_TimerTest, get_ellapsed_time_msec__will_return_the_elapsed_time)
{
   Timer timer;
   timer.start();
   usleep(1000);
   ASSERT_EQ(1, timer.get_elapsed_time_msec());

   //EXPECT_THAT(x, AllOf(Ge(1),Le(3)));
}


TEST(AllegroFlare_TimerTest, pause__will_prevent_stop_the_timer_from_incrementing)
{
   Timer timer;
   timer.start();
   usleep(60000);
   timer.pause();

   int ellapsed_time_msec = timer.get_elapsed_time_msec();

   EXPECT_GE(ellapsed_time_msec, 60);

   usleep(20000);

   int after_sleep_ellapsed_time_msec = timer.get_elapsed_time_msec();

   EXPECT_GE(ellapsed_time_msec, after_sleep_ellapsed_time_msec);
}


TEST(AllegroFlare_TimerTest, get_ellapsed_time_nonseconds__will_return_the_elapsed_time)
{
   Timer timer;
   timer.start();
   usleep(1000);
   ASSERT_EQ(1, (timer.get_elapsed_time_nanoseconds() / 1000000));

   //EXPECT_THAT(x, AllOf(Ge(1),Le(3)));
}


