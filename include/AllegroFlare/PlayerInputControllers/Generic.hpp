#pragma once


#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/PlayerInputControllers/Base.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
#include <functional>


namespace AllegroFlare
{
   namespace PlayerInputControllers
   {
      class Generic : public AllegroFlare::PlayerInputControllers::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/PlayerInputControllers/Generic";

      private:
         void* entity;
         std::function<void(AllegroFlare::Vec2D)> on_time_step_update;
         AllegroFlare::Vec2D player_control_move_velocity;
         AllegroFlare::Vec2D player_control_look_velocity;
         bool player_right_pressed;
         bool player_left_pressed;
         bool player_up_pressed;
         bool player_down_pressed;
         bool initialized;
         void player_stop_moving();
         void player_spin_change(float delta=0.0f);
         void player_tilt_change(float delta=0.0f);
         AllegroFlare::Vec2D infer_player_control_move_velocity_from_keypress();
         AllegroFlare::Vec3D calculate_strafe_xy(float spin=0.0f, float displacement=0.0f);
         AllegroFlare::Vec3D calculate_forward_back_xy(float spin=0.0f, float displacement=0.0f);

      protected:


      public:
         Generic(void* entity=nullptr);
         virtual ~Generic();

         void set_entity(void* entity);
         void set_on_time_step_update(std::function<void(AllegroFlare::Vec2D)> on_time_step_update);
         void* get_entity() const;
         std::function<void(AllegroFlare::Vec2D)> get_on_time_step_update() const;
         void initialize();
         virtual void update_player_controlled_entity_velocity_from_player_input() override;
         virtual void gameplay_suspend_func() override;
         virtual void gameplay_resume_func() override;
         virtual void virtual_control_button_up_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void key_down_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void key_up_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void joy_axis_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void mouse_down_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void mouse_axes_func(ALLEGRO_EVENT* ev=nullptr) override;
      };
   }
}



