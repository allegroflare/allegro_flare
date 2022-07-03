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
         intptr_t current_page_num;

      public:
         Storyboard(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, std::vector<std::string> pages={}, std::string screen_identifier_to_switch_to_after_completing="", intptr_t current_page_num=0);
         virtual ~Storyboard();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_pages(std::vector<std::string> pages);
         void set_screen_identifier_to_switch_to_after_completing(std::string screen_identifier_to_switch_to_after_completing);
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



