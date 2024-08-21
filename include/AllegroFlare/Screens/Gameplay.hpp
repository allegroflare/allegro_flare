#pragma once


#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/Gameplay.hpp>
#include <AllegroFlare/SuspendedKeyboardState.hpp>
#include <functional>
#include <string>


namespace AllegroFlare
{
   namespace Screens
   {
      class Gameplay : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Screens/Gameplay";

      private:
         std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_finished_callback_func;
         void* on_finished_callback_func_user_data;
         bool gameplay_suspended;
         AllegroFlare::SuspendedKeyboardState suspended_keyboard_state;

      protected:


      public:
         Gameplay();
         virtual ~Gameplay();

         void set_on_finished_callback_func(std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_finished_callback_func);
         void set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data);
         std::function<void(AllegroFlare::Screens::Gameplay*, void*)> get_on_finished_callback_func() const;
         void* get_on_finished_callback_func_user_data() const;
         bool get_gameplay_suspended() const;
         AllegroFlare::SuspendedKeyboardState get_suspended_keyboard_state() const;
         AllegroFlare::SuspendedKeyboardState &get_suspended_keyboard_state_ref();
         virtual void dialog_system_switch_in_func() override;
         virtual void dialog_system_switch_out_func() override;
         void suspend_gameplay();
         void resume_suspended_gameplay();
         void toggle_suspend_gameplay();
         virtual void gameplay_suspend_func();
         virtual void gameplay_resume_func();
         void call_on_finished_callback_func();
         virtual bool load_level_by_identifier(std::string possible_type="");
      };
   }
}



