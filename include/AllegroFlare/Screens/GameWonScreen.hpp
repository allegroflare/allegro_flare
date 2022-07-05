#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Screens
   {
      class GameWonScreen : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::FontBin* font_bin;
         std::string game_event_name_to_emit_on_submission;

      public:
         GameWonScreen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::string game_event_name_to_emit_on_submission="game_won_finished");
         virtual ~GameWonScreen();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_game_event_name_to_emit_on_submission(std::string game_event_name_to_emit_on_submission);
         std::string get_game_event_name_to_emit_on_submission();
         virtual void primary_timer_func() override;
         void render();
         void draw_primary_text();
         void draw_instruction_text();
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_instruction_font();
         virtual void virtual_control_button_down_func(int player_num=0, int button_num=0, bool is_repeat=false) override;
      };
   }
}



