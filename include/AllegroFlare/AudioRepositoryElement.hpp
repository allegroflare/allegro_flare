#pragma once


#include <string>


namespace AllegroFlare
{
   class AudioRepositoryElement
   {
   public:
      static constexpr char* OVERPLAY_STRATEGY_IGNORE = (char*)"ignore";
      static constexpr char* OVERPLAY_STRATEGY_RESTART = (char*)"restart";

   private:
      std::string filename;
      bool loop;
      std::string overplay_strategy;
      float volume;

   protected:


   public:
      AudioRepositoryElement(std::string filename="a-default-audio-repository-filename.ogg", bool loop=false, std::string overplay_strategy=OVERPLAY_STRATEGY_IGNORE, float volume=1.0);
      ~AudioRepositoryElement();

      std::string get_filename() const;
      bool get_loop() const;
      std::string get_overplay_strategy() const;
      float get_volume() const;
      void set_overplay_strategy(std::string overplay_strategy="[unset-overplay_strategy]");
      static bool is_valid_overplay_strategy(std::string possibly_valid_overplay_strategy="[unset-possibly_valid_overplay_strategy]");
      bool overplay_strategy_is_ignore();
      bool overplay_strategy_is_restart();
   };
}



