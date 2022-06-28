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
      class GameOverScreen : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::FontBin* font_bin;
         std::vector<std::pair<std::string, std::string>> menu_options;
         int cursor_position;
         bool initialized;

      public:
         GameOverScreen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
         virtual ~GameOverScreen();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         bool get_initialized();
         void initialize();
         void move_cursor_up();
         void move_cursor_down();
         void select_menu_option();
         virtual void primary_timer_func() override;
         void render();
         void draw_primary_text();
         void draw_menu();
         std::string infer_current_menu_option_value();
         std::string infer_current_menu_option_label();
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_menu_font();
         virtual void key_char_func(ALLEGRO_EVENT* event=nullptr) override;
      };
   }
}



