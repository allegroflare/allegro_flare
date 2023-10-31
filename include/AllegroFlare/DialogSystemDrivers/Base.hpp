#pragma once


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
         bool is_type(std::string possible_type="");
      };
   }
}



