

#include <AllegroFlare/Testing/MemoryAllocationDeallocationObserver.hpp>

#include <iostream>



namespace AllegroFlare
{
namespace Testing
{



bool MemoryAllocationDeallocationObserver::output_memory_event_logs_enabled = false;
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



bool MemoryAllocationDeallocationObserver::is_output_memory_event_logs_enabled()
{
   return output_memory_event_logs_enabled;
}



MemoryAllocationDeallocationObserver::MemoryAllocationDeallocationObserver()
{
   reset();
}



MemoryAllocationDeallocationObserver::~MemoryAllocationDeallocationObserver()
{
   reset();
}



void MemoryAllocationDeallocationObserver::reset()
{
   output_memory_event_logs_enabled = false;
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



void MemoryAllocationDeallocationObserver::enable_output_memory_event_logs()
{
   output_memory_event_logs_enabled = true;
}



void MemoryAllocationDeallocationObserver::disable_output_memory_event_logs()
{
   output_memory_event_logs_enabled = false;
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
   if (AllegroFlare::Testing::MemoryAllocationDeallocationObserver::is_output_memory_event_logs_enabled())
   {
      std::cout << "new: " << ptr << ", size: " << size << std::endl << std::flush;
   }

   return ptr;
}


void operator delete(void* ptr) noexcept
{
   if (AllegroFlare::Testing::MemoryAllocationDeallocationObserver::is_memory_tracking_enabled())
   {
      AllegroFlare::Testing::MemoryAllocationDeallocationObserver::increment_deallocation_count();
   }
   if (AllegroFlare::Testing::MemoryAllocationDeallocationObserver::is_output_memory_event_logs_enabled())
   {
      std::cout << "delete: " << ptr << std::endl << std::flush;
   }
   std::free(ptr);
}


void operator delete(void* ptr, std::size_t size) noexcept
{
   if (AllegroFlare::Testing::MemoryAllocationDeallocationObserver::is_memory_tracking_enabled())
   {
      AllegroFlare::Testing::MemoryAllocationDeallocationObserver::increment_deallocation_count();
   }
   if (AllegroFlare::Testing::MemoryAllocationDeallocationObserver::is_output_memory_event_logs_enabled())
   {
      std::cout << "delete: " << ptr << ", size: " << size << std::endl << std::flush;
   }
   std::free(ptr);
}



