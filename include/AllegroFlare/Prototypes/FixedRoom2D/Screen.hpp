#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Configuration.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/FixedRoom2D.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class Screen : public AllegroFlare::Screens::Base
         {
         public:
            static constexpr char* DEFAULT_EVENT_NAME_ON_EXIT = "exit_fixed_room_2d_screen";
            static constexpr char* DEFAULT_EVENT_NAME_TO_OPEN_CHRONICLE = "open_chronicle";

         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D fixed_room_2d;
            bool initialized;
            std::string game_event_name_to_emit_on_exit;
            std::string game_event_name_to_emit_to_open_chronicle;
            void emit_event_to_set_input_hints();
            void emit_event_to_set_input_hints_bar_to_inventory_controls();
            void emit_event_to_set_input_hints_bar_to_room_controls();

         protected:


         public:
            Screen(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, std::string game_event_name_to_emit_on_exit=DEFAULT_EVENT_NAME_ON_EXIT, std::string game_event_name_to_emit_to_open_chronicle=DEFAULT_EVENT_NAME_TO_OPEN_CHRONICLE);
            virtual ~Screen();

            void set_game_event_name_to_emit_on_exit(std::string game_event_name_to_emit_on_exit);
            void set_game_event_name_to_emit_to_open_chronicle(std::string game_event_name_to_emit_to_open_chronicle);
            std::string get_game_event_name_to_emit_on_exit() const;
            std::string get_game_event_name_to_emit_to_open_chronicle() const;
            AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D &get_fixed_room_2d_ref();
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
            void initialize();
            void load_gametest_configuration();
            void load_configuration(AllegroFlare::Prototypes::FixedRoom2D::Configuration configuration={});
            bool enter_start_room();
            virtual void on_activate() override;
            virtual void game_event_func(AllegroFlare::GameEvent* game_event=nullptr) override;
            virtual void on_deactivate() override;
            virtual void primary_timer_func() override;
            virtual void key_char_func(ALLEGRO_EVENT* ev=nullptr) override;
            void emit_event_to_exit();
            void emit_event_to_open_chronicle();
         };
      }
   }
}



