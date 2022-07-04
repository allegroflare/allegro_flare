#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Screens
   {
      class Storyboard : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::EventEmitter* event_emitter;
         std::vector<std::string> pages;
         std::string screen_identifier_to_switch_to_after_completing;
         std::string font_name;
         int font_size;
         ALLEGRO_COLOR text_color;
         float top_padding;
         float left_padding;
         float right_padding;
         float line_height_multiplier;
         float line_height_padding;
         intptr_t current_page_num;
         bool can_go_to_next_page;

      public:
         Storyboard(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, std::vector<std::string> pages={}, std::string screen_identifier_to_switch_to_after_completing="", std::string font_name="Inter-Medium.ttf", int font_size=-60, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{1, 1, 1, 1}, float top_padding=400, float left_padding=200, float right_padding=200, float line_height_multiplier=1.75f, float line_height_padding=0.0f, intptr_t current_page_num=0);
         virtual ~Storyboard();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_pages(std::vector<std::string> pages);
         void set_screen_identifier_to_switch_to_after_completing(std::string screen_identifier_to_switch_to_after_completing);
         void set_font_name(std::string font_name);
         void set_font_size(int font_size);
         void set_text_color(ALLEGRO_COLOR text_color);
         void set_top_padding(float top_padding);
         void set_left_padding(float left_padding);
         void set_right_padding(float right_padding);
         void set_line_height_multiplier(float line_height_multiplier);
         void set_line_height_padding(float line_height_padding);
         std::string get_font_name();
         int get_font_size();
         ALLEGRO_COLOR get_text_color();
         float get_top_padding();
         float get_left_padding();
         float get_right_padding();
         float get_line_height_multiplier();
         float get_line_height_padding();
         intptr_t get_current_page_num();
         void render();
         void reset();
         virtual void on_activate() override;
         virtual void primary_timer_func() override;
         virtual void key_down_func(ALLEGRO_EVENT* event=nullptr) override;
         ALLEGRO_FONT* obtain_font();
      };
   }
}



