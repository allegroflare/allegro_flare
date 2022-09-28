

#include <AllegroFlare/Screens/CharacterNameInputScreen.hpp>

#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


CharacterNameInputScreen::CharacterNameInputScreen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin, AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard)
   : AllegroFlare::Screens::Base("CharacterNameInputScreen")
   , event_emitter(event_emitter)
   , font_bin(font_bin)
   , software_keyboard(software_keyboard)
   , initialized(false)
{
}


CharacterNameInputScreen::~CharacterNameInputScreen()
{
}


void CharacterNameInputScreen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void CharacterNameInputScreen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void CharacterNameInputScreen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "CharacterNameInputScreen" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "CharacterNameInputScreen" << "::" << "initialize" << ": error: " << "guard \"event_emitter\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "CharacterNameInputScreen" << "::" << "initialize" << ": error: " << "guard \"font_bin\" not met";
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

void CharacterNameInputScreen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "CharacterNameInputScreen" << "::" << "on_activate" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   software_keyboard.reset();
   return;
}

void CharacterNameInputScreen::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "CharacterNameInputScreen" << "::" << "primary_timer_func" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   render();
   return;
}

void CharacterNameInputScreen::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "CharacterNameInputScreen" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   software_keyboard.render();
   return;
}


} // namespace Screens
} // namespace AllegroFlare


