

#include <gtest/gtest.h>

#include <AllegroFlare/Timer.hpp>

#include <unistd.h> // for usleep


using namespace AllegroFlare;


#include <chrono>
#include <thread>
static void SLEEP_FOR(int microseconds=0) { std::this_thread::sleep_for(std::chrono::microseconds(microseconds)); }

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
   // NOTE: This test was previously disabled on Windows. There was no note as to why.
   Timer timer;
   timer.start();
   SLEEP_FOR(1000);
   ASSERT_EQ(1, timer.get_elapsed_time_milliseconds());

   //EXPECT_THAT(x, AllOf(Ge(1),Le(3)));
}


TEST(AllegroFlare_TimerTest, pause__will_prevent_stop_the_timer_from_incrementing)
{
   Timer timer;
   timer.start();
   SLEEP_FOR(60000);
   timer.pause();

   int ellapsed_time_milliseconds = timer.get_elapsed_time_milliseconds();

   EXPECT_GE(ellapsed_time_milliseconds, 60);

   SLEEP_FOR(20000);

   int after_sleep_ellapsed_time_milliseconds = timer.get_elapsed_time_milliseconds();

   EXPECT_GE(ellapsed_time_milliseconds, after_sleep_ellapsed_time_milliseconds);
}


TEST(AllegroFlare_TimerTest, start__after_pause__will_prevent_resume_incrementing_time_without_including_paused_time)
{
   Timer timer;
   timer.start();
   SLEEP_FOR(60000); // 0.06 of a second (60 milliseconds)
   timer.pause();
   SLEEP_FOR(240000); // 0.24 of a second (240 milliseconds)
   timer.start();
   SLEEP_FOR(60000); // 0.06 of a second (60 milliseconds)
   timer.stop();

   int ellapsed_time_milliseconds = timer.get_elapsed_time_milliseconds();

   EXPECT_LE(ellapsed_time_milliseconds, 200);
}


TEST(AllegroFlare_TimerTest, DISABLED_FOR_WIN__get_ellapsed_time_microeconds__will_return_the_elapsed_time)
{
   Timer timer;
   timer.start();
   SLEEP_FOR(1000);
   ASSERT_EQ(1, (timer.get_elapsed_time_microseconds() / 1000));

   //EXPECT_THAT(x, AllOf(Ge(1),Le(3)));
}


TEST(AllegroFlare_TimerTest, DISABLED_FOR_WIN__get_ellapsed_time_nanoseconds__will_return_the_elapsed_time)
{
   Timer timer;
   timer.start();
   SLEEP_FOR(1000);
   ASSERT_EQ(1, (timer.get_elapsed_time_nanoseconds() / 1000000));

   //EXPECT_THAT(x, AllOf(Ge(1),Le(3)));
}


TEST(AllegroFlare_TimerTest, DISABLED_FOR_WIN__reset__will_clear_the_values_and_stop_the_timer_if_it_is_running)
{
   Timer timer;
   timer.start();
   SLEEP_FOR(1000);
   ASSERT_EQ(1, (timer.get_elapsed_time_nanoseconds() / 1000000));

   timer.reset();

   EXPECT_EQ(0, timer.get_elapsed_time_nanoseconds());
   EXPECT_EQ(false, timer.is_running());
}


