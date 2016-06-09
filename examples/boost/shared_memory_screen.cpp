



#include <allegro_flare/screens/shared_memory_screen.h>
#include <allegro_flare/useful.h>
#include <allegro_flare/useful_php.h>




SharedMemoryScreen::SharedMemoryScreen(std::string identifier, int size)
   : SharedMemory(identifier, size)
   , Screen(NULL)
   , shared_memory_content(size, '\0')
{}




void SharedMemoryScreen::primary_timer_func()
{
   std::string message_now = SharedMemory::read();
   message_now = php::trim(message_now);
   if (message_now != shared_memory_content)
   {
      shared_memory_content = message_now;
      on_shared_memory_change();
   }
}




std::string SharedMemoryScreen::get_shared_memory_message()
{
   return shared_memory_content;
}




void SharedMemoryScreen::on_shared_memory_change()
{
   std::cout << std::endl << "SharedMemoryScreen.on_shared_memory_change() -> " << get_shared_memory_message();
}




