#pragma once


#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/Gameplay.hpp>
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

      protected:


      public:
         Gameplay();
         virtual ~Gameplay();

         void set_on_finished_callback_func(std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_finished_callback_func);
         void set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data);
         std::function<void(AllegroFlare::Screens::Gameplay*, void*)> get_on_finished_callback_func() const;
         void* get_on_finished_callback_func_user_data() const;
         bool get_gameplay_suspended() const;
         virtual void gameplay_suspend_func();
         virtual void gameplay_resume_func();
         void suspend_gameplay();
         void resume_suspended_gameplay();
         void toggle_suspend_gameplay();
         void call_on_finished_callback_func();
         virtual void load_level_by_identifier(std::string possible_type="");
      };
   }
}



