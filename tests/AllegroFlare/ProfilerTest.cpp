
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/Profiler.hpp>
#include <allegro5/allegro_color.h>

// for usleep on Windows
#include <unistd.h>


class AllegroFlare_ProfilerTest : public ::testing::Test
{};

class AllegroFlare_ProfilerTestWithAllegroRenderingFixture : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_ProfilerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Profiler profiler;
}


TEST_F(AllegroFlare_ProfilerTest, DISABLED__emit__will_add_an_event_time_to_that_event_bucket)
   // TODO this test crashes on Windows
{
   std::string EVENT_IDENTIFIER = "my_custom_event";

   AllegroFlare::Profiler profiler;
   for (unsigned i=0; i<10; i++)
   {
      profiler.emit(EVENT_IDENTIFIER);
      usleep(10000);
   }

   ASSERT_EQ(1, profiler.get_event_buckets().size());
   ASSERT_EQ(10, profiler.get_event_samples(EVENT_IDENTIFIER, 10).size());
   ASSERT_EQ(6, profiler.get_event_samples(EVENT_IDENTIFIER, 6).size());
}


TEST_F(AllegroFlare_ProfilerTest, VISUAL__build_report__will_generate_a_simple_text_report)
{
   al_init();
   AllegroFlare::Profiler profiler;
   profiler.start("The global timer");
   al_rest(1);
   profiler.start("My timer 1");
   al_rest(1);
   profiler.start("Another timer of mine");
   al_rest(1);
   profiler.stop("My timer 1");
   profiler.start("A third timer");
   al_rest(1);
   profiler.stop("A third timer");
   profiler.stop("Another timer of mine");
   profiler.stop("The global timer");

   std::string actual_report = profiler.build_report();

   // TODO: Add some kind of EXPECT on the format of this report
   std::cout << "=== REPORT ===" << std::endl;
   std::cout << actual_report << std::endl;
   std::cout << "=== REPORT END ===" << std::endl;
   al_uninstall_system();
}


