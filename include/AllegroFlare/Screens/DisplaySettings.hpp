#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/DisplaySettingsInterfaces/Base.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/DisplaySettings.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
#include <functional>
#include <string>
#include <utility>


namespace AllegroFlare
{
   namespace Screens
   {
      class DisplaySettings : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Screens/DisplaySettings";
         static constexpr char* DEFAULT_LABEL_FOR_EXIT_SCREEN_MENU_OPTION = (char*)"Exit";

      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::ModelBin* model_bin;
         AllegroFlare::DisplaySettingsInterfaces::Base* display_settings_interface;
         std::string label_for_menu_option_to_exit_screen;
         std::function<void(AllegroFlare::Screens::DisplaySettings*, void*)> on_exit_callback_func;
         void* on_exit_callback_func_user_data;
         int surface_width;
         int surface_height;
         int base_font_size;
         int cursor_y;
         int cursor_x;
         bool up_pressed;
         double up_pressed_at;
         bool down_pressed;
         double down_pressed_at;
         bool initialized;
         ALLEGRO_FONT* obtain_heading_font();
         ALLEGRO_FONT* obtain_label_font();

      protected:


      public:
         DisplaySettings(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr, AllegroFlare::DisplaySettingsInterfaces::Base* display_settings_interface=nullptr, int base_font_size=-34);
         virtual ~DisplaySettings();

         void set_label_for_menu_option_to_exit_screen(std::string label_for_menu_option_to_exit_screen);
         void set_on_exit_callback_func(std::function<void(AllegroFlare::Screens::DisplaySettings*, void*)> on_exit_callback_func);
         void set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data);
         void set_surface_height(int surface_height);
         void set_base_font_size(int base_font_size);
         AllegroFlare::DisplaySettingsInterfaces::Base* get_display_settings_interface() const;
         std::string get_label_for_menu_option_to_exit_screen() const;
         std::function<void(AllegroFlare::Screens::DisplaySettings*, void*)> get_on_exit_callback_func() const;
         void* get_on_exit_callback_func_user_data() const;
         int get_surface_width() const;
         int get_surface_height() const;
         int get_base_font_size() const;
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_model_bin(AllegroFlare::ModelBin* model_bin=nullptr);
         void set_display_settings_interface(AllegroFlare::DisplaySettingsInterfaces::Base* display_settings_interface=nullptr);
         void initialize();
         void exit_screen();
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void deactivate_up_down_keypress_repeat_tracking();
         void move_cursor_up();
         void move_cursor_down();
         void move_cursor_left();
         void move_cursor_right();
         int infer_num_elements();
         int infer_current_element_depth();
         bool is_cursor_at(int x=0, int y=0);
         void activate_current_option();
         void increment_current_option();
         void decrement_current_option();
         void update();
         void render();
         void do_manual_key_repat_logic();
         virtual void primary_update_func(double time_now=0.0, double delta_time=0.0) override;
         virtual void primary_render_func() override;
         static void draw_cursor_pointer(float x=0.0f, float y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
         void draw_label(std::string label="[unset-label]", float x=0.0f, float y=0.0f);
         void draw_helper_text(std::string text="[unset-text]", float x=0.0f, float y=0.0f, float width=712.0f);
         void draw_slider_toggle_box(bool onoff=true, float x=0.0f, float y=0.0f);
         void draw_int_spinner(int number=1920, bool selected=false, float x=0.0f, float y=0.0f, bool disabled=false);
         virtual void virtual_control_button_up_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_axis_change_func(ALLEGRO_EVENT* ev=nullptr) override;
         bool obtain_fullscreen_status();
         bool obtain_screensaver_inhibited();
         bool obtain_mouse_cursor_hidden();
         std::pair<int, int> obtain_window_dimensions();
         std::pair<int, int> obtain_display_dimensions();
      };
   }
}



