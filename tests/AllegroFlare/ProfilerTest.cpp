
#include <gtest/gtest.h>

#include <AllegroFlare/Profiler.hpp>

TEST(AllegroFlare_ProfilerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Profiler profiler;
}

TEST(AllegroFlare_ProfilerTest, emit__will_add_an_event_time_to_that_event_bucket)
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

