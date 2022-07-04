#pragma once


#include <string>


namespace AllegroFlare
{
   class GameEvent
   {
   private:
      std::string name;

   public:
      GameEvent(std::string name="[unnamed-game-event]");
      ~GameEvent();

      std::string get_name();
   };
}



