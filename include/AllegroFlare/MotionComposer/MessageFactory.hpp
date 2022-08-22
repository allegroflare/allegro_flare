#pragma once


#include <AllegroFlare/MotionComposer/Messages/SetPlayheadPosition.hpp>
#include <string>


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

         std::string build_set_playhead_position_message_json(float position=0.0f);
         AllegroFlare::MotionComposer::Messages::SetPlayheadPosition* create_set_playhead_position_message(float position=0.0f);
      };
   }
}



