#pragma once


#include <string>


namespace AllegroFlare
{
   class AudioRepositoryElement
   {
   private:
      std::string filename;
      bool loop;

   public:
      AudioRepositoryElement(std::string filename="unset-audio-repository-filename.ogg", bool loop=false);
      ~AudioRepositoryElement();

      std::string get_filename();
      bool get_loop();
   };
}



