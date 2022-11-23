#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class DialogSystem
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::Elements::DialogBoxes::Base* active_dialog;
            bool initialized;
            ALLEGRO_FONT* obtain_font();

         protected:


         public:
            DialogSystem(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr);
            ~DialogSystem();

            AllegroFlare::Elements::DialogBoxes::Base* &get_active_dialog_ref();
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
            void initialize();
            void update();
            bool a_dialog_is_active();
            void render();
            void process_game_event(AllegroFlare::GameEvent* game_event=nullptr);
            void process_dialog_event(AllegroFlare::GameEventDatas::Base* game_event_data=nullptr);
            void emit_dialog_switch_in_event();
            void emit_dialog_switch_out_event();
            void spawn_basic_dialog(std::vector<std::string> pages={});
            void spawn_you_got_an_item_dialog(std::string item_name="[unset-item_name]", std::string item_bitmap_identifier="[unset-item_bitmap_identifier]");
            void spawn_you_got_new_evidence_dialog(std::string evidence_name="[unset-evidence_name]", std::string evidence_bitmap_identifier="[unset-evidence_bitmap_identifier]");
            void dialog_advance();
            void dialog_cursor_up();
            void dialog_cursor_down();
            bool dialog_is_finished();
            bool shutdown_dialog();
            void move_cursor_up();
            void move_cursor_down();
         };
      }
   }
}



