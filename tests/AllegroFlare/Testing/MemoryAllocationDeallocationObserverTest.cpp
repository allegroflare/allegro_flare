
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/MemoryAllocationDeallocationObserver.hpp>


TEST(AllegroFlare_Testing_MemoryAllocationDeallocationObserverTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Testing::MemoryAllocationDeallocationObserver memory_allocation_deallocation_observer;
}


