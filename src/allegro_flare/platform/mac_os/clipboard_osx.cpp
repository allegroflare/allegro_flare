



#include <allegro_flare/clipboard.h>

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <allegro5/allegro.h>




Clipboard *Clipboard::instance = NULL;




Clipboard::Clipboard()
   : __text("")
{}




static std::string __OSX_exec(const char* cmd)
{
   FILE* pipe = popen(cmd, "r");
   if (!pipe) return "ERROR";
   char buffer[128];
   std::string result = "";
   while(!feof(pipe))
   {
      if(fgets(buffer, 128, pipe) != NULL)
      {
         result += buffer;
      }
   }
   pclose(pipe);
   return result;
}




Clipboard *Clipboard::get_instance()
{
   if (!instance) instance = new Clipboard();
   return instance;
}




void Clipboard::set(std::string text)
{
   std::stringstream cmd;
   cmd << "printf \"" << text << "\" | pbcopy";
   __OSX_exec(cmd.str().c_str());

   get_instance()->__text = text;
}




std::string Clipboard::get()
{
   std::string text = __OSX_exec("pbpaste");

   get_instance()->__text = text;

   return text;
}




