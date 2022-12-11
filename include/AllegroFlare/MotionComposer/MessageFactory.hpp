#pragma once


#include <string>


namespace AllegroFlare
{
   namespace MotionComposer
   {
      class MessageFactory
      {
      private:

      protected:


      public:
         MessageFactory();
         ~MessageFactory();

         std::string build_set_playhead_position_message_json(float position=0.0f);
         std::string build_toggle_playback_message_json();
         std::string build_clear_message_json();
         std::string build_run_build_process_message_json(std::string platform="[unset-platform]", std::string source_release_zip_url="[unset-source_release_zip_url]");
         std::string build_add_actor2d_with_script_message_json(std::string identifier="[unset-identifier]", std::string bitmap_identifier="[unset-bitmap_identifier]", std::string script="[unset-script]");
      };
   }
}



