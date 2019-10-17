#ifndef __AF_CLIPBOARD_HEADER
#define __AF_CLIPBOARD_HEADER




#include <string>




namespace allegro_flare
{
   class Clipboard
   {
   private:
      static Clipboard *instance;
      static Clipboard *get_instance();

      std::string __text;
      Clipboard();

   public:
      static void set(std::string text);
      static std::string get();
   };
}




#endif
