

#include <AllegroFlare/Testing/MemoryAllocationDeallocationObserver.hpp>



namespace AllegroFlare
{
namespace Testing
{



bool MemoryAllocationDeallocationObserver::memory_tracking_enabled = false;
int MemoryAllocationDeallocationObserver::allocation_count = 0;
int MemoryAllocationDeallocationObserver::deallocation_count = 0;



void MemoryAllocationDeallocationObserver::increment_allocation_count()
{
   allocation_count++;
}



void MemoryAllocationDeallocationObserver::increment_deallocation_count()
{
   deallocation_count++;
}


bool MemoryAllocationDeallocationObserver::is_memory_tracking_enabled()
{
   return memory_tracking_enabled;
}



void MemoryAllocationDeallocationObserver::reset()
{
   memory_tracking_enabled = false;
   allocation_count = 0;
   deallocation_count = 0;
}



void MemoryAllocationDeallocationObserver::enable_memory_tracking()
{
   memory_tracking_enabled = true;
}



void MemoryAllocationDeallocationObserver::disable_memory_tracking()
{
   memory_tracking_enabled = false;
}



int MemoryAllocationDeallocationObserver::get_num_allocations()
{
   return allocation_count;
}



int MemoryAllocationDeallocationObserver::get_num_deallocations()
{
   return deallocation_count;
}



} // namespace Testing
} // namespace AllegroFlare



void* operator new(std::size_t size)
{
   void* ptr = std::malloc(size);
   if (AllegroFlare::Testing::MemoryAllocationDeallocationObserver::is_memory_tracking_enabled())
   {
      AllegroFlare::Testing::MemoryAllocationDeallocationObserver::increment_allocation_count();
   }
   return ptr;
}


void operator delete(void* ptr) noexcept
{
   if (AllegroFlare::Testing::MemoryAllocationDeallocationObserver::is_memory_tracking_enabled())
   {
      AllegroFlare::Testing::MemoryAllocationDeallocationObserver::increment_deallocation_count();
   }
   std::free(ptr);
}


void operator delete(void* ptr, std::size_t size) noexcept
{
   if (AllegroFlare::Testing::MemoryAllocationDeallocationObserver::is_memory_tracking_enabled())
   {
      AllegroFlare::Testing::MemoryAllocationDeallocationObserver::increment_deallocation_count();
   }
   std::free(ptr);
}



