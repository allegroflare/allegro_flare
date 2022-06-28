#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>


namespace AllegroFlare
{
   namespace Screens
   {
      class GameWonScreen : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::FontBin* font_bin;

      public:
         GameWonScreen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
         virtual ~GameWonScreen();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         virtual void primary_timer_func() override;
         void render();
         void draw_primary_text();
         void draw_instruction_text();
         void return_to_title_screen();
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_instruction_font();
         virtual void key_char_func(ALLEGRO_EVENT* event=nullptr) override;
      };
   }
}



