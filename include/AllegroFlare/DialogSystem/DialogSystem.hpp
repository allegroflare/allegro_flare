#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/DialogSystemDrivers/Base.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <AllegroFlare/DialogTree/Nodes/ChapterTitle.hpp>
#include <AllegroFlare/DialogTree/Nodes/EmitGameEvent.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitProgram.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/DialogTree/Nodes/RawScriptLine.hpp>
#include <AllegroFlare/DialogTree/Nodes/Wait.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <tuple>
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
         static constexpr float DEFAULT_STANDARD_DIALOG_BOX_X = 1920/2.0f;
         static constexpr float DEFAULT_STANDARD_DIALOG_BOX_Y = 1080/8.0f*6;
         static constexpr float DEFAULT_STANDARD_DIALOG_BOX_WIDTH = 1920/2.0f;
         static constexpr float DEFAULT_STANDARD_DIALOG_BOX_HEIGHT = 1080/5.0f;

      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::DialogTree::NodeBank dialog_node_bank;
         AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;
         AllegroFlare::DialogTree::Nodes::Base* active_dialog_node;
         std::string active_dialog_node_name;
         AllegroFlare::Elements::DialogBoxes::Base* active_dialog_box;
         AllegroFlare::DialogSystemDrivers::Base* driver;
         bool switched_in;
         std::string standard_dialog_box_font_name;
         int standard_dialog_box_font_size;
         float standard_dialog_box_x;
         float standard_dialog_box_y;
         float standard_dialog_box_width;
         float standard_dialog_box_height;
         bool initialized;

      protected:


      public:
         DialogSystem(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr);
         ~DialogSystem();

         void set_standard_dialog_box_font_name(std::string standard_dialog_box_font_name);
         void set_standard_dialog_box_font_size(int standard_dialog_box_font_size);
         void set_standard_dialog_box_x(float standard_dialog_box_x);
         void set_standard_dialog_box_y(float standard_dialog_box_y);
         void set_standard_dialog_box_width(float standard_dialog_box_width);
         void set_standard_dialog_box_height(float standard_dialog_box_height);
         AllegroFlare::EventEmitter* get_event_emitter() const;
         AllegroFlare::DialogTree::NodeBank get_dialog_node_bank() const;
         AllegroFlare::DialogTree::Nodes::Base* get_active_dialog_node() const;
         std::string get_active_dialog_node_name() const;
         AllegroFlare::Elements::DialogBoxes::Base* get_active_dialog_box() const;
         AllegroFlare::DialogSystemDrivers::Base* get_driver() const;
         bool get_switched_in() const;
         std::string get_standard_dialog_box_font_name() const;
         int get_standard_dialog_box_font_size() const;
         float get_standard_dialog_box_x() const;
         float get_standard_dialog_box_y() const;
         float get_standard_dialog_box_width() const;
         float get_standard_dialog_box_height() const;
         bool get_initialized() const;
         AllegroFlare::DialogSystemDrivers::Base* &get_driver_ref();
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void set_driver(AllegroFlare::DialogSystemDrivers::Base* driver=nullptr);
         void clear_and_reset();
         void set_dialog_node_bank(AllegroFlare::DialogTree::NodeBank dialog_node_bank={});
         void load_dialog_node_bank_from_file(std::string filename="[unset-filename]");
         void initialize();
         void destroy();
         void switch_in();
         void switch_in_if_not();
         void switch_out();
         void activate_EmitGameEvent_dialog_node(AllegroFlare::DialogTree::Nodes::EmitGameEvent* node=nullptr);
         void activate_RawScriptLine_dialog_node(AllegroFlare::DialogTree::Nodes::RawScriptLine* node=nullptr);
         void activate_Wait_dialog_node(AllegroFlare::DialogTree::Nodes::Wait* node=nullptr);
         void activate_ChapterTitle_dialog_node(AllegroFlare::DialogTree::Nodes::ChapterTitle* node=nullptr);
         void activate_ExitDialog_dialog_node(AllegroFlare::DialogTree::Nodes::ExitDialog* node=nullptr);
         void activate_ExitProgram_dialog_node(AllegroFlare::DialogTree::Nodes::ExitProgram* node=nullptr);
         void activate_MultipageWithOptions_dialog_node(AllegroFlare::DialogTree::Nodes::MultipageWithOptions* node=nullptr, std::string node_identifier="[unset-node_identifier-for-MultipageWithOptions]");
         void activate_dialog_node(AllegroFlare::DialogTree::Nodes::Base* dialog_node=nullptr);
         void activate_dialog_node_by_name(std::string dialog_name="[unset-dialog_name]");
         void advance_MultipageWithOptions_dialog_node(AllegroFlare::DialogTree::Nodes::MultipageWithOptions* node=nullptr, int cursor_position=0);
         void dialog_advance();
         void activate_dialog_option(int selection_choice=0);
         void spawn_basic_dialog(std::string speaking_character="[unset-speaking_character]", std::vector<std::string> pages={});
         void spawn_intertitle_dialog(std::string text="[unset-text]");
         void spawn_text_messages_dialog(std::vector<std::tuple<std::string, std::string, float>> messages={});
         void spawn_wait_dialog(float duration_seconds=1.0f);
         void spawn_chapter_title_dialog(std::string title_text="[unset-title_text]", float duration_seconds=1.0f);
         void spawn_character_feature_dialog(std::string character_name="[unset-character_name]", std::string character_description="[unset-character_description]", std::string character_image_identifier="[unset-character_image_identifier]", float duration_seconds=6.0f);
         void spawn_choice_dialog(std::string speaking_character="[unset-speaking_character]", std::string prompt="[unset-prompt]", std::vector<std::string> options={}, int cursor_position_on_spawn=0);
         void update(float time_now=0);
         void render();
         bool a_dialog_is_active();
         bool dialog_is_finished();
         bool shutdown();
         void move_dialog_cursor_position_up();
         void move_dialog_cursor_position_down();
         void handle_raw_ALLEGRO_EVENT_that_is_dialog_event(ALLEGRO_EVENT* ev=nullptr, AllegroFlare::GameEventDatas::Base* data=nullptr);
      };
   }
}



