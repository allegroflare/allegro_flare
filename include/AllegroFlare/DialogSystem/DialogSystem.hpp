#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/DialogSystemDrivers/Base.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <allegro5/allegro.h>
#include <functional>
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
         static constexpr float DEFAULT_STANDARD_DIALOG_BOX_X = 1920/2.0f;
         static constexpr float DEFAULT_STANDARD_DIALOG_BOX_Y = 1080/8.0f*6;
         static constexpr float DEFAULT_STANDARD_DIALOG_BOX_WIDTH = 1920/2.0f;
         static constexpr float DEFAULT_STANDARD_DIALOG_BOX_HEIGHT = 1080/5.0f;

      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::DialogTree::NodeBank dialog_node_bank;
         AllegroFlare::Elements::DialogBoxes::Base* active_dialog_box;
         AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;
         AllegroFlare::DialogTree::Nodes::Base* active_dialog_node;
         std::string active_dialog_node_name;
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
         std::string get_active_dialog_node_name() const;
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
         void set_activate_dialog_node_type_unhandled_func(std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, void*)> activate_dialog_node_type_unhandled_func);
         void set_activate_dialog_node_type_unhandled_func_user_data(void* activate_dialog_node_type_unhandled_func_user_data=nullptr);
         void clear_and_reset();
         void set_dialog_node_bank(AllegroFlare::DialogTree::NodeBank dialog_node_bank={});
         void load_dialog_node_bank_from_file(std::string filename="[unset-filename]");
         void initialize();
         void destroy();
         void switch_in();
         void switch_in_if_not();
         void switch_out();
         void activate_dialog_node_by_name(std::string dialog_name="[unset-dialog_name]");
         void spawn_basic_dialog(std::string speaking_character="[unset-speaking_character]", std::vector<std::string> pages={});
         void spawn_wait_dialog(float duration_seconds=1.0f);
         void spawn_chapter_title_dialog(std::string title_text="[unset-title_text]", float duration_seconds=1.0f);
         void spawn_character_feature_dialog(std::string character_name="[unset-character_name]", std::string character_description="[unset-character_description]", std::string character_image_identifier="[unset-character_image_identifier]", float duration_seconds=6.0f);
         void spawn_choice_dialog(std::string speaking_character="[unset-speaking_character]", std::string prompt="[unset-prompt]", std::vector<std::string> options={}, int cursor_position_on_spawn=0);
         void update(float time_now=0);
         void render();
         bool a_dialog_is_active();
         void dialog_advance();
         void activate_dialog_option(int selection_choice=0);
         bool dialog_is_finished();
         bool shutdown_dialog();
         void move_dialog_cursor_position_up();
         void move_dialog_cursor_position_down();
         void handle_raw_ALLEGRO_EVENT_that_is_dialog_event(ALLEGRO_EVENT* ev=nullptr, AllegroFlare::GameEventDatas::Base* data=nullptr);
      };
   }
}



