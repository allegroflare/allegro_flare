#pragma once


#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
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
         virtual void on_deactivate();
         virtual void on_render();
         virtual bool activate_dialog_node_by_name(AllegroFlare::DialogSystem::DialogSystem* dialog_system=nullptr, std::string active_dialog_node_name="[unset-dialog_node_identifier]", AllegroFlare::DialogTree::Nodes::Base* active_dialog_node=nullptr, void* user_data=nullptr);
         bool is_type(std::string possible_type="");
      };
   }
}



