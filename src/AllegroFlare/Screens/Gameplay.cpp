

#include <AllegroFlare/Screens/Gameplay.hpp>

#include <AllegroFlare/Logger.hpp>


namespace AllegroFlare
{
namespace Screens
{


Gameplay::Gameplay()
   : AllegroFlare::Screens::Base(AllegroFlare::Screens::Gameplay::TYPE)
   , game_world_step_timer({})
   , on_paused_callback_func()
   , on_paused_callback_func_user_data(nullptr)
   , on_finished_callback_func()
   , on_finished_callback_func_user_data(nullptr)
   , on_manual_save_callback_func()
   , on_manual_save_callback_func_user_data(nullptr)
   , on_autosave_save_callback_func()
   , on_autosave_save_callback_func_user_data(nullptr)
   , on_quicksave_save_callback_func()
   , on_quicksave_save_callback_func_user_data(nullptr)
   , player_input_controller(nullptr)
   , gameplay_suspended(false)
   , suspended_keyboard_state({})
   , suspended_joystick_state({})
   , disable_escape_key_pauses_game(false)
   , timer_strategy(AllegroFlare::Screens::Gameplay::TimerStrategy::TIMER_STRATEGY_CLASSIC)
{
}


Gameplay::~Gameplay()
{
}


void Gameplay::set_on_paused_callback_func(std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_paused_callback_func)
{
   this->on_paused_callback_func = on_paused_callback_func;
}


void Gameplay::set_on_paused_callback_func_user_data(void* on_paused_callback_func_user_data)
{
   this->on_paused_callback_func_user_data = on_paused_callback_func_user_data;
}


void Gameplay::set_on_finished_callback_func(std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_finished_callback_func)
{
   this->on_finished_callback_func = on_finished_callback_func;
}


void Gameplay::set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data)
{
   this->on_finished_callback_func_user_data = on_finished_callback_func_user_data;
}


void Gameplay::set_on_manual_save_callback_func(std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_manual_save_callback_func)
{
   this->on_manual_save_callback_func = on_manual_save_callback_func;
}


void Gameplay::set_on_manual_save_callback_func_user_data(void* on_manual_save_callback_func_user_data)
{
   this->on_manual_save_callback_func_user_data = on_manual_save_callback_func_user_data;
}


void Gameplay::set_on_autosave_save_callback_func(std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_autosave_save_callback_func)
{
   this->on_autosave_save_callback_func = on_autosave_save_callback_func;
}


void Gameplay::set_on_autosave_save_callback_func_user_data(void* on_autosave_save_callback_func_user_data)
{
   this->on_autosave_save_callback_func_user_data = on_autosave_save_callback_func_user_data;
}


void Gameplay::set_on_quicksave_save_callback_func(std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_quicksave_save_callback_func)
{
   this->on_quicksave_save_callback_func = on_quicksave_save_callback_func;
}


void Gameplay::set_on_quicksave_save_callback_func_user_data(void* on_quicksave_save_callback_func_user_data)
{
   this->on_quicksave_save_callback_func_user_data = on_quicksave_save_callback_func_user_data;
}


void Gameplay::set_disable_escape_key_pauses_game(bool disable_escape_key_pauses_game)
{
   this->disable_escape_key_pauses_game = disable_escape_key_pauses_game;
}


void Gameplay::set_timer_strategy(AllegroFlare::Screens::Gameplay::TimerStrategy timer_strategy)
{
   this->timer_strategy = timer_strategy;
}


std::function<void(AllegroFlare::Screens::Gameplay*, void*)> Gameplay::get_on_paused_callback_func() const
{
   return on_paused_callback_func;
}


void* Gameplay::get_on_paused_callback_func_user_data() const
{
   return on_paused_callback_func_user_data;
}


std::function<void(AllegroFlare::Screens::Gameplay*, void*)> Gameplay::get_on_finished_callback_func() const
{
   return on_finished_callback_func;
}


void* Gameplay::get_on_finished_callback_func_user_data() const
{
   return on_finished_callback_func_user_data;
}


std::function<void(AllegroFlare::Screens::Gameplay*, void*)> Gameplay::get_on_manual_save_callback_func() const
{
   return on_manual_save_callback_func;
}


void* Gameplay::get_on_manual_save_callback_func_user_data() const
{
   return on_manual_save_callback_func_user_data;
}


std::function<void(AllegroFlare::Screens::Gameplay*, void*)> Gameplay::get_on_autosave_save_callback_func() const
{
   return on_autosave_save_callback_func;
}


void* Gameplay::get_on_autosave_save_callback_func_user_data() const
{
   return on_autosave_save_callback_func_user_data;
}


std::function<void(AllegroFlare::Screens::Gameplay*, void*)> Gameplay::get_on_quicksave_save_callback_func() const
{
   return on_quicksave_save_callback_func;
}


void* Gameplay::get_on_quicksave_save_callback_func_user_data() const
{
   return on_quicksave_save_callback_func_user_data;
}


AllegroFlare::PlayerInputControllers::Base* Gameplay::get_player_input_controller() const
{
   return player_input_controller;
}


bool Gameplay::get_gameplay_suspended() const
{
   return gameplay_suspended;
}


AllegroFlare::SuspendedKeyboardState Gameplay::get_suspended_keyboard_state() const
{
   return suspended_keyboard_state;
}


AllegroFlare::SuspendedJoystickState Gameplay::get_suspended_joystick_state() const
{
   return suspended_joystick_state;
}


bool Gameplay::get_disable_escape_key_pauses_game() const
{
   return disable_escape_key_pauses_game;
}


AllegroFlare::Screens::Gameplay::TimerStrategy Gameplay::get_timer_strategy() const
{
   return timer_strategy;
}


AllegroFlare::GameWorldTimer &Gameplay::get_game_world_step_timer_ref()
{
   return game_world_step_timer;
}


AllegroFlare::SuspendedKeyboardState &Gameplay::get_suspended_keyboard_state_ref()
{
   return suspended_keyboard_state;
}


AllegroFlare::SuspendedJoystickState &Gameplay::get_suspended_joystick_state_ref()
{
   return suspended_joystick_state;
}


void Gameplay::set_player_input_controller(AllegroFlare::PlayerInputControllers::Base* player_input_controller)
{
   if (player_input_controller)
   {
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Screens::Gameplay::set_player_input_controller",
         "deactivating current player_input_controller"
      );
      player_input_controller->on_deactivate();
   }
   this->player_input_controller = player_input_controller;
   AllegroFlare::Logger::info_from(
      "AllegroFlare::Screens::Gameplay::set_player_input_controller",
      "activating new player_input_controller"
   );
   this->player_input_controller->on_activate();
   return;
}

void Gameplay::dialog_system_switch_in_func()
{
   // Function that is called on ALLEGRO_FLARE_DIALOG_SWITCHED_IN
   // TODO: Consider disabling automatic suspend and unsuspend with an option on this class
   suspend_gameplay();
   return;
}

void Gameplay::dialog_system_switch_out_func()
{
   // Function that is called on ALLEGRO_FLARE_DIALOG_SWITCHED_OUT
   // TODO: Consider disabling automatic suspend and unsuspend with an option on this class
   resume_suspended_gameplay();
   return;
}

void Gameplay::suspend_gameplay()
{
   if (gameplay_suspended) return; // TODO: Should this throw? (it caused an issue in a Routers/Standard test)

   game_world_step_timer.pause();

   ALLEGRO_JOYSTICK *joystick = (al_get_num_joysticks() == 0) ? nullptr : al_get_joystick(0); // HACK
   suspended_joystick_state.set_joystick(joystick); // HACK

   suspended_keyboard_state.capture_initial_keyboard_state(); // TODO: Add guard if state cannot be captured
   if (suspended_joystick_state.joystick_exists()) suspended_joystick_state.capture_initial_joystick_state();
   gameplay_suspended = true;
   gameplay_suspend_func();

   // Suspend the player input controls
   if (player_input_controller) player_input_controller->gameplay_suspend_func();

   return;
}

void Gameplay::resume_suspended_gameplay()
{
   if (!gameplay_suspended) return; // TODO: Should this throw? (it caused an issue in a Routers/Standard test)

   gameplay_suspended = false;
   suspended_keyboard_state.capture_subsequent_keyboard_state(); // TODO: Add guard if state cannot be captured
   suspended_keyboard_state.calculate_keyboard_state_changes(); // TODO: Add guard if state cannot be captured
   if (suspended_joystick_state.joystick_exists())
   {
      suspended_joystick_state.capture_subsequent_joystick_state();
      suspended_joystick_state.calculate_joystick_state_changes();
   }

   game_world_step_timer.start();

   gameplay_resume_func();
   send_input_changes_since_last_suspend_to_player_input_controller(); // TODO: Test this
   suspended_keyboard_state.reset();
   suspended_joystick_state.reset();

   // Resume the player input controls
   if (player_input_controller) player_input_controller->gameplay_resume_func();

   return;
}

void Gameplay::send_input_changes_since_last_suspend_to_player_input_controller()
{
   if (!player_input_controller) return;

   // In this techniqe, we'll build a fake ALLEGRO_EVENT and pass it into the player_input_controller.
   // There could potentially be unidentified side effects with this approach, some example:
   //   1) This event does not pass through the normal global event queue.
   //   2) The "source" and "display" fields are not used in this event, but may need to be present at
   //      some point
   //   3) The input controller may be expecting a full pass of the event through the system before
   //      processing a second "event".
   // Advantage of this approach is that the base class takes key_up_func and key_down_func, so this
   // technique could be used on all PlayerInputController::Base classes.
   float time_now = al_get_time(); // TODO: Inject time when the resume occurred

   // Build changed keyboard info
   std::vector<uint32_t> keys_pressed = suspended_keyboard_state.get_keys_pressed();
   std::vector<uint32_t> keys_released = suspended_keyboard_state.get_keys_released();

   // Build changed joystick info
   std::map<std::pair<int, int>, std::pair<float, float>> sticks_moved;
   std::vector<uint32_t> buttons_pressed;
   std::vector<uint32_t> buttons_released;
   if (suspended_joystick_state.get_joystick_state_changes_are_calculated())
   {
      sticks_moved = suspended_joystick_state.get_sticks_moved();
      buttons_pressed = suspended_joystick_state.get_buttons_pressed();
      buttons_released = suspended_joystick_state.get_buttons_released();
   }

   // Process key releases (a.k.a. "key up")
   for (auto &key_released : keys_released)
   {
      ALLEGRO_EVENT event;
      event.type = ALLEGRO_EVENT_KEY_UP;
      event.any.source = nullptr; // TODO: Should I be using a SuspendedKeyboardState event source?
      event.any.timestamp = time_now;
      event.keyboard.keycode = key_released;
      event.keyboard.display = nullptr; // TODO: Consider if al_get_current_display() should be used here

      player_input_controller->key_up_func(&event);
      //entity_control_connector->key_up_func(&event);
   }

   // Process key presses (a.k.a. "key down")
   for (auto &key_pressed : keys_pressed)
   {
      ALLEGRO_EVENT event;
      event.type = ALLEGRO_EVENT_KEY_DOWN;
      event.any.source = nullptr; // TODO: Should I be using a SuspendedKeyboardState event source?
      event.any.timestamp = time_now;
      event.keyboard.keycode = key_pressed;
      event.keyboard.display = nullptr; // TODO: Consider if al_get_current_display() should be used here

      player_input_controller->key_down_func(&event);
      //entity_control_connector->key_down_func(&event);
   }

   // Process joy presses (a.k.a. "joy button down")
   for (auto &button_pressed : buttons_pressed)
   {
      ALLEGRO_EVENT event;
      event.type = ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN;
      event.any.source = nullptr; // TODO: Should I be using a SuspendedJoystickState event source?
      event.any.timestamp = time_now;
      event.joystick.id = suspended_joystick_state.get_joystick();
      event.joystick.button = button_pressed;
      //event.keyboard.display = nullptr; // TODO: Consider if al_get_current_display() should be used here

      player_input_controller->joy_button_down_func(&event);
   }

   // Process joy presses (a.k.a. "joy button up")
   for (auto &button_pressed : buttons_pressed)
   {
      ALLEGRO_EVENT event;
      event.type = ALLEGRO_EVENT_JOYSTICK_BUTTON_UP;
      event.any.source = nullptr; // TODO: Should I be using a SuspendedJoystickState event source?
      event.any.timestamp = time_now;
      event.joystick.id = suspended_joystick_state.get_joystick();
      event.joystick.button = button_pressed;
      //event.keyboard.display = nullptr; // TODO: Consider if al_get_current_display() should be used here

      player_input_controller->joy_button_up_func(&event);
   }

   // Process joy axes changes (a.k.a. "joy axis")
   for (auto &stick_moved : sticks_moved)
   {
      ALLEGRO_EVENT event;
      event.type = ALLEGRO_EVENT_JOYSTICK_AXIS;
      event.any.source = nullptr; // TODO: Should I be using a SuspendedJoystickState event source?
      event.any.timestamp = time_now;
      event.joystick.id = suspended_joystick_state.get_joystick();

      //AllegroFlare::SuspendedJoystickState::sticks_moved ==> [std::make_pair(stick_num, axis_num)] =
         //{ stick_delta, subsequent_joystick_state.stick[stick_num].axis[axis_num] };

      event.joystick.stick = stick_moved.first.first; // TODO: Validate this is correct
      event.joystick.axis = stick_moved.first.second; // TODO: Validate this is correct
      event.joystick.pos = stick_moved.second.second; // TODO: Validate this is correct
      //event.keyboard.display = nullptr; // TODO: Consider if al_get_current_display() should be used here

      player_input_controller->joy_axis_func(&event);
   }

   // HERE
   /*
   - name: joy_axis_func
     virtual: true
     parameters:
       - name: ev
         type: ALLEGRO_EVENT*
         default_argument: nullptr
     body: |
       // Override this in the derived class
       return;


   - name: joy_button_down_func
     virtual: true
     parameters:
       - name: ev
         type: ALLEGRO_EVENT*
         default_argument: nullptr
     body: |
       // Override this in the derived class
       return;


   - name: joy_button_up_func
     virtual: true
     parameters:
       - name: ev
         type: ALLEGRO_EVENT*
         default_argument: nullptr
     body: |
       // Override this in the derived class
       return;
   */

   // TODO: Process additional inputs from joystick
   // TODO: Find a way to unify keyboard and joystick inputs as if single input so you could play with keyboard,
   // pause with some keys pressed (player in motion), switch to joystick, hold same inputs but as buttons, unpause,
   // and resume with same control state.
   return;
}

void Gameplay::save_to_manual_save()
{
   if (!on_manual_save_callback_func)
   {
      AllegroFlare::Logger::warn_from_once(THIS_CLASS_AND_METHOD_NAME,
         "Expecting this class to have \"on_manual_save_callback_func\" defined but it is not. Unable to delegate "
         "this method to the callback to handle it."
      );
      return;
   }
   on_manual_save_callback_func(this, on_manual_save_callback_func_user_data);
   return;
}

void Gameplay::save_to_autosave_save()
{
   if (!on_autosave_save_callback_func)
   {
      AllegroFlare::Logger::warn_from_once(THIS_CLASS_AND_METHOD_NAME,
         "Expecting this class to have \"on_autosave_save_callback_func\" defined but it is not. Unable to delegate "
         "this method to the callback to handle it."
      );
      return;
   }
   on_autosave_save_callback_func(this, on_autosave_save_callback_func_user_data);
   return;
}

void Gameplay::save_to_quicksave_save()
{
   if (!on_quicksave_save_callback_func)
   {
      AllegroFlare::Logger::warn_from_once(THIS_CLASS_AND_METHOD_NAME,
         "Expecting this class to have \"on_quicksave_save_callback_func\" defined but it is not. Unable to "
         "delegate this method to the callback to handle it."
      );
      return;
   }
   on_quicksave_save_callback_func(this, on_quicksave_save_callback_func_user_data);
   return;
}

void Gameplay::toggle_suspend_gameplay__DEPRECATED()
{
   gameplay_suspended = !gameplay_suspended;
   if (gameplay_suspended) gameplay_suspend_func();
   else gameplay_resume_func();
   return;
}

void Gameplay::gameplay_suspend_func()
{
   // Function that is called immediately after the gameplay is suspended.
   AllegroFlare::Logger::warn_from_once(
      "AllegroFlare::Screens::Gameplay::gameplay_suspend_func",
      "Not implemented in the base class. This method should be implemented in the derived class. Take into account "
         "the AllegroFlare/Screens/Gameplay class has a suspend_gameplay func"
   );
   return;
}

void Gameplay::gameplay_resume_func()
{
   // Function that is called immediately after the gameplay is resumed.
   AllegroFlare::Logger::warn_from_once(
      "AllegroFlare::Screens::Gameplay::gameplay_suspend_func",
      "Not implemented in the base class. This method should be implemented in the derived class. Take into account "
         "the AllegroFlare/Screens/Gameplay class has a resume_gameplay func"
   );
   return;
}

void Gameplay::primary_timer_func()
{
   // NOTE: This "primary_timer_func" method is the old classic way of doing it. Consider migrating to use
   // "primary_update_func" and "primary_render_func" with:
   // set_update_strategy(AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS);
   // TODO: Consider throwing here and forcing downstream migration to "primary_update_func"
   if (player_input_controller)
   {
      double time_now = al_get_time();
      double placeholder_fps = 1.0/60.0;
      player_input_controller->update_time_step(time_now, placeholder_fps);
   }

   return;
}

void Gameplay::primary_time_step_func(double step, double total)
{
   // This is the method the end user should override in their derived class.
   // This method is only used if the derived screen is using the TIMER_STRATEGY_ATOMIC_TIME_STEP timer_strategy,
   // which can be set with set_timer_strategy_to_atomic_time_step();
   return;
}

void Gameplay::primary_update_func(double time_now, double delta_time)
{
   // Here, the primary update func just ticks at whatever rate is determined by the framework's primary timer.
   // The game world timer then checks periodically if it should step the simulation in atomic units (if the
   // simulation is running and not paused).
   // The user can override this function if they want, but ideally should set the timer strategy to use
   // TIMER_STRATEGY_ATOMIC_TIME_STEP and 
   if (timer_strategy_is_classic())
   {
      if (player_input_controller) player_input_controller->update_time_step(time_now, delta_time);
   }
   else if (timer_strategy_is_atomic_time_step())
   {
      game_world_step_timer.set_atomic_on_step_func([this](double step, double total, void* user){
         if (player_input_controller)
         {
            player_input_controller->update_time_step(total, step);
            //throw std::runtime_error("SJIFODSJFIO");
         }
         this->primary_time_step_func(step, total);
      });
      game_world_step_timer.update();
   }
   return;
}

void Gameplay::primary_render_func()
{
   // Override in the derived class
   return;
}

void Gameplay::call_on_paused_callback_func()
{
   // TODO: Test this callback call
   // TODO: Check downstream projects that may use this technique, or may already be using it and should have
   // their implementation removed for this one
   if (on_paused_callback_func) on_paused_callback_func(this, on_paused_callback_func_user_data);
   return;
}

void Gameplay::call_on_finished_callback_func()
{
   // TODO: Test this callback call
   if (on_finished_callback_func) on_finished_callback_func(this, on_finished_callback_func_user_data);
   return;
}

bool Gameplay::load_level_by_identifier(std::string possible_type)
{
   AllegroFlare::Logger::warn_from(
      "AllegroFlare::Screens::Gameplay::load_level_by_identifier",
      "Nothing to do here, returning false (false indicates that no level was loaded as a result of this method "
         "call. Consider removing this method and have loading occur outside of this screen class."
   );
   return false; // NOTE: false indicates that no level was loaded as a result of this method call
}

void Gameplay::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (player_input_controller)
   {
      player_input_controller->virtual_control_button_down_func(
         player,
         virtual_controller,
         virtual_controller_button_num,
         is_repeat
      );
   }
   return;
}

void Gameplay::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (player_input_controller)
   {
      player_input_controller->virtual_control_button_up_func(
         player,
         virtual_controller,
         virtual_controller_button_num,
         is_repeat
      );
   }
   return;
}

void Gameplay::key_down_func(ALLEGRO_EVENT* ev)
{
   if (player_input_controller) player_input_controller->key_down_func(ev);

   switch (ev->keyboard.keycode)
   {
      case ALLEGRO_KEY_ESCAPE: {
         if (!disable_escape_key_pauses_game) call_on_paused_callback_func();
      } break;
   }
   return;
}

void Gameplay::key_up_func(ALLEGRO_EVENT* ev)
{
   if (player_input_controller) player_input_controller->key_up_func(ev);
   return;
}

void Gameplay::key_char_func(ALLEGRO_EVENT* ev)
{
   if (player_input_controller) player_input_controller->key_char_func(ev);
   return;
}

void Gameplay::joy_button_down_func(ALLEGRO_EVENT* ev)
{
   if (player_input_controller) player_input_controller->joy_button_down_func(ev);

   //if (ev->joystick.button)
   //{
      // TODO: Work in this button feature when it is available:
      //case ALLEGRO_GAMEPAD_BUTTON_START: {
         // TODO: Test this behavior
         //if (!disable_start_button_pauses_game) call_on_paused_callback_func();
      //} break;
   //}
   return;
}

void Gameplay::joy_button_up_func(ALLEGRO_EVENT* ev)
{
   if (player_input_controller) player_input_controller->joy_button_up_func(ev);
   return;
}

void Gameplay::joy_axis_func(ALLEGRO_EVENT* ev)
{
   if (player_input_controller) player_input_controller->joy_axis_func(ev);
   return;
}

void Gameplay::mouse_up_func(ALLEGRO_EVENT* ev)
{
   if (player_input_controller) player_input_controller->mouse_up_func(ev);
   return;
}

void Gameplay::mouse_down_func(ALLEGRO_EVENT* ev)
{
   if (player_input_controller) player_input_controller->mouse_down_func(ev);
   return;
}

void Gameplay::mouse_axes_func(ALLEGRO_EVENT* ev)
{
   if (player_input_controller) player_input_controller->mouse_axes_func(ev);
   return;
}

bool Gameplay::timer_strategy_is_classic()
{
   return timer_strategy == AllegroFlare::Screens::Gameplay::TimerStrategy::TIMER_STRATEGY_CLASSIC;
}

bool Gameplay::timer_strategy_is_atomic_time_step()
{
   return timer_strategy == AllegroFlare::Screens::Gameplay::TimerStrategy::TIMER_STRATEGY_ATOMIC_TIME_STEP;
}

void Gameplay::set_timer_strategy_to_atomic_time_step()
{
   timer_strategy = AllegroFlare::Screens::Gameplay::TimerStrategy::TIMER_STRATEGY_ATOMIC_TIME_STEP;
}


} // namespace Screens
} // namespace AllegroFlare


