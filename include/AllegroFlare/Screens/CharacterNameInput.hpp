#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/SoftwareKeyboard/SoftwareKeyboard.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


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
         void set_font_name(std::string font_name=AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::DEFAULT_FONT_NAME);
         void set_font_size(int font_size=1);
         void set_event_to_emit_on_pressing_ok_key(std::string event_to_emit_on_pressing_ok_key=AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::DEFAULT_EVENT_TO_EMIT_ON_PRESSING_OK_KEY);
         bool mode_is_using_keyboard();
         bool mode_is_using_virtual_controls();
         void set_mode_to_using_keyboard();
         void set_mode_to_using_virtual_controls();
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void key_char_func(ALLEGRO_EVENT* event=nullptr) override;
         void render();
      };
   }
}



