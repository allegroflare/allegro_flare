#pragma once


#include <AllegroFlare/Elements/Storyboard.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
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
         bool auto_advance;
         std::string game_event_name_to_emit_after_completing;
         bool initialized;
         void emit_completion_event();

      protected:


      public:
         Storyboard(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, std::string game_event_name_to_emit_after_completing="storyboard_finished");
         virtual ~Storyboard();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_auto_advance(bool auto_advance);
         void set_game_event_name_to_emit_after_completing(std::string game_event_name_to_emit_after_completing);
         bool get_auto_advance() const;
         std::string get_game_event_name_to_emit_after_completing() const;
         AllegroFlare::Elements::Storyboard &get_storyboard_element_ref();
         void initialize();
         virtual void on_activate() override;
         virtual void primary_timer_func() override;
         void advance();
         virtual void virtual_control_button_down_func(int player_num=0, int button_num=0, bool is_repeat=false) override;
      };
   }
}



