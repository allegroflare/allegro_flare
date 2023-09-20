#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      class DialogSystem
      {
      public:
         static constexpr char* DEFAULT_STANDARD_DIALOG_BOX_FONT_NAME = (char*)"Inter-Regular.ttf";
         static constexpr int DEFAULT_STANDARD_DIALOG_BOX_FONT_SIZE = -36;

      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::Elements::DialogBoxes::Base* active_dialog;
         bool switched_in;
         std::string standard_dialog_box_font_name;
         int standard_dialog_box_font_size;
         bool initialized;
         void dialog_cursor_up();
         void dialog_cursor_down();

      protected:


      public:
         DialogSystem(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, std::string standard_dialog_box_font_name=DEFAULT_STANDARD_DIALOG_BOX_FONT_NAME, int standard_dialog_box_font_size=DEFAULT_STANDARD_DIALOG_BOX_FONT_SIZE);
         ~DialogSystem();

         void set_standard_dialog_box_font_name(std::string standard_dialog_box_font_name);
         void set_standard_dialog_box_font_size(int standard_dialog_box_font_size);
         bool get_switched_in() const;
         std::string get_standard_dialog_box_font_name() const;
         int get_standard_dialog_box_font_size() const;
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void initialize();
         void switch_in();
         void switch_out();
         void update(float time_now=0);
         bool a_dialog_is_active();
         void render();
         void dialog_advance();
         bool dialog_is_finished();
         void emit_dialog_switch_out_event();
         void emit_dialog_switch_in_event();
         bool shutdown_dialog();
         void move_cursor_up();
         void move_cursor_down();
      };
   }
}



