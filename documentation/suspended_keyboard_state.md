# Using SuspendedKeyboardState and SuspendedJoystickState


TLDR: In your `Gameplay/Screen`'s `gameplay_resume_func`, you can obtain the
delta in pressed/unpressed keyboard keys between the suspend/unsuspend, like so:

```
void Screen::gameplay_resume_func() // virtual, override
{
   // NOTE: This function is called immediately after the gameplay is resumed.
   // TODO: Consider reviewing states on entities, reviewing their state timers, etc.

   // Keyboard changes that occurred during the gameplay
   AllegroFlare::SuspendedKeyboardState &suspended_keyboard_state = get_suspended_keyboard_state_ref();
   std::vector<uint32_t> keys_pressed = suspended_keyboard_state.get_keys_pressed();
   std::vector<uint32_t> keys_released = suspended_keyboard_state.get_keys_released();
   float time_now = al_get_time(); // TODO: Inject time when the resume occurred

   auto entity_control_connector = get_entity_control_connector();
   if (entity_control_connector)
   {
      if (entity_control_connector->is_type(SomePlatformer::EntityControlConnectors::PlayerCharacter::TYPE))
      {
         // In this techniqe, we'll build a fake ALLEGRO_EVENT and pass it into the entity_control_connector.
         // There could potentially be unidentified side effects with this approach, some example:
         //   1) This event does not pass through the normal global event queue.
         //   2) The "source" and "display" fields are not used in this event, but may need to be present at
         //      some point
         //   3) The control connector may be expecting a full pass of the event through the system before
         //      processing a second "event".
         // Advantage of this approach is that the base class takes key_up_func and key_down_func, so this
         // technique could be used on all EntityControlConnectors::Base classes.

         // Process key releases (a.k.a. "key up")
         for (auto &key_released : keys_released)
         {
            ALLEGRO_EVENT event;
            event.type = ALLEGRO_EVENT_KEY_UP;
            event.any.source = nullptr; // TODO: Should I be using a SuspendedKeyboardState event source?
            event.any.timestamp = time_now;
            event.keyboard.keycode = key_released;
            event.keyboard.display = nullptr; // TODO: Consider if al_get_current_display() should be used here

            entity_control_connector->key_up_func(&event);
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

            entity_control_connector->key_down_func(&event);
         }
      }
   }
   return;
}
```


## Reasoning

> Need to figure out a technique for when a player pauses while holding a keypress, and then unpauses after having changed keys. 
> It happens during dialogs too when gameplay is suspended, and/or window focus changes.

> ChatGPT: This issue is common in game development, where input state might not be correctly captured when transitioning between different game states, such as gameplay and dialog.


> I already had a virtual gameplay_suspend_func() and virtual gameplay_resume_func() in the gameplay screen, these are callbacks. In the base class I capture the keyboard on suspend, and then it's available for the derived class in the callback.

> As a last step in the callback that "seems to work fine", I create an ALLEGRO_KEY_UP_EVENT and ALLEGRO_KEY_DOWN_EVENT for each key change, and pass them into the key_down_func and key_up_fun that controls the character (called an EntityControlConnector).

> https://gist.github.com/MarkOates/116be3ccc085e6f806f1d4e93d554aae#file-gameplay_screen__gameplay_resume_func-cpp-L17-L51


## Keyboard


- AllegroFlare/SuspendedKeyboardState


```
AllegroFlare::SuspendedKeyboardState input_state;
input_state.capture_initial_keyboard_state();
// ...
input_state.capture_subsequent_keyboard_state();
input_state.calculate_keyboard_state_changes();
```

```
std::vector<uint32_t> keys_pressed = input_state.get_keys_pressed();
std::vector<uint32_t> keys_released = input_state.get_keys_released();
```




## Joystick


- AllegroFlare/SuspendedJoystickState


```
ALLEGRO_JOYSTICK *my_joystick = ...;
  
AllegroFlare::SuspendedJoystickState input_state;
input_state.set_joystick(my_joystick);
input_state.capture_initial_joystick_state();
// .. your joystick configuration changes, then ...
input_state.capture_subsequent_joystick_state();
input_state.calculate_joystick_state_changes();
```


The std::map<std::pair<int, int>, std::pair<float, float>> structure is stick_num axis_num, then axis_delta, and axis_position, so like:



```
std::map<std::pair<int, int>, std::pair<float, float>> sticks_moved = input_state.get_sticks_moved();

int stick_num, axis_num;
float axis_delta, axis_position;
for (auto &stick : sticks)
{
   std::tie(stick_num, axis_num) = stick.first;
   std::tie(axis_delta, axis_position) = stick.second;

   // Now do your stuff with the stick/axis/delta/position vars here
}
```
