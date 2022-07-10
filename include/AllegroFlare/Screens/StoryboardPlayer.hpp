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
      class StoryboardPlayer : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::Elements::Storyboard storyboard_element;
         std::string game_event_name_to_emit_after_completing;
         bool initialized;

      public:
         StoryboardPlayer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, std::string game_event_name_to_emit_after_completing="storyboard_finished");
         virtual ~StoryboardPlayer();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_game_event_name_to_emit_after_completing(std::string game_event_name_to_emit_after_completing);
         std::string get_game_event_name_to_emit_after_completing();
         AllegroFlare::Elements::Storyboard &get_storyboard_element_ref();
         void initialize();
         virtual void on_activate() override;
         virtual void primary_timer_func() override;
         void advance();
         virtual void virtual_control_button_down_func(int player_num=0, int button_num=0, bool is_repeat=false) override;
      };
   }
}



