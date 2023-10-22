#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/PauseScreen.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <functional>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Screens
   {
      class PauseScreen : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::BitmapBin* bitmap_bin;
         std::string title_text;
         std::string footer_text;
         std::function<void(AllegroFlare::Screens::PauseScreen*, void*)> on_menu_choice_callback_func;
         void* on_menu_choice_callback_func_user_data;
         std::string title_bitmap_name;
         std::string font_name;
         ALLEGRO_COLOR title_text_color;
         ALLEGRO_COLOR menu_text_color;
         ALLEGRO_COLOR menu_selector_color;
         ALLEGRO_COLOR footer_text_color;
         int title_font_size;
         int menu_font_size;
         int footer_font_size;
         bool show_footer_text;
         std::vector<std::pair<std::string, std::string>> menu_options;
         int cursor_position;
         float title_menu_gutter;
         void move_cursor_up();
         void move_cursor_down();
         void select_menu_option();
         std::string infer_current_menu_option_value();
         std::string infer_current_menu_option_label();
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_menu_font();
         ALLEGRO_FONT* obtain_footer_font();
         ALLEGRO_BITMAP* obtain_title_bitmap();
         bool menu_is_empty();
         bool menu_has_items();

      protected:


      public:
         PauseScreen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::string title_text="GAME PAUSED", std::string footer_text="", std::string title_bitmap_name="", std::string font_name="Inter-Regular.ttf", ALLEGRO_COLOR title_text_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR menu_text_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR menu_selector_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR footer_text_color=ALLEGRO_COLOR{0.2, 0.2, 0.25, 1.0}, int title_font_size=-70, int menu_font_size=-30, int footer_font_size=-28, bool show_footer_text=true);
         virtual ~PauseScreen();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_title_text(std::string title_text);
         void set_footer_text(std::string footer_text);
         void set_on_menu_choice_callback_func(std::function<void(AllegroFlare::Screens::PauseScreen*, void*)> on_menu_choice_callback_func);
         void set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data);
         void set_title_bitmap_name(std::string title_bitmap_name);
         void set_font_name(std::string font_name);
         void set_title_text_color(ALLEGRO_COLOR title_text_color);
         void set_menu_text_color(ALLEGRO_COLOR menu_text_color);
         void set_menu_selector_color(ALLEGRO_COLOR menu_selector_color);
         void set_footer_text_color(ALLEGRO_COLOR footer_text_color);
         void set_title_font_size(int title_font_size);
         void set_menu_font_size(int menu_font_size);
         void set_footer_font_size(int footer_font_size);
         void set_show_footer_text(bool show_footer_text);
         void set_title_menu_gutter(float title_menu_gutter);
         std::string get_title_text() const;
         std::string get_footer_text() const;
         std::function<void(AllegroFlare::Screens::PauseScreen*, void*)> get_on_menu_choice_callback_func() const;
         void* get_on_menu_choice_callback_func_user_data() const;
         std::string get_title_bitmap_name() const;
         std::string get_font_name() const;
         ALLEGRO_COLOR get_title_text_color() const;
         ALLEGRO_COLOR get_menu_text_color() const;
         ALLEGRO_COLOR get_menu_selector_color() const;
         ALLEGRO_COLOR get_footer_text_color() const;
         int get_title_font_size() const;
         int get_menu_font_size() const;
         int get_footer_font_size() const;
         bool get_show_footer_text() const;
         std::vector<std::pair<std::string, std::string>> get_menu_options() const;
         int get_cursor_position() const;
         float get_title_menu_gutter() const;
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void set_menu_options(std::vector<std::pair<std::string, std::string>> menu_options={});
         virtual void activate_menu_option(std::string menu_option_name="[unset-menu-option-name]");
         virtual void primary_timer_func() override;
         void render();
         void draw_title();
         void draw_footer_text();
         void draw_menu();
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         static std::vector<std::pair<std::string, std::string>> build_default_menu_options();
      };
   }
}



