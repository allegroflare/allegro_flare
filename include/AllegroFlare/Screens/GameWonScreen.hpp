#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
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
         std::string title_text;
         std::string title_font_name;
         int title_font_size;
         std::string instruction_font_name;
         int instruction_font_size;
         std::string game_event_name_to_emit_on_submission;
         static std::string DEFAULT_TITLE_TEXT;
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_instruction_font();

      protected:


      public:
         GameWonScreen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::string title_text=DEFAULT_TITLE_TEXT, std::string title_font_name="Inter-Medium.ttf", int title_font_size=-80, std::string instruction_font_name="Inter-Medium.ttf", int instruction_font_size=-48, std::string game_event_name_to_emit_on_submission="game_won_finished");
         virtual ~GameWonScreen();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_title_text(std::string title_text);
         void set_title_font_name(std::string title_font_name);
         void set_title_font_size(int title_font_size);
         void set_instruction_font_name(std::string instruction_font_name);
         void set_instruction_font_size(int instruction_font_size);
         void set_game_event_name_to_emit_on_submission(std::string game_event_name_to_emit_on_submission);
         std::string get_title_font_name() const;
         int get_title_font_size() const;
         std::string get_instruction_font_name() const;
         int get_instruction_font_size() const;
         std::string get_game_event_name_to_emit_on_submission() const;
         virtual void primary_timer_func() override;
         void render();
         void draw_primary_text();
         void draw_instruction_text();
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
      };
   }
}



