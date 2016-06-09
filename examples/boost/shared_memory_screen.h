#ifndef __AF_SHARED_MEMORY_SCREEN_HEADER
#define __AF_SHARED_MEMORY_SCREEN_HEADER




#include <allegro_flare/screen.h>
#include <allegro_flare/shared_memory.h>




class SharedMemoryScreen : public SharedMemory, public Screen
{
private:
   std::string shared_memory_content;

public:
   SharedMemoryScreen(std::string identifier, int size);
   void primary_timer_func();// override;
   std::string get_shared_memory_message();
   virtual void on_shared_memory_change();
};




#endif
