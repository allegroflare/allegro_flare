
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/MemoryAllocationDeallocationObserver.hpp>


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


