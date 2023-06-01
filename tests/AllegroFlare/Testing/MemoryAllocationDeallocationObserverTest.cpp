
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AllegroFlare/Testing/MemoryAllocationDeallocationObserver.hpp>
#include <mutex>


TEST(AllegroFlare_Testing_MemoryAllocationDeallocationObserverTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Testing::MemoryAllocationDeallocationObserver memory_allocation_deallocation_observer;
}


TEST(AllegroFlare_Testing_MemoryAllocationDeallocationObserverTest, when_active__will_count_the_number_allocations)
{
   AllegroFlare::Testing::MemoryAllocationDeallocationObserver memory_allocation_deallocation_observer;
   int *var = nullptr;
   memory_allocation_deallocation_observer.enable_memory_tracking();
   var = new int(3);
   memory_allocation_deallocation_observer.disable_memory_tracking();
   EXPECT_EQ(1, memory_allocation_deallocation_observer.get_num_allocations());
   delete var;
}


TEST(AllegroFlare_Testing_MemoryAllocationDeallocationObserverTest, when_active__will_count_the_number_deallocations)
{
   AllegroFlare::Testing::MemoryAllocationDeallocationObserver memory_allocation_deallocation_observer;
   int *var = new int(3);
   memory_allocation_deallocation_observer.enable_memory_tracking();
   delete var;
   memory_allocation_deallocation_observer.disable_memory_tracking();

   EXPECT_EQ(1, memory_allocation_deallocation_observer.get_num_deallocations());
}


TEST(AllegroFlare_Testing_MemoryAllocationDeallocationObserverTest,
   DISABLED__FLAKEY__output_memory_event_logs_enabled__when_true__will_output_to_cout_when_an_allocation_occurs)
{
   // TODO: Find out why this test is flakey and undisable it
   AllegroFlare::Testing::MemoryAllocationDeallocationObserver memory_allocation_deallocation_observer;
   memory_allocation_deallocation_observer.reset(); // TODO: create an object that, on destruction, will reset. Prefer
                                                    // using this object in test cases to guarantee disabling logs
   std::mutex mutex;
   mutex.lock();

   testing::internal::CaptureStdout();
   memory_allocation_deallocation_observer.enable_output_memory_event_logs();
   int *var = new int(3);
   memory_allocation_deallocation_observer.disable_output_memory_event_logs();
   std::string actual_stdout = testing::internal::GetCapturedStdout();

   mutex.unlock();

   EXPECT_THAT(actual_stdout, ::testing::MatchesRegex("new: .*"));

   delete var;
}


TEST(AllegroFlare_Testing_MemoryAllocationDeallocationObserverTest,
   DISABLED__FLAKEY__output_memory_event_logs_enabled__when_true__will_output_to_cout_when_an_deallocation_occurs)
{
   // TODO: Find out why this test is flakey and undisable it
   AllegroFlare::Testing::MemoryAllocationDeallocationObserver observer;
   observer.reset(); // TODO: create an object that, on destruction, will reset. Prefer using this object in test
                     // cases to guarantee disabling logs
   int *var = new int(3);

   std::mutex mutex;
   mutex.lock();

   testing::internal::CaptureStdout();
   observer.enable_output_memory_event_logs();
   delete var;
   observer.disable_output_memory_event_logs();
   std::string actual_stdout = testing::internal::GetCapturedStdout();

   mutex.unlock();

   EXPECT_THAT(actual_stdout, ::testing::MatchesRegex("delete: .*"));
}


