



#include <allegro_flare/clipboard.h>

#include <iostream>




Clipboard::Clipboard()
   : __text()
{}




Clipboard *Clipboard::get_instance()
{
   if (!instance) instance = new Clipboard();
   return instance;
}




void Clipboard::set(std::string text)
{
   std::cout << "Copying to clipboard (Your OS is not supported; Using internal clipboard)" << std::endl;
   Clipboard::get_instance()->__text = text;
}




std::string Clipboard::get()
{
   std::cout << "Copying from clipboard (Your OS is not supported; Using internal clipboard)" << std::endl;
   return Clipboard::get_instance()->__text;
}




Clipboard *Clipboard::instance = NULL;




