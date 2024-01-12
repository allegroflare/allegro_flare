#pragma once


#include <string>
#include <utility>


namespace AllegroFlare
{
   namespace DisplaySettingsInterfaces
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/DisplaySettingsInterfaces/Base";

      private:
         std::string type;

      protected:


      public:
         Base(std::string type=AllegroFlare::DisplaySettingsInterfaces::Base::TYPE);
         virtual ~Base();

         std::string get_type() const;
         virtual void activate_fullscreen();
         virtual void deactivate_fullscreen();
         virtual void toggle_fullscreen();
         virtual bool is_fullscreen();
         virtual void set_window_size(int width=1920, int height=1080);
         virtual std::pair<int, int> get_window_size();
         virtual std::pair<int, int> get_display_size();
         virtual void manually_mark_screensaver_as_inhibited();
         virtual void enable_inhibit_screensaver();
         virtual void disable_inhibit_screensaver();
         virtual void toggle_inhibit_screensaver();
         virtual bool is_screensaver_inhibited();
         virtual void hide_mouse_cursor();
         virtual void show_mouse_cursor();
         virtual void toggle_hide_mouse_cursor();
         virtual bool is_mouse_cursor_hidden();
         bool is_type(std::string possible_type="");
      };
   }
}



