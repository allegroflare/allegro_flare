#pragma once


#include <AllegroFlare/DisplaySettingsInterfaces/Base.hpp>
#include <utility>


namespace AllegroFlare
{
   namespace Testing
   {
      namespace AllegroFlare
      {
         namespace DisplaySettingsInterfaces
         {
            class DisplayMock : public ::AllegroFlare::DisplaySettingsInterfaces::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Testing/AllegroFlare/DisplaySettingsInterfaces/DisplayMock";

            private:
               bool fullscreen_status;
               int display_width;
               int display_height;
               bool screensaver_inhibited;
               bool mouse_cursor_hidden;

            protected:


            public:
               DisplayMock();
               virtual ~DisplayMock();

               bool get_fullscreen_status() const;
               int get_display_width() const;
               int get_display_height() const;
               virtual void activate_fullscreen() override;
               virtual void deactivate_fullscreen() override;
               virtual void toggle_fullscreen() override;
               virtual bool is_fullscreen() override;
               virtual void set_window_size(int width=1920, int height=1080) override;
               virtual std::pair<int, int> get_window_size() override;
               virtual std::pair<int, int> get_display_size() override;
               virtual void manually_mark_screensaver_as_inhibited() override;
               virtual void enable_inhibit_screensaver() override;
               virtual void disable_inhibit_screensaver() override;
               virtual void toggle_inhibit_screensaver() override;
               virtual bool is_screensaver_inhibited() override;
               virtual void hide_mouse_cursor() override;
               virtual void show_mouse_cursor() override;
               virtual void toggle_hide_mouse_cursor() override;
               virtual bool is_mouse_cursor_hidden() override;
            };
         }
      }
   }
}



