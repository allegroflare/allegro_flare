#pragma once


#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/ForwardDeclarations/AllegroFlare/DialogSystem/DialogSystem.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystemDrivers
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystemDrivers/Base";

      private:
         std::string type;

      protected:


      public:
         Base(std::string type=AllegroFlare::DialogSystemDrivers::Base::TYPE);
         virtual ~Base();

         std::string get_type() const;
         virtual void on_switch_in();
         virtual void on_switch_out();
         virtual bool on_load_node_bank_from_file(std::string filename="[unset-filename]", AllegroFlare::DialogTree::NodeBank* node_bank_to_load_into=nullptr);
         virtual void update();
         virtual void on_render();
         virtual void on_before_spawn_basic_dialog(std::string speaking_character_identifier="[unset-speaking_character_identifier]");
         virtual void on_before_spawn_choice_dialog(std::string speaking_character_identifier="[unset-speaking_character_identifier]");
         virtual void enter_character(std::string character_identifier="[unset-character_identifier]");
         virtual void exit_character(std::string character_identifier="[unset-character_identifier]");
         virtual void on_raw_script_line_activate(AllegroFlare::DialogSystem::DialogSystem* dialog_system=nullptr, std::string activating_node_name="[unset-activating_node_name]", AllegroFlare::DialogTree::Nodes::Base* activating_node=nullptr, void* user_data=nullptr);
         virtual void on_raw_script_line_finished(AllegroFlare::DialogSystem::DialogSystem* dialog_system=nullptr, AllegroFlare::Elements::DialogBoxes::Base* active_dialog_box=nullptr, AllegroFlare::DialogTree::Nodes::Base* active_dialog_node=nullptr);
         virtual bool on_activate_dialog_node_type_unhandled(AllegroFlare::DialogSystem::DialogSystem* dialog_system=nullptr, AllegroFlare::DialogTree::Nodes::Base* active_dialog_node=nullptr);
         virtual std::string decorate_speaking_character_name(std::string speaking_character_identifier="[unset-speaking_character_identifier]");
         bool is_type(std::string possible_type="");
      };
   }
}



