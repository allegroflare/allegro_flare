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
         intptr_t current_page;

      public:
         Storyboard(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, std::vector<std::string> pages={}, std::string screen_identifier_to_switch_to_after_completing="", intptr_t current_page=0);
         virtual ~Storyboard();

         void render();
         void reset();
         virtual void on_activate() override;
         virtual void primary_timer_func() override;
         virtual void key_down_func(ALLEGRO_EVENT* event=nullptr) override;
         ALLEGRO_FONT* obtain_font();
      };
   }
}



