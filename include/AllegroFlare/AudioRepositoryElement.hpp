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
      float volume;

   protected:


   public:
      AudioRepositoryElement(std::string filename="a-default-audio-repository-filename.ogg", bool loop=false, std::string overplay_strategy="ignore", float volume=1.0);
      ~AudioRepositoryElement();

      std::string get_filename() const;
      bool get_loop() const;
      std::string get_overplay_strategy() const;
      float get_volume() const;
      bool overplay_strategy_is_ignore();
      bool overplay_strategy_is_restart();
   };
}



