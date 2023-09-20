#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <cstdint>
#include <string>
#include <vector>


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
         std::string get_standard_dialog_box_font_name() const;
         int get_standard_dialog_box_font_size() const;
         AllegroFlare::Elements::DialogBoxes::Base* &get_active_dialog_ref();
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void initialize();
         void update(float time_now=0);
         bool a_dialog_is_active();
         void render();
         void process_dialog_event(uint32_t user_event=0, void* raw_data1_assumed_to_be_game_event_data=nullptr);
         void emit_dialog_switch_in_event();
         void emit_dialog_switch_out_event();
         void spawn_basic_dialog(std::vector<std::string> pages={});
         void spawn_you_got_an_item_dialog(std::string item_name="[unset-item_name]", std::string item_bitmap_identifier="[unset-item_bitmap_identifier]");
         void spawn_you_got_new_evidence_dialog(std::string evidence_name="[unset-evidence_name]", std::string evidence_bitmap_identifier="[unset-evidence_bitmap_identifier]");
         void dialog_advance();
         bool dialog_is_finished();
         bool shutdown_dialog();
         void move_cursor_up();
         void move_cursor_down();
      };
   }
}



