#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Screens
   {
      class TitleScreen : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::FontBin* font_bin;
         std::string title_text;
         std::string copyright_text;
         std::vector<std::pair<std::string, std::string>> menu_options;
         int cursor_position;

      public:
         TitleScreen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::string title_text="Untitled Game", std::string copyright_text="Copyright 2022");
         virtual ~TitleScreen();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         std::string get_title_text();
         std::string get_copyright_text();
         std::vector<std::pair<std::string, std::string>> get_menu_options();
         void set_menu_options(std::vector<std::pair<std::string, std::string>> menu_options={});
         void move_cursor_up();
         void move_cursor_down();
         virtual void activate_menu_option(std::string menu_option_name="[unset-menu-option-name]");
         void select_menu_option();
         virtual void primary_timer_func() override;
         void render();
         void draw_title_text();
         void draw_copyright_text();
         void draw_menu();
         std::string infer_current_menu_option_value();
         std::string infer_current_menu_option_label();
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_menu_font();
         ALLEGRO_FONT* obtain_copyright_font();
         virtual void key_char_func(ALLEGRO_EVENT* event=nullptr) override;
         bool menu_is_empty();
         bool menu_has_items();
         static std::vector<std::pair<std::string, std::string>> build_default_menu_options();
      };
   }
}



