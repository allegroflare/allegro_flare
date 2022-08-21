#pragma once


#include <AllegroFlare/MotionComposer/Messages/SetPlayheadPosition.hpp>


namespace AllegroFlare
{
   namespace MotionComposer
   {
      class MessageFactory
      {
      private:

      public:
         MessageFactory();
         ~MessageFactory();

         AllegroFlare::MotionComposer::Messages::SetPlayheadPosition* create_set_playead_position_message(float position=0.0f);
      };
   }
}



