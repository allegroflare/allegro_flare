#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Configuration.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/FixedRoom2D.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class Screen : public AllegroFlare::Screens::Base
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D fixed_room_2d;
            bool initialized;
            void emit_event_to_set_input_hints();
            void emit_event_to_set_input_hints_bar_to_inventory_controls();
            void emit_event_to_set_input_hints_bar_to_room_controls();

         protected:


         public:
            Screen(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr);
            virtual ~Screen();

            AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D &get_fixed_room_2d_ref();
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
            void initialize();
            void load_gametest_configuration_and_start();
            void load_game_configuration_and_start(AllegroFlare::Prototypes::FixedRoom2D::Configuration configuration={});
            virtual void on_activate() override;
            virtual void game_event_func(AllegroFlare::GameEvent* game_event=nullptr) override;
            virtual void on_deactivate() override;
            virtual void primary_timer_func() override;
            virtual void key_char_func(ALLEGRO_EVENT* ev=nullptr) override;
         };
      }
   }
}



