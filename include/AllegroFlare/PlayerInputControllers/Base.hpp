#pragma once


#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace PlayerInputControllers
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/PlayerInputControllers/Base";

      private:
         std::string type;

      protected:


      public:
         Base(std::string type=AllegroFlare::PlayerInputControllers::Base::TYPE);
         virtual ~Base();

         std::string get_type() const;
         virtual void update_time_step(double time_now=(al_is_system_installed() ? al_get_time() : throw std::runtime_error("asjdfio")), double delta_time=1.0 / 60.0);
         virtual void on_activate();
         virtual void on_deactivate();
         virtual void gameplay_suspend_func();
         virtual void gameplay_resume_func();
         virtual void virtual_control_button_up_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false);
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false);
         virtual void key_down_func(ALLEGRO_EVENT* ev=nullptr);
         virtual void key_up_func(ALLEGRO_EVENT* ev=nullptr);
         virtual void key_char_func(ALLEGRO_EVENT* ev=nullptr);
         virtual void joy_axis_func(ALLEGRO_EVENT* ev=nullptr);
         virtual void mouse_down_func(ALLEGRO_EVENT* ev=nullptr);
         virtual void mouse_axes_func(ALLEGRO_EVENT* ev=nullptr);
         bool is_type(std::string possible_type="");
      };
   }
}



