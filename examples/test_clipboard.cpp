

#include <allegro_flare/allegro_flare.h>



int main(int argc, char *argv[])
{
   af::initialize();
   Display *display = af::create_display(800, 600);

   std::cout << "the current clipboard text is \"" << Clipboard::get() << "\"" << std::endl;
   std::cout << "setting clipboard text" << std::endl;
   Clipboard::set("Hey guys! Here's some clipboard text! Have a nice day!");

   return 0;
}


