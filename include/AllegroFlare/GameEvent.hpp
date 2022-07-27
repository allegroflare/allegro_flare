#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   class GameEvent
   {
   private:
      std::string name;
      AllegroFlare::GameEventDatas::Base* data;

   public:
      GameEvent(std::string name="[unnamed-game-event]", AllegroFlare::GameEventDatas::Base* data=nullptr);
      ~GameEvent();

      void set_data(AllegroFlare::GameEventDatas::Base* data);
      std::string get_name();
      AllegroFlare::GameEventDatas::Base* get_data();
   };
}



