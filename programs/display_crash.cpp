#include <allegro5/allegro.h>
#include <iostream>


int main(int argc, char** argv)
{
   al_init();
   ALLEGRO_DISPLAY *display = nullptr;

   int attempts = 20;

   for (int attempt=0; attempt<attempts; attempt++)
   {
      std::cout << "creating display (attempt " << attempt << ")" << std::endl;
      try
      {
         display = al_create_display(1920, 1080);
      }
      catch (std::exception& e)
      {
         std::cout << e.what() << '\n';
      }
      std::cout << "   display created" << std::endl;
      std::cout << "destroying display" << std::endl;
      al_destroy_display(display);
      std::cout << "   display destroyed" << std::endl;
   }

   std::cout << "Process finished." << std::endl;

   al_uninstall_system();
   return 0;
}


