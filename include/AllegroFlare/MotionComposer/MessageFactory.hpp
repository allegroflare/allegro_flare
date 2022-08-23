#pragma once


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
         std::string build_toggle_playback_message_json();
         std::string build_clear_message_json();
      };
   }
}



