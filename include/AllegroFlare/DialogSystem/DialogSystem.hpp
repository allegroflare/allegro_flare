#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/DialogSystem/CharacterRoster.hpp>
#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Base.hpp>
#include <AllegroFlare/DialogSystem/NodeStates/Base.hpp>
#include <AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/Elements/DialogRoll.hpp>
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

      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::DialogTree::NodeBank dialog_node_bank;
         AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver driver;
         AllegroFlare::DialogSystem::CharacterRoster* character_roster;
         AllegroFlare::Elements::DialogBoxes::Base* active_dialog_box;
         AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;
         AllegroFlare::DialogTree::Nodes::Base* active_dialog_node;
         std::string active_dialog_node_name;
         AllegroFlare::DialogSystem::NodeStates::Base* active_dialog_node_state;
         AllegroFlare::DialogSystem::CharacterStagingLayouts::Base* active_character_staging_layout;
         std::function<bool(std::string, AllegroFlare::DialogTree::NodeBank*, void*)> load_node_bank_func;
         AllegroFlare::Elements::DialogRoll dialog_roll;
         void* load_node_bank_func_user_data;
         std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, std::string, AllegroFlare::DialogTree::Nodes::Base*, void*)> activate_dialog_node_by_name_func;
         void* activate_dialog_node_by_name_func_user_data;
         std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, void*)> activate_dialog_node_type_unhandled_func;
         void* activate_dialog_node_type_unhandled_func_user_data;
         std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, AllegroFlare::Elements::DialogBoxes::Base*, AllegroFlare::DialogTree::Nodes::Base*, void*)> dialog_advance_is_finished_node_type_unhandled_func;
         void* dialog_advance_is_finished_node_type_unhandled_func_user_data;
         bool switched_in;
         std::string standard_dialog_box_font_name;
         int standard_dialog_box_font_size;
         bool initialized;

      protected:


      public:
         DialogSystem(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::DialogSystem::CharacterRoster* character_roster=nullptr);
         ~DialogSystem();

         void set_character_roster(AllegroFlare::DialogSystem::CharacterRoster* character_roster);
         void set_load_node_bank_func(std::function<bool(std::string, AllegroFlare::DialogTree::NodeBank*, void*)> load_node_bank_func);
         void set_dialog_roll(AllegroFlare::Elements::DialogRoll dialog_roll);
         void set_load_node_bank_func_user_data(void* load_node_bank_func_user_data);
         void set_activate_dialog_node_by_name_func(std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, std::string, AllegroFlare::DialogTree::Nodes::Base*, void*)> activate_dialog_node_by_name_func);
         void set_activate_dialog_node_by_name_func_user_data(void* activate_dialog_node_by_name_func_user_data);
         void set_activate_dialog_node_type_unhandled_func(std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, void*)> activate_dialog_node_type_unhandled_func);
         void set_activate_dialog_node_type_unhandled_func_user_data(void* activate_dialog_node_type_unhandled_func_user_data);
         void set_dialog_advance_is_finished_node_type_unhandled_func(std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, AllegroFlare::Elements::DialogBoxes::Base*, AllegroFlare::DialogTree::Nodes::Base*, void*)> dialog_advance_is_finished_node_type_unhandled_func);
         void set_dialog_advance_is_finished_node_type_unhandled_func_user_data(void* dialog_advance_is_finished_node_type_unhandled_func_user_data);
         void set_standard_dialog_box_font_name(std::string standard_dialog_box_font_name);
         void set_standard_dialog_box_font_size(int standard_dialog_box_font_size);
         AllegroFlare::EventEmitter* get_event_emitter() const;
         AllegroFlare::DialogTree::NodeBank get_dialog_node_bank() const;
         AllegroFlare::DialogSystem::CharacterRoster* get_character_roster() const;
         std::string get_active_dialog_node_name() const;
         std::function<bool(std::string, AllegroFlare::DialogTree::NodeBank*, void*)> get_load_node_bank_func() const;
         AllegroFlare::Elements::DialogRoll get_dialog_roll() const;
         void* get_load_node_bank_func_user_data() const;
         std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, std::string, AllegroFlare::DialogTree::Nodes::Base*, void*)> get_activate_dialog_node_by_name_func() const;
         void* get_activate_dialog_node_by_name_func_user_data() const;
         std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, void*)> get_activate_dialog_node_type_unhandled_func() const;
         void* get_activate_dialog_node_type_unhandled_func_user_data() const;
         std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, AllegroFlare::Elements::DialogBoxes::Base*, AllegroFlare::DialogTree::Nodes::Base*, void*)> get_dialog_advance_is_finished_node_type_unhandled_func() const;
         void* get_dialog_advance_is_finished_node_type_unhandled_func_user_data() const;
         bool get_switched_in() const;
         std::string get_standard_dialog_box_font_name() const;
         int get_standard_dialog_box_font_size() const;
         AllegroFlare::Elements::DialogRoll &get_dialog_roll_ref();
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void set_dialog_node_bank(AllegroFlare::DialogTree::NodeBank dialog_node_bank={});
         void load_dialog_node_bank_from_file(std::string filename="[unset-filename]");
         void initialize();
         void destroy();
         void switch_in();
         void switch_out();
         void clear_character_staging_layout();
         void set_speaking_character_avatar(std::string speaking_character_identifier="[unset-speaking_character_identifier]", std::string speaking_character_expression="[unset-speaking_character_expression]");
         ALLEGRO_BITMAP* lookup_speaking_character_avatar(std::string speaking_character_identifier="[unset-speaking_character_identifier]", std::string speaking_character_expression="[unset-speaking_character_expression]");
         void append_to_dialog_roll(std::string speaking_character="[unset-speaking_character]", std::string dialog="[unset-dialog]");
         void activate_dialog_node_by_name(std::string dialog_name="[unset-dialog_name]");
         void spawn_basic_dialog(std::string speaking_character="[unset-speaking_character]", std::vector<std::string> pages={});
         void spawn_choice_dialog(std::string speaking_character="[unset-speaking_character]", std::string prompt="[unset-prompt]", std::vector<std::string> options={});
         void update(float time_now=0);
         void evaluate_auto_advance_on_dialog_node_state();
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



