#pragma once


#include <string>


namespace AllegroFlare
{
   class AudioRepositoryElement
   {
   private:
      std::string filename;
      bool loop;
      std::string overplay_strategy;

   public:
      AudioRepositoryElement(std::string filename="a-default-audio-repository-filename.ogg", bool loop=false, std::string overplay_strategy="ignore");
      ~AudioRepositoryElement();

      std::string get_filename();
      bool get_loop();
      std::string get_overplay_strategy();
   };
}



