#pragma once


#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/ForwardDeclarations/AllegroFlare/DialogSystem/DialogSystem.hpp>
#include <functional>
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
         std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, void*)> activate_dialog_node_type_unhandled_func;
         void* activate_dialog_node_type_unhandled_func_user_data;

      protected:


      public:
         Base(std::string type=AllegroFlare::DialogSystemDrivers::Base::TYPE);
         virtual ~Base();

         void set_activate_dialog_node_type_unhandled_func(std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, void*)> activate_dialog_node_type_unhandled_func);
         void set_activate_dialog_node_type_unhandled_func_user_data(void* activate_dialog_node_type_unhandled_func_user_data);
         std::string get_type() const;
         std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, void*)> get_activate_dialog_node_type_unhandled_func() const;
         void* get_activate_dialog_node_type_unhandled_func_user_data() const;
         virtual void on_switch_in();
         virtual void on_switch_out();
         virtual void on_render();
         virtual void on_before_spawn_basic_dialog(std::string speaking_character_identifier="[unset-speaking_character_identifier]");
         virtual void on_before_spawn_choice_dialog(std::string speaking_character_identifier="[unset-speaking_character_identifier]");
         virtual void on_raw_script_line_activate(AllegroFlare::DialogSystem::DialogSystem* dialog_system=nullptr, std::string activating_node_name="[unset-activating_node_name]", AllegroFlare::DialogTree::Nodes::Base* activating_node=nullptr, void* user_data=nullptr);
         virtual void on_raw_script_line_finished(AllegroFlare::DialogSystem::DialogSystem* dialog_system=nullptr, AllegroFlare::Elements::DialogBoxes::Base* active_dialog_box=nullptr, AllegroFlare::DialogTree::Nodes::Base* active_dialog_node=nullptr);
         virtual std::string decorate_speaking_character_name(std::string speaking_character_identifier="[unset-speaking_character_identifier]");
         bool is_type(std::string possible_type="");
      };
   }
}



