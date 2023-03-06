

#include <AllegroFlare/VirtualControlsProcessor.hpp>

#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


VirtualControlsProcessor::VirtualControlsProcessor(AllegroFlare::EventEmitter* event_emitter)
   : event_emitter(event_emitter)
   , physical_input_devices({})
   , physical_input_device_to_virtual_control_mappings({})
   , initialized(false)
{
}


VirtualControlsProcessor::~VirtualControlsProcessor()
{
}


void VirtualControlsProcessor::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


bool VirtualControlsProcessor::get_initialized() const
{
   return initialized;
}


std::vector<AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping> &VirtualControlsProcessor::get_physical_input_device_to_virtual_control_mappings_ref()
{
   return physical_input_device_to_virtual_control_mappings;
}


void VirtualControlsProcessor::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_joystick_installed()))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::initialize]: error: guard \"al_is_joystick_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::initialize: error: guard \"al_is_joystick_installed()\" not met");
   }
   setup_configuration_of_connected_joystick_devices();
   initialized = true;
   return;
}

void VirtualControlsProcessor::setup_configuration_of_connected_joystick_devices()
{
   al_reconfigure_joysticks();
   //joystick_devices.clear();
   for (int i=0; i<al_get_num_joysticks(); i++)
   {
      // 
      //joystick_devices[al_get_joystick(i)] = i;
   }
   return;
}

int VirtualControlsProcessor::infer_num_physical_input_devices()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::infer_num_physical_input_devices]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::infer_num_physical_input_devices: error: guard \"initialized\" not met");
   }
   return physical_input_devices.size();
}

int VirtualControlsProcessor::infer_num_physical_input_devices_connected()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::infer_num_physical_input_devices_connected]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::infer_num_physical_input_devices_connected: error: guard \"initialized\" not met");
   }
   // TODO: implement this function
   return 0;
}

int VirtualControlsProcessor::find_player_num_from_al_joystick(ALLEGRO_JOYSTICK* al_joystick)
{
   throw std::runtime_error("VirtualControlsProcessor::find_player_num_from_al_joystick");
   // TODO: implement this function
   for (auto &physical_input_device : physical_input_devices)
   {
      // TODO: This logic
      //if (physical_input_device->is_joystick()) {}
   }
   return 0;
}

void VirtualControlsProcessor::handle_raw_keyboard_key_down_event(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_raw_keyboard_key_down_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_raw_keyboard_key_down_event: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_raw_keyboard_key_down_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_raw_keyboard_key_down_event: error: guard \"event_emitter\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_raw_keyboard_key_down_event]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_raw_keyboard_key_down_event: error: guard \"event\" not met");
   }
   std::pair<int, int> player_num_and_virtual_button =
      get_keyboard_mapped_player_num_and_virtual_button(event->keyboard.keycode);
   if (player_num_and_virtual_button == std::pair<int, int>{-1, -1}) return;
      // ^^ TODO: this behavior should be a little better; Maybe "has_mapping" first

   int player_num = player_num_and_virtual_button.first;
   int virtual_button = player_num_and_virtual_button.second;

   emit_virtual_controls_button_down_event(player_num, virtual_button);
   return;
}

void VirtualControlsProcessor::handle_raw_keyboard_key_up_event(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_raw_keyboard_key_up_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_raw_keyboard_key_up_event: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_raw_keyboard_key_up_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_raw_keyboard_key_up_event: error: guard \"event_emitter\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_raw_keyboard_key_up_event]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_raw_keyboard_key_up_event: error: guard \"event\" not met");
   }
   std::pair<int, int> player_num_and_virtual_button =
      get_keyboard_mapped_player_num_and_virtual_button(event->keyboard.keycode);
   if (player_num_and_virtual_button == std::pair<int, int>{-1, -1}) return;
      // ^^ TODO: this behavior should be a little better; Maybe "has_mapping" first

   int player_num = player_num_and_virtual_button.first;
   int virtual_button = player_num_and_virtual_button.second;

   emit_virtual_controls_button_up_event(player_num, virtual_button);
   return;
}

void VirtualControlsProcessor::handle_raw_joystick_button_down_event(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_raw_joystick_button_down_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_raw_joystick_button_down_event: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_raw_joystick_button_down_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_raw_joystick_button_down_event: error: guard \"event_emitter\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_raw_joystick_button_down_event]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_raw_joystick_button_down_event: error: guard \"event\" not met");
   }
   int player_num = find_player_num_from_al_joystick(event->joystick.id);
   int virtual_button = get_joystick_mapped_virtual_button(event->joystick.button);
   if (virtual_button == -1) return; // TODO: this behavior should be a little better; Maybe "has_mapping" first

   emit_virtual_controls_button_down_event(player_num, virtual_button);
   return;
}

void VirtualControlsProcessor::handle_raw_joystick_button_up_event(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_raw_joystick_button_up_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_raw_joystick_button_up_event: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_raw_joystick_button_up_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_raw_joystick_button_up_event: error: guard \"event_emitter\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_raw_joystick_button_up_event]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_raw_joystick_button_up_event: error: guard \"event\" not met");
   }
   int player_num = find_player_num_from_al_joystick(event->joystick.id);
   int virtual_button = get_joystick_mapped_virtual_button(event->joystick.button);
   if (virtual_button == -1) return; // TODO: this behavior should be a little better; Maybe "has_mapping" first

   emit_virtual_controls_button_up_event(player_num, virtual_button);
   return;
}

void VirtualControlsProcessor::handle_raw_joystick_axis_change_event(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_raw_joystick_axis_change_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_raw_joystick_axis_change_event: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_raw_joystick_axis_change_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_raw_joystick_axis_change_event: error: guard \"event_emitter\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_raw_joystick_axis_change_event]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_raw_joystick_axis_change_event: error: guard \"event\" not met");
   }
   int player_num = find_player_num_from_al_joystick(event->joystick.id);
   emit_virtual_controls_axis_change_event(
      player_num,
      event->joystick.stick,
      event->joystick.axis,
      event->joystick.pos
   );
   return;
}

void VirtualControlsProcessor::handle_joystick_device_configuration_change_event(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_joystick_device_configuration_change_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_joystick_device_configuration_change_event: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_joystick_device_configuration_change_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_joystick_device_configuration_change_event: error: guard \"event_emitter\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::handle_joystick_device_configuration_change_event]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::handle_joystick_device_configuration_change_event: error: guard \"event\" not met");
   }
   AllegroFlare::Logger::info_from(
      "AllegroFlare::VirtualControlsProcessor::handle_joystick_device_configuration_change_event",
      "Joystick configuration changed on the system. A device has been connected or disconnected."
   );

   setup_configuration_of_connected_joystick_devices();

   return;
}

int VirtualControlsProcessor::get_joystick_mapped_virtual_button(int native_button_num)
{
   throw std::runtime_error("VirtualControlsProcessor::get_joystick_mapped_virtual_button: not implemented");
   //bool map_value_exists = joystick_button_map.find(native_button_num) != joystick_button_map.end();
   //if (!map_value_exists) return -1;
   //int virtual_button = joystick_button_map[native_button_num];
   //return virtual_button;
   return 0;
}

std::pair<int, int> VirtualControlsProcessor::get_keyboard_mapped_player_num_and_virtual_button(int al_keyboard_keycode)
{
   // TODO: Do a better job of grabbing and passing back AllegroFlare::Player from mapping

   bool player_num_found = false; // TODO: likey this "player_num_found" will be removed.
   bool player_found = false;
   bool virtual_button_found = false;

   AllegroFlare::Player *player = nullptr;
   int player_num = 0; // TODO: Resolve player num (Actually, need to update the signature of these functions
                       // so they take an AllegroFlare::Player* and not a "player num")
   int virtual_button_num = -1; // TODO: have virtual button num *also* pass along the device

   for (auto &physical_input_device_to_virtual_control_mapping : physical_input_device_to_virtual_control_mappings)
   {
      // This mapping should only be looked up if it is a keyboard, continue on if this mapping is not to the
      // physical keyboard
      if (!physical_input_device_to_virtual_control_mapping.physical_input_device_is_keyboard()) continue;

      // If there is no mapping for this keyboard key, continue to the next one.
      if (!physical_input_device_to_virtual_control_mapping
            .mapping_exists_on_physical_device_button(al_keyboard_keycode)
      ) continue;

      virtual_button_num = physical_input_device_to_virtual_control_mapping.get_mapping(al_keyboard_keycode);
      AllegroFlare::Player *player = physical_input_device_to_virtual_control_mapping.get_player();

      player_num_found = true; // TODO: Do a better job of grabbing AllegroFlare::Player from mapping
      player_found = true; // TODO: Do a better job of grabbing AllegroFlare::Player from mapping
      virtual_button_found = true;
   }

   if (player_num_found && player_found && virtual_button_found) return { player_num, virtual_button_num };

   return { -1, -1 };
}

void VirtualControlsProcessor::emit_virtual_controls_button_up_event(int player_num, int virtual_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::emit_virtual_controls_button_up_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::emit_virtual_controls_button_up_event: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::emit_virtual_controls_button_up_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::emit_virtual_controls_button_up_event: error: guard \"event_emitter\" not met");
   }
   // TODO: consider using non-global event names for these types, or a better design for this scope
   event_emitter->emit_event(
      ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP,
      player_num,
      virtual_button_num,
      is_repeat
   );
   return;
}

void VirtualControlsProcessor::emit_virtual_controls_button_down_event(int player_num, int virtual_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::emit_virtual_controls_button_down_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::emit_virtual_controls_button_down_event: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::emit_virtual_controls_button_down_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::emit_virtual_controls_button_down_event: error: guard \"event_emitter\" not met");
   }
   // TODO: consider using non-global event names for these types, or a better design for this scope
   event_emitter->emit_event(
      ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN,
      player_num,
      virtual_button_num,
      is_repeat
   );
   return;
}

void VirtualControlsProcessor::emit_virtual_controls_axis_change_event(int player_num, int stick, int axis, float position)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::emit_virtual_controls_axis_change_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::emit_virtual_controls_axis_change_event: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::emit_virtual_controls_axis_change_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::emit_virtual_controls_axis_change_event: error: guard \"event_emitter\" not met");
   }
   // TODO: consider using non-global event names for these types, or a better design for this scope
   event_emitter->emit_event(
      ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_AXIS_CHANGE,
      player_num,
      stick,
      axis,
      (int)(position * 255)
   );
   return;
}


} // namespace AllegroFlare


