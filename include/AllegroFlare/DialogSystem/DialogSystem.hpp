#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/DialogTree/Node.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
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
         AllegroFlare::DialogTree::NodeBank dialog_node_bank;
         AllegroFlare::Elements::DialogBoxes::Base* active_dialog_box;
         AllegroFlare::DialogTree::Node* active_dialog_node;
         std::string active_dialog_node_name;
         bool switched_in;
         std::string standard_dialog_box_font_name;
         int standard_dialog_box_font_size;
         bool initialized;

      protected:


      public:
         DialogSystem(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, std::string standard_dialog_box_font_name=DEFAULT_STANDARD_DIALOG_BOX_FONT_NAME, int standard_dialog_box_font_size=DEFAULT_STANDARD_DIALOG_BOX_FONT_SIZE);
         ~DialogSystem();

         void set_standard_dialog_box_font_name(std::string standard_dialog_box_font_name);
         void set_standard_dialog_box_font_size(int standard_dialog_box_font_size);
         AllegroFlare::DialogTree::NodeBank get_dialog_node_bank() const;
         bool get_switched_in() const;
         std::string get_standard_dialog_box_font_name() const;
         int get_standard_dialog_box_font_size() const;
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void load_dialog_node_bank_from_file(std::string filename="[unset-filename]");
         void initialize();
         void switch_in();
         void switch_out();
         void spawn_named_dialog(std::string dialog_name="[unset-dialog_name]");
         void spawn_basic_dialog(std::vector<std::string> pages={});
         void update(float time_now=0);
         void render();
         bool a_dialog_is_active();
         void dialog_advance();
         void activate_dialog_option(int selection_choice=0);
         bool dialog_is_finished();
         bool shutdown_dialog();
         void move_dialog_cursor_position_up();
         void move_dialog_cursor_position_down();
         void move_dialog_cursor_position_left();
         void move_dialog_cursor_position_right();
      };
   }
}



