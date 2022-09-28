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
      public:
         static constexpr int MODE_USING_VIRTUAL_CONTROLS = 1;
         static constexpr int MODE_USING_KEYBOARD = 2;

      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard;
         int mode;
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
         bool mode_is_using_keyboard();
         bool mode_is_using_virtual_controls();
         void set_mode_to_using_keyboard();
         void set_mode_to_using_virtual_controls();
         virtual void virtual_control_button_down_func(int player_num=0, int button_num=0, bool is_repeat=false) override;
         virtual void key_char_func(ALLEGRO_EVENT* event=nullptr) override;
         void render();
      };
   }
}



