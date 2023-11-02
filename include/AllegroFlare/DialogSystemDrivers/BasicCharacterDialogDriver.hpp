#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/DialogSystem/ChapterIndex.hpp>
#include <AllegroFlare/DialogSystem/CharacterRoster.hpp>
#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Base.hpp>
#include <AllegroFlare/DialogSystem/Characters/Basic.hpp>
#include <AllegroFlare/DialogSystem/DialogSystem.hpp>
#include <AllegroFlare/DialogSystem/SceneIndex.hpp>
#include <AllegroFlare/DialogSystemDrivers/Base.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/Elements/DialogRoll.hpp>
#include <allegro5/allegro.h>
#include <functional>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystemDrivers
   {
      class BasicCharacterDialogDriver : public AllegroFlare::DialogSystemDrivers::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver";

      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::Elements::DialogRoll dialog_roll;
         std::function<bool( AllegroFlare::DialogSystem::DialogSystem*, std::string, AllegroFlare::DialogTree::Nodes::Base*, void*) > handle_activate_dialog_from_raw_script_line_func;
         void* handle_activate_dialog_from_raw_script_line_func_user_data;
         std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, AllegroFlare::Elements::DialogBoxes::Base*, AllegroFlare::DialogTree::Nodes::Base*, void*)> handle_finished_dialog_from_raw_script_line_func;
         void* handle_finished_dialog_from_raw_script_line_func_user_data;
         std::function<bool(std::string, AllegroFlare::DialogTree::NodeBank*, void*)> handle_load_node_bank_from_file_func;
         void* handle_load_node_bank_from_file_func_user_data;
         bool initialized;

      protected:


      public:
         AllegroFlare::DialogSystem::CharacterStagingLayouts::Base* active_character_staging_layout;
         AllegroFlare::DialogSystem::CharacterRoster* character_roster;
         AllegroFlare::DialogSystem::SceneIndex* scene_index;
         AllegroFlare::DialogSystem::ChapterIndex* chapter_index;
         BasicCharacterDialogDriver(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         virtual ~BasicCharacterDialogDriver();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_dialog_roll(AllegroFlare::Elements::DialogRoll dialog_roll);
         void set_handle_activate_dialog_from_raw_script_line_func(std::function<bool( AllegroFlare::DialogSystem::DialogSystem*, std::string, AllegroFlare::DialogTree::Nodes::Base*, void*) > handle_activate_dialog_from_raw_script_line_func);
         void set_handle_activate_dialog_from_raw_script_line_func_user_data(void* handle_activate_dialog_from_raw_script_line_func_user_data);
         void set_handle_finished_dialog_from_raw_script_line_func(std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, AllegroFlare::Elements::DialogBoxes::Base*, AllegroFlare::DialogTree::Nodes::Base*, void*)> handle_finished_dialog_from_raw_script_line_func);
         void set_handle_finished_dialog_from_raw_script_line_func_user_data(void* handle_finished_dialog_from_raw_script_line_func_user_data);
         void set_handle_load_node_bank_from_file_func(std::function<bool(std::string, AllegroFlare::DialogTree::NodeBank*, void*)> handle_load_node_bank_from_file_func);
         void set_handle_load_node_bank_from_file_func_user_data(void* handle_load_node_bank_from_file_func_user_data);
         AllegroFlare::Elements::DialogRoll get_dialog_roll() const;
         std::function<bool( AllegroFlare::DialogSystem::DialogSystem*, std::string, AllegroFlare::DialogTree::Nodes::Base*, void*) > get_handle_activate_dialog_from_raw_script_line_func() const;
         void* get_handle_activate_dialog_from_raw_script_line_func_user_data() const;
         std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, AllegroFlare::Elements::DialogBoxes::Base*, AllegroFlare::DialogTree::Nodes::Base*, void*)> get_handle_finished_dialog_from_raw_script_line_func() const;
         void* get_handle_finished_dialog_from_raw_script_line_func_user_data() const;
         std::function<bool(std::string, AllegroFlare::DialogTree::NodeBank*, void*)> get_handle_load_node_bank_from_file_func() const;
         void* get_handle_load_node_bank_from_file_func_user_data() const;
         AllegroFlare::Elements::DialogRoll &get_dialog_roll_ref();
         void initialize();
         void destroy();
         virtual void on_switch_in() override;
         virtual void on_switch_out() override;
         virtual void on_load_node_bank_from_file(AllegroFlare::DialogSystem::DialogSystem* dialog_system=nullptr, std::string activating_node_name="[unset-activating_node_name]") override;
         virtual void on_render() override;
         virtual void on_before_spawn_basic_dialog(std::string speaking_character_identifier="[unset-speaking_character_identifier]") override;
         virtual void on_before_spawn_choice_dialog(std::string speaking_character_identifier="[unset-speaking_character_identifier]") override;
         virtual void on_raw_script_line_activate(AllegroFlare::DialogSystem::DialogSystem* dialog_system=nullptr, std::string activating_node_name="[unset-activating_node_name]", AllegroFlare::DialogTree::Nodes::Base* activating_node=nullptr, void* user_data=nullptr) override;
         virtual void on_raw_script_line_finished(AllegroFlare::DialogSystem::DialogSystem* dialog_system=nullptr, AllegroFlare::Elements::DialogBoxes::Base* active_dialog_box=nullptr, AllegroFlare::DialogTree::Nodes::Base* active_dialog_node=nullptr) override;
         virtual std::string decorate_speaking_character_name(std::string speaking_character_identifier="[unset-speaking_character_identifier]") override;
         void clear_character_staging_layout();
         AllegroFlare::DialogSystem::Characters::Basic* find_character_by_identifier_as_Basic(std::string character_identifier="[unset-character_identifier]");
         void set_speaking_character_avatar(std::string speaking_character_identifier="[unset-speaking_character_identifier]", std::string speaking_character_expression="[unset-speaking_character_expression]");
         ALLEGRO_BITMAP* lookup_speaking_character_avatar(std::string speaking_character_identifier="[unset-speaking_character_identifier]", std::string speaking_character_expression="[unset-speaking_character_expression]");
         void append_to_dialog_roll(std::string speaking_character="[unset-speaking_character]", std::string dialog="[unset-dialog]");
      };
   }
}



