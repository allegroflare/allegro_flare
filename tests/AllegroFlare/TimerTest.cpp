

#include <gtest/gtest.h>

#include <AllegroFlare/Timer.hpp>


using namespace AllegroFlare;


TEST(AllegroFlare_TimerTest, can_be_created_without_arguments)
{
   Timer timer;
}


TEST(AllegroFlare_TimerTest, get_ellapsed_time_msec__will_be_zero_before_started)
{
   Timer timer;
   ASSERT_EQ(0, timer.get_elappsed_time_msec());
}


TEST(AllegroFlare_TimerTest, get_ellapsed_time_msec__will_return_the_elapsed_time)
{
   Timer timer;
   timer.start();
   usleep(1000);
   ASSERT_EQ(1, timer.get_elappsed_time_msec());
}


TEST(AllegroFlare_TimerTest, pause__will_prevent_stop_the_timer_from_incrementing)
{
   Timer timer;
   timer.start();
   usleep(6000);
   timer.pause();

   EXPECT_EQ(6, timer.get_elappsed_time_msec());

   usleep(20000);
   EXPECT_EQ(6, timer.get_elappsed_time_msec());
}


