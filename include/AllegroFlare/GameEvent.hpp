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

   protected:


   public:
      GameEvent(std::string type="[unset-type]", AllegroFlare::GameEventDatas::Base* data=nullptr);
      ~GameEvent();

      void set_data(AllegroFlare::GameEventDatas::Base* data);
      std::string get_type() const;
      AllegroFlare::GameEventDatas::Base* get_data() const;
      bool is_type(std::string possible_type="[unset-possible_type]");
      bool data_is_type(std::string data_possible_type="[unset-data_possible_type]");
   };
}



