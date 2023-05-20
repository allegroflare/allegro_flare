#pragma once


#include <string>



namespace AllegroFlare
{
   namespace Testing
   {
      class MemoryAllocationDeallocationObserver
      {
      private:
         static bool memory_tracking_enabled;
         static int allocation_count;
         static int deallocation_count;

      public:
         static inline void increment_allocation_count();
         static inline void increment_deallocation_count();
         static inline bool is_memory_tracking_enabled();
         static void enable_memory_tracking();
         static void disable_memory_tracking();
      };
   }
}



// Override global new and delete operators
void* operator new(std::size_t size);
void operator delete(void* ptr) noexcept;


