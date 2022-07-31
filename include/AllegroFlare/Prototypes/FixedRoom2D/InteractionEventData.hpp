#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class InteractionEventData : public AllegroFlare::GameEventDatas::Base
         {
         private:
            std::string item_interacted_with;
            float cursor_x;
            float cursor_y;

         public:
            InteractionEventData(std::string item_interacted_with="[unset-item_interacted_with]", float cursor_x=0.0, float cursor_y=0.0);
            ~InteractionEventData();

         };
      }
   }
}



