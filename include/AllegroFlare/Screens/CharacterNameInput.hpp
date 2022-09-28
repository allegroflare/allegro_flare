#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/SoftwareKeyboard/SoftwareKeyboard.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Screens
   {
      class CharacterNameInput : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard;
         bool initialized;

      protected:


      public:
         CharacterNameInput(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard={});
         virtual ~CharacterNameInput();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void initialize();
         virtual void on_activate() override;
         virtual void primary_timer_func() override;
         virtual void key_char_func(ALLEGRO_EVENT* event=nullptr) override;
         void render();
      };
   }
}



