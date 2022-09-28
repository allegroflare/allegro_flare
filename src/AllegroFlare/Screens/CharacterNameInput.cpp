

#include <AllegroFlare/Screens/CharacterNameInput.hpp>

#include <AllegroFlare/VirtualControls.hpp>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


CharacterNameInput::CharacterNameInput(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin, AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard)
   : AllegroFlare::Screens::Base("CharacterNameInput")
   , event_emitter(event_emitter)
   , font_bin(font_bin)
   , software_keyboard(software_keyboard)
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


void CharacterNameInput::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "CharacterNameInput" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "CharacterNameInput" << "::" << "initialize" << ": error: " << "guard \"event_emitter\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "CharacterNameInput" << "::" << "initialize" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   software_keyboard.set_event_emitter(event_emitter);
   software_keyboard.set_font_bin(font_bin);
   software_keyboard.initialize();
   software_keyboard.set_keys(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::build_boilerplate_keyboard_keys());
   AllegroFlare::Vec2D keyboard_dimentions =
   AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::calculate_boilerplate_keyboard_dimentions();
   software_keyboard.set_keyboard_dimentions(keyboard_dimentions.x, keyboard_dimentions.y);
   software_keyboard.set_keyboard_position(1920/2, 1080/12*7 + 20);
   initialized = true;
   return;
}

void CharacterNameInput::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "CharacterNameInput" << "::" << "on_activate" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   software_keyboard.reset();
   return;
}

void CharacterNameInput::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "CharacterNameInput" << "::" << "primary_timer_func" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   render();
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

void CharacterNameInput::virtual_control_button_down_func(int player_num, int button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "CharacterNameInput" << "::" << "virtual_control_button_down_func" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (mode != MODE_USING_VIRTUAL_CONTROLS) return;

   switch(button_num)
   {
      case AllegroFlare::VirtualControls::BUTTON_UP:
         software_keyboard.move_cursor_up();
      break;

      case AllegroFlare::VirtualControls::BUTTON_DOWN:
         software_keyboard.move_cursor_down();
      break;

      case AllegroFlare::VirtualControls::BUTTON_LEFT:
         software_keyboard.decrement_cursor_pos();
      break;

      case AllegroFlare::VirtualControls::BUTTON_RIGHT:
         software_keyboard.increment_cursor_pos();
      break;

      case AllegroFlare::VirtualControls::BUTTON_A:
         software_keyboard.press_key_under_cursor();
      break;

      case AllegroFlare::VirtualControls::BUTTON_X:
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
      error_message << "CharacterNameInput" << "::" << "key_char_func" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "CharacterNameInput" << "::" << "key_char_func" << ": error: " << "guard \"event\" not met";
      throw std::runtime_error(error_message.str());
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
            bool shift = (event->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT);
            if (shift) { software_keyboard.press_key_by_name("OK"); }
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
      error_message << "CharacterNameInput" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   software_keyboard.render();
   return;
}


} // namespace Screens
} // namespace AllegroFlare


