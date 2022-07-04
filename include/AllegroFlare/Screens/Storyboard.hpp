#pragma once


#include <AllegroFlare/Elements/Storyboard.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Screens
   {
      class Storyboard : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::Elements::Storyboard storyboard_element;
         std::string screen_identifier_to_switch_to_after_completing;
         bool initialized;

      public:
         Storyboard(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, std::string screen_identifier_to_switch_to_after_completing="");
         virtual ~Storyboard();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_screen_identifier_to_switch_to_after_completing(std::string screen_identifier_to_switch_to_after_completing);
         AllegroFlare::Elements::Storyboard &get_storyboard_element_ref();
         void initialize();
         virtual void on_activate() override;
         virtual void primary_timer_func() override;
         virtual void key_down_func(ALLEGRO_EVENT* event=nullptr) override;
      };
   }
}



