

#include <AllegroFlare/Screens/CharacterNameInput.hpp>

#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


CharacterNameInput::CharacterNameInput(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin, AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard, std::string default_result_text_on_activate, std::string default_cursor_position_over_key_name_on_activate, AllegroFlare::Placement3D software_keyboard_placement)
   : AllegroFlare::Screens::Base("CharacterNameInput")
   , event_emitter(event_emitter)
   , font_bin(font_bin)
   , software_keyboard(software_keyboard)
   , on_submit_callback_func()
   , on_submit_callback_func_user_data(nullptr)
   , default_result_text_on_activate(default_result_text_on_activate)
   , default_cursor_position_over_key_name_on_activate(default_cursor_position_over_key_name_on_activate)
   , software_keyboard_placement(software_keyboard_placement)
   , mode(MODE_USING_VIRTUAL_CONTROLS)
   , initialized(false)
{
}


CharacterNameInput::~CharacterNameInput()
{
}


void CharacterNameInput::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void CharacterNameInput::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void CharacterNameInput::set_on_submit_callback_func(std::function<void(AllegroFlare::Screens::CharacterNameInput*, void*)> on_submit_callback_func)
{
   this->on_submit_callback_func = on_submit_callback_func;
}


void CharacterNameInput::set_on_submit_callback_func_user_data(void* on_submit_callback_func_user_data)
{
   this->on_submit_callback_func_user_data = on_submit_callback_func_user_data;
}


void CharacterNameInput::set_default_result_text_on_activate(std::string default_result_text_on_activate)
{
   this->default_result_text_on_activate = default_result_text_on_activate;
}


void CharacterNameInput::set_default_cursor_position_over_key_name_on_activate(std::string default_cursor_position_over_key_name_on_activate)
{
   this->default_cursor_position_over_key_name_on_activate = default_cursor_position_over_key_name_on_activate;
}


void CharacterNameInput::set_software_keyboard_placement(AllegroFlare::Placement3D software_keyboard_placement)
{
   this->software_keyboard_placement = software_keyboard_placement;
}


std::function<void(AllegroFlare::Screens::CharacterNameInput*, void*)> CharacterNameInput::get_on_submit_callback_func() const
{
   return on_submit_callback_func;
}


void* CharacterNameInput::get_on_submit_callback_func_user_data() const
{
   return on_submit_callback_func_user_data;
}


std::string CharacterNameInput::get_default_result_text_on_activate() const
{
   return default_result_text_on_activate;
}


std::string CharacterNameInput::get_default_cursor_position_over_key_name_on_activate() const
{
   return default_cursor_position_over_key_name_on_activate;
}


AllegroFlare::Placement3D CharacterNameInput::get_software_keyboard_placement() const
{
   return software_keyboard_placement;
}


AllegroFlare::SoftwareKeyboard::SoftwareKeyboard &CharacterNameInput::get_software_keyboard_ref()
{
   return software_keyboard;
}


AllegroFlare::Placement3D &CharacterNameInput::get_software_keyboard_placement_ref()
{
   return software_keyboard_placement;
}


void CharacterNameInput::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[CharacterNameInput::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterNameInput::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[CharacterNameInput::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterNameInput::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[CharacterNameInput::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterNameInput::initialize: error: guard \"font_bin\" not met");
   }
   software_keyboard.set_event_emitter(event_emitter);
   software_keyboard.set_font_bin(font_bin);
   software_keyboard.initialize();
   software_keyboard.set_keys(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::build_boilerplate_keyboard_keys());
   AllegroFlare::Vec2D keyboard_dimensions =
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::calculate_boilerplate_keyboard_dimensions();
   software_keyboard.set_keyboard_dimensions(keyboard_dimensions.x, keyboard_dimensions.y);
   software_keyboard.set_keyboard_position(1920/2, 1080/12*7 + 20);

   // Setup our screen to manage handling the submit on the software keyboard
   software_keyboard.set_on_submit_callback_func(on_software_keyboard_on_submit_callback_func);
   software_keyboard.set_on_submit_callback_func_user_data(this);

   initialized = true;
   return;
}

void CharacterNameInput::on_software_keyboard_on_submit_callback_func(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard* software_keyboard, void* user_data)
{
   if (!(software_keyboard))
   {
      std::stringstream error_message;
      error_message << "[CharacterNameInput::on_software_keyboard_on_submit_callback_func]: error: guard \"software_keyboard\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterNameInput::on_software_keyboard_on_submit_callback_func: error: guard \"software_keyboard\" not met");
   }
   if (!(user_data))
   {
      std::stringstream error_message;
      error_message << "[CharacterNameInput::on_software_keyboard_on_submit_callback_func]: error: guard \"user_data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterNameInput::on_software_keyboard_on_submit_callback_func: error: guard \"user_data\" not met");
   }
   // TODO: Test this callback
   AllegroFlare::Screens::CharacterNameInput *as =
      static_cast<AllegroFlare::Screens::CharacterNameInput*>(user_data);
   if (as->get_on_submit_callback_func())
   {
      as->on_submit_callback_func(as, as->get_on_submit_callback_func_user_data());
   }
   return;
}

void CharacterNameInput::set_result_string(std::string result_string)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CharacterNameInput::set_result_string]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterNameInput::set_result_string: error: guard \"initialized\" not met");
   }
   // TODO: Test this
   software_keyboard.set_result_string(result_string);
   return;
}

std::string CharacterNameInput::get_result_string()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CharacterNameInput::get_result_string]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterNameInput::get_result_string: error: guard \"initialized\" not met");
   }
   // TODO: Test this
   return software_keyboard.get_result_string();
}

void CharacterNameInput::silently_position_cursor_over_key_by_name(std::string key_name)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CharacterNameInput::silently_position_cursor_over_key_by_name]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterNameInput::silently_position_cursor_over_key_by_name: error: guard \"initialized\" not met");
   }
   if (!(software_keyboard.key_exists(key_name)))
   {
      std::stringstream error_message;
      error_message << "[CharacterNameInput::silently_position_cursor_over_key_by_name]: error: guard \"software_keyboard.key_exists(key_name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterNameInput::silently_position_cursor_over_key_by_name: error: guard \"software_keyboard.key_exists(key_name)\" not met");
   }
   // TODO: Test this
   // TODO: Create and use a different method in the SoftwareKeyboard that would silently reposition the cursor
   // without motion delay
   return software_keyboard.jump_cursor_pos_to_index_of_key_name(key_name);
}

void CharacterNameInput::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CharacterNameInput::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterNameInput::on_activate: error: guard \"initialized\" not met");
   }
   // TODO: Considider a "reset_on_activate" boolean option
   software_keyboard.reset_with_defaults(
      default_result_text_on_activate,
      default_cursor_position_over_key_name_on_activate
   );
   return;
}

void CharacterNameInput::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CharacterNameInput::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterNameInput::on_deactivate: error: guard \"initialized\" not met");
   }
   return;
}

void CharacterNameInput::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CharacterNameInput::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterNameInput::primary_timer_func: error: guard \"initialized\" not met");
   }
   render();
   return;
}

void CharacterNameInput::set_font_name(std::string font_name)
{
   // TODO: guards, cannot be blank (or maybe this should be a guard in the bin if it is not)
   software_keyboard.set_font_name(font_name);
   return;
}

void CharacterNameInput::set_font_size(int font_size)
{
   // TODO: guards, cannot be zero (or maybe this should be a guard in the bin if it is not)
   software_keyboard.set_font_size(font_size);
   return;
}

void CharacterNameInput::set_event_to_emit_on_pressing_submit_key(std::string event_to_emit_on_pressing_submit_key)
{
   software_keyboard.set_event_to_emit_on_pressing_submit_key(event_to_emit_on_pressing_submit_key);
   return;
}

bool CharacterNameInput::mode_is_using_keyboard()
{
   return mode == MODE_USING_KEYBOARD;
}

bool CharacterNameInput::mode_is_using_virtual_controls()
{
   return mode == MODE_USING_VIRTUAL_CONTROLS;
}

void CharacterNameInput::set_mode_to_using_keyboard()
{
   mode = MODE_USING_KEYBOARD;
   return;
}

void CharacterNameInput::set_mode_to_using_virtual_controls()
{
   mode = MODE_USING_VIRTUAL_CONTROLS;
   return;
}

void CharacterNameInput::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CharacterNameInput::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterNameInput::virtual_control_button_down_func: error: guard \"initialized\" not met");
   }
   if (mode != MODE_USING_VIRTUAL_CONTROLS) return;

   // TODO: validate VirtualControllers::GenericController type

   switch(virtual_controller_button_num)
   {
      case AllegroFlare::VirtualControllers::GenericController::BUTTON_UP:
         software_keyboard.move_cursor_up();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN:
         software_keyboard.move_cursor_down();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_LEFT:
         software_keyboard.decrement_cursor_pos();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT:
         software_keyboard.increment_cursor_pos();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_A:
         software_keyboard.press_key_under_cursor();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_X:
         software_keyboard.press_key_by_name("BACKSPACE");
      break;
   }

   return;
}

void CharacterNameInput::key_char_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CharacterNameInput::key_char_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterNameInput::key_char_func: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[CharacterNameInput::key_char_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterNameInput::key_char_func: error: guard \"event\" not met");
   }
   if (mode != MODE_USING_KEYBOARD) return;

   switch(event->keyboard.keycode)
   {
      case ALLEGRO_KEY_UP:
         software_keyboard.move_cursor_up();
      break;

      case ALLEGRO_KEY_DOWN:
         software_keyboard.move_cursor_down();
      break;

      case ALLEGRO_KEY_RIGHT:
         software_keyboard.increment_cursor_pos();
      break;

      case ALLEGRO_KEY_LEFT:
         software_keyboard.decrement_cursor_pos();
      break;

      case ALLEGRO_KEY_ENTER:
         {
            // TODO: Test this case
            bool shift = (event->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT);
            if (shift) { software_keyboard.press_key_by_name("SUBMIT"); }
            else { software_keyboard.press_key_under_cursor(); }
         }
      break;

      case ALLEGRO_KEY_BACKSPACE:
         software_keyboard.press_key_by_name("BACKSPACE");
      break;

      case ALLEGRO_KEY_SPACE:
         software_keyboard.press_key_by_name("SPACE");
      break;

      default:
         std::string s(1, event->keyboard.unichar);
         software_keyboard.press_key_by_name(s);
      break;
   }
   return;
}

void CharacterNameInput::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CharacterNameInput::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CharacterNameInput::render: error: guard \"initialized\" not met");
   }
   software_keyboard_placement.start_transform();
   software_keyboard.render();
   software_keyboard_placement.restore_transform();
   return;
}


} // namespace Screens
} // namespace AllegroFlare


