#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         namespace ScriptEventDatas
         {
            class EnterRoom : public AllegroFlare::GameEventDatas::Base
            {
            public:
               static constexpr char* TYPE = (char*)"ScriptEventDatas/EnterRoom";

            private:
               std::string room_dictionary_name_to_enter;

            protected:


            public:
               EnterRoom(std::string room_dictionary_name_to_enter="[unset-room_dictionary_name_to_enter]");
               ~EnterRoom();

               void set_room_dictionary_name_to_enter(std::string room_dictionary_name_to_enter);
               std::string get_room_dictionary_name_to_enter() const;
            };
         }
      }
   }
}



