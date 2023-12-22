

#include <AllegroFlare/VirtualControlsProcessor.hpp>

#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/GameEventDatas/VirtualControllerAxisChangeEventData.hpp>
#include <AllegroFlare/GameEventDatas/VirtualControllerButtonPressedEventData.hpp>
#include <AllegroFlare/GameEventDatas/VirtualControllerButtonReleasedEventData.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/PhysicalInputDeviceToVirtualControllerMappingFactory.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


VirtualControlsProcessor::VirtualControlsProcessor(AllegroFlare::InputDevicesList* input_devices_list, AllegroFlare::EventEmitter* event_emitter)
   : input_devices_list(input_devices_list)
   , event_emitter(event_emitter)
   , physical_input_device_to_virtual_control_mappings({})
   , initialized(false)
{
}


VirtualControlsProcessor::~VirtualControlsProcessor()
{
}


bool VirtualControlsProcessor::get_initialized() const
{
   return initialized;
}


std::vector<AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping> &VirtualControlsProcessor::get_physical_input_device_to_virtual_control_mappings_ref()
{
   return physical_input_device_to_virtual_control_mappings;
}


void VirtualControlsProcessor::set_input_devices_list(AllegroFlare::InputDevicesList* input_devices_list)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::set_input_devices_list]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::set_input_devices_list: error: guard \"(!initialized)\" not met");
   }
   this->input_devices_list = input_devices_list;
   return;
}

void VirtualControlsProcessor::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::set_event_emitter: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
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
   if (!(input_devices_list))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::initialize]: error: guard \"input_devices_list\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::initialize: error: guard \"input_devices_list\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[VirtualControlsProcessor::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VirtualControlsProcessor::initialize: error: guard \"event_emitter\" not met");
   }
   AllegroFlare::PhysicalInputDeviceToVirtualControllerMappingFactory factory; // TODO: remove factory as dependency
   AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping mapping =
   factory.create_single_player_keyboard_mapping_from_scratch();

   physical_input_device_to_virtual_control_mappings = { mapping };

   // TODO: Create basic mapping for joysticks
   initialized = true;
   return;
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
   AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping *mapping =
      get_keyboard_mapped_physical_input_device_to_virtual_controller_mapping(event->keyboard.keycode);

   if (!mapping) return;

   emit_virtual_controls_button_down_event(
      mapping->get_player(),
      mapping->get_virtual_controller(),
      mapping->get_mapping(event->keyboard.keycode),
      event->keyboard.repeat // NOTE: this will not fire unless the event is a "ALLEGRO_EVENT_KEY_CHAR" event
   );
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
   AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping *mapping =
      get_keyboard_mapped_physical_input_device_to_virtual_controller_mapping(event->keyboard.keycode);

   if (!mapping) return;

   emit_virtual_controls_button_up_event(
      mapping->get_player(),
      mapping->get_virtual_controller(),
      mapping->get_mapping(event->keyboard.keycode),
      event->keyboard.repeat // NOTE: this will not fire unless the event is a "ALLEGRO_EVENT_KEY_CHAR" event
   );
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
   // TODO: Implement this function
   AllegroFlare::Logger::warn_from_once(
      "VirtualControlsProcessor::handle_raw_joystick_button_down_event",
      "not implemented"
   );
   // TODO: Remove this throw
   //throw std::runtime_error("VirtualControlsProcessor::handle_raw_joystick_button_down_event: not implemented");
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
   // TODO: Implement this function
   AllegroFlare::Logger::warn_from_once(
      "VirtualControlsProcessor::handle_raw_joystick_button_up_event",
      "not implemented"
   );
   // TODO: Remove this throw
   //throw std::runtime_error("VirtualControlsProcessor::handle_raw_joystick_button_up_event: not implemented");
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
   // TODO: Implement this function
   AllegroFlare::Logger::warn_from_once(
      "VirtualControlsProcessor::handle_raw_joystick_axis_change_event",
      "not implemented"
   );
   // TODO: Remove this throw
   //throw std::runtime_error("VirtualControlsProcessor::handle_raw_joystick_button_up_event: not implemented");
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
   // TODO: Implement this function
   AllegroFlare::Logger::warn_from_once(
      "VirtualControlsProcessor::handle_joystick_device_configuration_event",
      "not implemented"
   );
   // TODO: Remove this throw
   //throw std::runtime_error("VirtualControlsProcessor::handle_joystick_device_configuration_change_event: not implemented");
   return;
}

int VirtualControlsProcessor::get_joystick_mapped_virtual_button(int native_button_num)
{
   // TODO: Implement this function
   AllegroFlare::Logger::warn_from_once(
      "VirtualControlsProcessor::get_joystick_mapped_virtual_button",
      "not implemented"
   );
   // TODO: Remove this throw
   //throw std::runtime_error("VirtualControlsProcessor::get_joystick_mapped_virtual_button: not implemented");
   return 0;
}

AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping* VirtualControlsProcessor::get_keyboard_mapped_physical_input_device_to_virtual_controller_mapping(int al_keyboard_keycode)
{
   AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping *mapping = nullptr;

   for (auto &physical_input_device_to_virtual_control_mapping : physical_input_device_to_virtual_control_mappings)
   {
      // This mapping should only be looked up if it is a keyboard, continue on if this mapping is not to the
      // physical keyboard
      if (!physical_input_device_to_virtual_control_mapping.physical_input_device_is_keyboard()) continue;

      // If there is no mapping for this keyboard key, continue to the next one.
      if (!physical_input_device_to_virtual_control_mapping
            .mapping_exists_on_physical_device_button(al_keyboard_keycode)
      ) continue;

      // We found a mapping for that keyboard
      mapping = &physical_input_device_to_virtual_control_mapping;
      break;
   }

   return mapping;
}

void VirtualControlsProcessor::emit_virtual_controls_button_up_event(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
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
   AllegroFlare::GameEventDatas::VirtualControllerButtonReleasedEventData *event_data = new
      AllegroFlare::GameEventDatas::VirtualControllerButtonReleasedEventData();

   event_data->set_player(player);
   event_data->set_virtual_controller(virtual_controller);
   event_data->set_virtual_controller_button_num(virtual_controller_button_num);
   // TODO: Consider adding "is_repeat"

   event_emitter->emit_event(
      ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP,
      (intptr_t)event_data
   );
   return;
}

void VirtualControlsProcessor::emit_virtual_controls_button_down_event(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
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
   AllegroFlare::GameEventDatas::VirtualControllerButtonPressedEventData *event_data = new
      AllegroFlare::GameEventDatas::VirtualControllerButtonPressedEventData();

   event_data->set_player(player);
   event_data->set_virtual_controller(virtual_controller);
   event_data->set_virtual_controller_button_num(virtual_controller_button_num);
   // TODO: Consider adding "is_repeat"

   event_emitter->emit_event(
      ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN,
      (intptr_t)event_data
   );
   return;
}

void VirtualControlsProcessor::emit_virtual_controls_axis_change_event(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_stick, int virtual_controller_axis, float virtual_controller_position)
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
   AllegroFlare::GameEventDatas::VirtualControllerAxisChangeEventData *event_data = new
      AllegroFlare::GameEventDatas::VirtualControllerAxisChangeEventData();

   event_data->set_player(player);
   event_data->set_virtual_controller(virtual_controller);
   event_data->set_virtual_controller_stick(virtual_controller_stick);
   event_data->set_virtual_controller_axis(virtual_controller_axis);
   event_data->set_virtual_controller_position(virtual_controller_position);

   event_emitter->emit_event(
      ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_AXIS_CHANGE,
      (intptr_t)event_data
      //player_num,
      //stick,
      //axis,
      //(int)(position * 255)
   );
   return;
}


} // namespace AllegroFlare


