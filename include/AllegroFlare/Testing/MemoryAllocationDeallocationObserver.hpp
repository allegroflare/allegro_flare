#pragma once


#include <string>



namespace AllegroFlare
{
   namespace Testing
   {
      class MemoryAllocationDeallocationObserver
      {
      private:
         static bool output_memory_event_logs_enabled;
         static bool memory_tracking_enabled;
         static int allocation_count;
         static int deallocation_count;

         static inline void increment_allocation_count();
         static inline void increment_deallocation_count();

      public:
         MemoryAllocationDeallocationObserver();
         ~MemoryAllocationDeallocationObserver();

         static void reset();
         static void enable_memory_tracking();
         static void disable_memory_tracking();
         static inline bool is_memory_tracking_enabled();

         static void enable_output_memory_event_logs();
         static void disable_output_memory_event_logs();
         static inline bool is_output_memory_event_logs_enabled();

         static int get_num_allocations();
         static int get_num_deallocations();

         friend void* ::operator new(std::size_t size);
         friend void ::operator delete(void* ptr) noexcept;
         friend void ::operator delete(void* ptr, std::size_t size) noexcept; // This overload is used in Windows
      };
   }
}



// Override global new and delete operators
void* operator new(std::size_t size);
void operator delete(void* ptr) noexcept;
void operator delete(void* ptr, std::size_t size) noexcept; // This overload is used in Windows


