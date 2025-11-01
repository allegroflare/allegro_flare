#pragma once


#include <AllegroFlare/GameWorldTimer.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/PlayerInputControllers/Base.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/Gameplay.hpp>
#include <AllegroFlare/SuspendedJoystickState.hpp>
#include <AllegroFlare/SuspendedKeyboardState.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
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

      public:

         enum class TimerStrategy
         {
            TIMER_STRATEGY_UNDEF = 0,
            TIMER_STRATEGY_CLASSIC,
            TIMER_STRATEGY_ATOMIC_TIME_STEP,
         };
      private:
         AllegroFlare::GameWorldTimer game_world_step_timer;
         std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_paused_callback_func;
         void* on_paused_callback_func_user_data;
         std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_finished_callback_func;
         void* on_finished_callback_func_user_data;
         std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_manual_save_callback_func;
         void* on_manual_save_callback_func_user_data;
         std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_autosave_save_callback_func;
         void* on_autosave_save_callback_func_user_data;
         std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_quicksave_save_callback_func;
         void* on_quicksave_save_callback_func_user_data;
         AllegroFlare::PlayerInputControllers::Base* player_input_controller;
         bool gameplay_suspended;
         AllegroFlare::SuspendedKeyboardState suspended_keyboard_state;
         AllegroFlare::SuspendedJoystickState suspended_joystick_state;
         bool disable_escape_key_pauses_game;
         AllegroFlare::Screens::Gameplay::TimerStrategy timer_strategy;

      protected:


      public:
         Gameplay();
         virtual ~Gameplay();

         void set_on_paused_callback_func(std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_paused_callback_func);
         void set_on_paused_callback_func_user_data(void* on_paused_callback_func_user_data);
         void set_on_finished_callback_func(std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_finished_callback_func);
         void set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data);
         void set_on_manual_save_callback_func(std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_manual_save_callback_func);
         void set_on_manual_save_callback_func_user_data(void* on_manual_save_callback_func_user_data);
         void set_on_autosave_save_callback_func(std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_autosave_save_callback_func);
         void set_on_autosave_save_callback_func_user_data(void* on_autosave_save_callback_func_user_data);
         void set_on_quicksave_save_callback_func(std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_quicksave_save_callback_func);
         void set_on_quicksave_save_callback_func_user_data(void* on_quicksave_save_callback_func_user_data);
         void set_disable_escape_key_pauses_game(bool disable_escape_key_pauses_game);
         void set_timer_strategy(AllegroFlare::Screens::Gameplay::TimerStrategy timer_strategy);
         std::function<void(AllegroFlare::Screens::Gameplay*, void*)> get_on_paused_callback_func() const;
         void* get_on_paused_callback_func_user_data() const;
         std::function<void(AllegroFlare::Screens::Gameplay*, void*)> get_on_finished_callback_func() const;
         void* get_on_finished_callback_func_user_data() const;
         std::function<void(AllegroFlare::Screens::Gameplay*, void*)> get_on_manual_save_callback_func() const;
         void* get_on_manual_save_callback_func_user_data() const;
         std::function<void(AllegroFlare::Screens::Gameplay*, void*)> get_on_autosave_save_callback_func() const;
         void* get_on_autosave_save_callback_func_user_data() const;
         std::function<void(AllegroFlare::Screens::Gameplay*, void*)> get_on_quicksave_save_callback_func() const;
         void* get_on_quicksave_save_callback_func_user_data() const;
         AllegroFlare::PlayerInputControllers::Base* get_player_input_controller() const;
         bool get_gameplay_suspended() const;
         AllegroFlare::SuspendedKeyboardState get_suspended_keyboard_state() const;
         AllegroFlare::SuspendedJoystickState get_suspended_joystick_state() const;
         bool get_disable_escape_key_pauses_game() const;
         AllegroFlare::Screens::Gameplay::TimerStrategy get_timer_strategy() const;
         AllegroFlare::GameWorldTimer &get_game_world_step_timer_ref();
         AllegroFlare::SuspendedKeyboardState &get_suspended_keyboard_state_ref();
         AllegroFlare::SuspendedJoystickState &get_suspended_joystick_state_ref();
         void set_player_input_controller(AllegroFlare::PlayerInputControllers::Base* player_input_controller=nullptr);
         void deactivate_current_and_clear_player_input_controller();
         virtual void dialog_system_switch_in_func() override;
         virtual void dialog_system_switch_out_func() override;
         void suspend_gameplay();
         void resume_suspended_gameplay();
         void send_input_changes_since_last_suspend_to_player_input_controller();
         void save_to_manual_save();
         void save_to_autosave_save();
         void save_to_quicksave_save();
         void toggle_suspend_gameplay__DEPRECATED();
         virtual void gameplay_suspend_func();
         virtual void gameplay_resume_func();
         virtual void primary_timer_func() override;
         virtual void primary_time_step_func(double step=0.0, double total=0.0) override;
         virtual void primary_update_func(double time_now=al_get_time(), double delta_time=1.0 / 60.0) override;
         virtual void primary_render_func() override;
         void call_on_paused_callback_func();
         void call_on_finished_callback_func();
         virtual bool load_level_by_identifier(std::string possible_type="");
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_button_up_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void key_down_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void key_up_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void key_char_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void joy_button_down_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void joy_button_up_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void joy_axis_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void mouse_up_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void mouse_down_func(ALLEGRO_EVENT* ev=nullptr) override;
         virtual void mouse_axes_func(ALLEGRO_EVENT* ev=nullptr) override;
         bool timer_strategy_is_classic();
         bool timer_strategy_is_atomic_time_step();
         void set_timer_strategy_to_atomic_time_step();
      };
   }
}



