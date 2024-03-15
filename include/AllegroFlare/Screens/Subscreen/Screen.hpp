#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/Subscreen/Element.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>


namespace AllegroFlare
{
   namespace Screens
   {
      namespace Subscreen
      {
         class Screen : public AllegroFlare::Screens::Base
         {
         private:
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::Screens::Subscreen::Element* subscreen_element;
            bool initialized;
            virtual void emit_event_to_update_input_hints_bar();

         protected:


         public:
            Screen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Screens::Subscreen::Element* subscreen_element=nullptr);
            virtual ~Screen();

            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_subscreen_element(AllegroFlare::Screens::Subscreen::Element* subscreen_element);
            AllegroFlare::EventEmitter* get_event_emitter() const;
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            AllegroFlare::Screens::Subscreen::Element* get_subscreen_element() const;
            bool get_initialized() const;
            void initialize();
            void refresh();
            virtual void on_activate() override;
            virtual void on_deactivate() override;
            void set_background_bitmap(ALLEGRO_BITMAP* background_bitmap=nullptr);
            void emit_show_and_size_input_hints_bar_event();
            void emit_hide_and_restore_size_input_hints_bar_event();
            void move_pane_left();
            void move_pane_right();
            virtual void primary_update_func(double time_now=0.0f, double delta_time=1.0f) override;
            virtual void primary_render_func() override;
            void xprimary_timer_func();
            virtual void key_up_func(ALLEGRO_EVENT* event=nullptr) override;
            virtual void key_down_func(ALLEGRO_EVENT* event=nullptr) override;
            virtual void key_char_func(ALLEGRO_EVENT* event=nullptr) override;
         };
      }
   }
}



