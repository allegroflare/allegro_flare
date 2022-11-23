#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <allegro5/allegro_font.h>


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
            void process_dialog_event(AllegroFlare::GameEventDatas::Base* game_event_data=nullptr);
            ALLEGRO_FONT* obtain_font();

         protected:


         public:
            DialogSystem(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
            ~DialogSystem();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void initialize();
            void update();
            void render();
            void process_game_event(AllegroFlare::GameEvent* game_event=nullptr);
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



