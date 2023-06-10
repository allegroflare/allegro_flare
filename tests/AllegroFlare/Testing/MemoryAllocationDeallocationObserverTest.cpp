
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AllegroFlare/Testing/MemoryAllocationDeallocationObserver.hpp>
#include <mutex>


TEST(AllegroFlare_Testing_MemoryAllocationDeallocationObserverTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Testing::MemoryAllocationDeallocationObserver observer;
}


TEST(AllegroFlare_Testing_MemoryAllocationDeallocationObserverTest, when_active__will_count_the_number_allocations)
{
   AllegroFlare::Testing::MemoryAllocationDeallocationObserver observer;
   int *var = nullptr;
   observer.enable_memory_tracking();
   var = new int(3);
   observer.disable_memory_tracking();
   EXPECT_EQ(1, observer.get_num_allocations());
   delete var;
}


TEST(AllegroFlare_Testing_MemoryAllocationDeallocationObserverTest, when_active__will_count_the_number_deallocations)
{
   AllegroFlare::Testing::MemoryAllocationDeallocationObserver observer;
   int *var = new int(3);
   observer.enable_memory_tracking();
   delete var;
   observer.disable_memory_tracking();

   EXPECT_EQ(1, observer.get_num_deallocations());
}


TEST(AllegroFlare_Testing_MemoryAllocationDeallocationObserverTest,
   FLAKEY__output_memory_event_logs_enabled__when_true__will_output_to_cout_when_an_allocation_occurs)
{
   AllegroFlare::Testing::MemoryAllocationDeallocationObserver observer;
   std::mutex mutex;
   mutex.lock();

   testing::internal::CaptureStdout();
   observer.enable_output_memory_event_logs();
   int *var = new int(3);
   observer.disable_output_memory_event_logs();
   std::string actual_stdout = testing::internal::GetCapturedStdout();

   mutex.unlock();

   EXPECT_THAT(actual_stdout, ::testing::MatchesRegex("new: .*\n"));

   delete var;
}


TEST(AllegroFlare_Testing_MemoryAllocationDeallocationObserverTest,
   FLAKEY__output_memory_event_logs_enabled__when_true__will_output_to_cout_when_an_deallocation_occurs)
{
   AllegroFlare::Testing::MemoryAllocationDeallocationObserver observer;
   int *var = new int(3);

   std::mutex mutex;
   mutex.lock();

   testing::internal::CaptureStdout();
   observer.enable_output_memory_event_logs();
   delete var;
   observer.disable_output_memory_event_logs();
   std::string actual_stdout = testing::internal::GetCapturedStdout();

   mutex.unlock();

   EXPECT_THAT(actual_stdout, ::testing::MatchesRegex("delete: .*\n"));
}


