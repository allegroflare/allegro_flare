
#include <gtest/gtest.h>

#include <AllegroFlare/Time.hpp>
#include <allegro5/allegro.h>


TEST(AllegroFlare_TimeTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Time time;
}


TEST(AllegroFlare_TimeTest, DISABLED__now__returns_the_current_time)
{
   // This test is disabled because it is flakey, returning values that will be slightly off. However, the test is
   // returning values that are close to expected.
   // TOOD: Modify this test to be able to account for flaky testing conditions

   al_init();
   AllegroFlare::Time time;
   EXPECT_EQ(0.0, time.now());

   al_rest(1);

   EXPECT_EQ(1.0, time.now());

   time.set_rate(3.0);
   al_rest(1);

   EXPECT_EQ(4.0, time.now());

   time.set_rate(0.25);
   al_rest(1);

   EXPECT_EQ(4.25, time.now());

   al_uninstall_system();
}


TEST(AllegroFlare_TimeTest, set_rate__modifies_the_passing_of_now)
{
   double my_universal_absolute_now = 0.0f;

   AllegroFlare::Time time;
   time.set_absolute_now(my_universal_absolute_now);

   EXPECT_EQ(0.0, time.now());

   my_universal_absolute_now += 1.0; // Simulate resting 1 second

   time.set_absolute_now(my_universal_absolute_now);
   EXPECT_EQ(1.0, time.now());

   time.set_rate(3.0);

   my_universal_absolute_now += 1.0; // Simulate resting 1 second
   time.set_absolute_now(my_universal_absolute_now);

   EXPECT_EQ(4.0, time.now());

   time.set_rate(0.25);
   time.set_absolute_now(my_universal_absolute_now);

   my_universal_absolute_now += 1.0; // Simulate resting 1 second

   time.set_absolute_now(my_universal_absolute_now);
   EXPECT_EQ(4.25, time.now());
}


TEST(AllegroFlare_TimeTest, pause__will_suspend_the_passage_of_now)
{
   double my_universal_absolute_now = 0.0f;

   AllegroFlare::Time time;
   time.set_absolute_now(my_universal_absolute_now);
   EXPECT_EQ(0.0, time.now());

   time.pause();

   my_universal_absolute_now += 1.0; // Simulate resting 1 second
   time.set_absolute_now(my_universal_absolute_now);

   EXPECT_EQ(0.0, time.now());

   time.unpause();

   my_universal_absolute_now += 1.0; // Simulate resting 1 second
   time.set_absolute_now(my_universal_absolute_now);

   EXPECT_EQ(1.0, time.now());
}


