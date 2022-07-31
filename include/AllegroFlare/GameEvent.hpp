#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   class GameEvent
   {
   private:
      std::string type;
      AllegroFlare::GameEventDatas::Base* data;

   public:
      GameEvent(std::string type="[unset-type]", AllegroFlare::GameEventDatas::Base* data=nullptr);
      ~GameEvent();

      void set_data(AllegroFlare::GameEventDatas::Base* data);
      std::string get_type();
      AllegroFlare::GameEventDatas::Base* get_data();
      std::string get_name();
      bool is_type(std::string possible_type="[unset-possible_type]");
   };
}



