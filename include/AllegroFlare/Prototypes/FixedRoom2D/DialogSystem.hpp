#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <allegro5/allegro_font.h>
#include <string>


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
            AllegroFlare::Elements::DialogBoxes::Base* active_dialog;
            bool initialized;
            ALLEGRO_FONT* obtain_font();

         protected:


         public:
            DialogSystem(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
            ~DialogSystem();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_font_bin(AllegroFlare::FontBin* font_bin);
            AllegroFlare::Elements::DialogBoxes::Base* &get_active_dialog_ref();
            void initialize();
            void update();
            bool a_dialog_is_active();
            void render();
            void process_game_event(AllegroFlare::GameEvent* game_event=nullptr);
            bool process_script_event(AllegroFlare::GameEventDatas::Base* game_event_data=nullptr);
            void process_dialog_event(AllegroFlare::GameEventDatas::Base* game_event_data=nullptr);
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



