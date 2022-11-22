

#include <AllegroFlare/Prototypes/FixedRoom2D/Screen.hpp>

#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


Screen::Screen(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, std::string game_event_name_to_emit_on_exit)
   : AllegroFlare::Screens::Base("Prototypes::FixedRoom2D::Screen")
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , fixed_room_2d({})
   , initialized(false)
   , game_event_name_to_emit_on_exit(game_event_name_to_emit_on_exit)
{
}


Screen::~Screen()
{
}


void Screen::set_game_event_name_to_emit_on_exit(std::string game_event_name_to_emit_on_exit)
{
   this->game_event_name_to_emit_on_exit = game_event_name_to_emit_on_exit;
}


std::string Screen::get_game_event_name_to_emit_on_exit() const
{
   return game_event_name_to_emit_on_exit;
}


AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D &Screen::get_fixed_room_2d_ref()
{
   return fixed_room_2d;
}


void Screen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
   fixed_room_2d.set_bitmap_bin(bitmap_bin);
   return;
}

void Screen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
   fixed_room_2d.set_font_bin(font_bin);
   return;
}

void Screen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
   fixed_room_2d.set_event_emitter(event_emitter);
   return;
}

void Screen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "initialize" << ": error: " << "guard \"bitmap_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "initialize" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "initialize" << ": error: " << "guard \"event_emitter\" not met";
      throw std::runtime_error(error_message.str());
   }
   fixed_room_2d.set_bitmap_bin(bitmap_bin);
   fixed_room_2d.set_font_bin(font_bin);
   fixed_room_2d.set_event_emitter(event_emitter);
   fixed_room_2d.initialize();

   initialized = true;
   return;
}

void Screen::load_gametest_configuration()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "load_gametest_configuration" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   // TODO: build and inject "gametest_configuration" and pass into a "load_configuration()" call
   fixed_room_2d.load_gametest_configuration();
   return;
}

void Screen::load_configuration(AllegroFlare::Prototypes::FixedRoom2D::Configuration configuration)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "load_configuration" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   fixed_room_2d.load_configuration(configuration);
   return;
}

bool Screen::enter_start_room()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "enter_start_room" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   return fixed_room_2d.enter_start_room();
}

void Screen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "on_activate" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   event_emitter->emit_show_input_hints_bar_event();
   emit_event_to_set_input_hints();
   return;
}

void Screen::game_event_func(AllegroFlare::GameEvent* game_event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "game_event_func" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(game_event))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "game_event_func" << ": error: " << "guard \"game_event\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (fixed_room_2d.is_subscribed_to_game_event_name(game_event->get_type()))
   {
      fixed_room_2d.process_subscribed_to_game_event(game_event);
   };
   return;
}

void Screen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "on_deactivate" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   event_emitter->emit_hide_input_hints_bar_event();
   return;
}

void Screen::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "primary_timer_func" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   fixed_room_2d.update();
   fixed_room_2d.render();
   return;
}

void Screen::key_char_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "key_char_func" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   float cursor_speed = 10.0f;
   switch(ev->keyboard.keycode)
   {
      case ALLEGRO_KEY_UP:
         fixed_room_2d.move_cursor(0, -cursor_speed);
         fixed_room_2d.move_cursor_up();
      break;

      case ALLEGRO_KEY_DOWN:
         fixed_room_2d.move_cursor(0, cursor_speed);
         fixed_room_2d.move_cursor_down();
      break;

      case ALLEGRO_KEY_LEFT:
         fixed_room_2d.move_cursor(-cursor_speed, 0);
         fixed_room_2d.move_cursor_left();
      break;

      case ALLEGRO_KEY_RIGHT:
         fixed_room_2d.move_cursor(cursor_speed, 0);
         fixed_room_2d.move_cursor_right();
      break;

      case ALLEGRO_KEY_ENTER:
         fixed_room_2d.activate_primary_action();
      break;

      //case ALLEGRO_KEY_I:
         //fixed_room_2d.toggle_inventory();
         //emit_event_to_set_input_hints();
      //break;

      case ALLEGRO_KEY_X:
         emit_event_to_exit();
      break;

      case ALLEGRO_KEY_P:
         event_emitter->emit_game_event(AllegroFlare::GameEvent("pause_game"));
         //fixed_room_2d.pause_game();
      break;

      case ALLEGRO_KEY_U:
         event_emitter->emit_game_event(AllegroFlare::GameEvent("unpause_game"));
         //fixed_room_2d.unpause_game();
      break;
   }
   return;
}

void Screen::emit_event_to_exit()
{
   // NOTE: may need guards, or a confirmation dialog
   event_emitter->emit_game_event(game_event_name_to_emit_on_exit);
   return;
}

void Screen::emit_event_to_set_input_hints()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "emit_event_to_set_input_hints" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   //if (fixed_room_2d.inventory_is_open()) emit_event_to_set_input_hints_bar_to_inventory_controls();
   else emit_event_to_set_input_hints_bar_to_room_controls();
   event_emitter->emit_set_input_hints_bar_text_opacity_event(0.265);
   return;
}

void Screen::emit_event_to_set_input_hints_bar_to_inventory_controls()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "emit_event_to_set_input_hints_bar_to_inventory_controls" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   event_emitter->emit_set_input_hints_bar_event({
      "UP", "%SPACE", "DOWN", "%SPACE", "LEFT", "%SPACE", "RIGHT", "%SPACER", "LABEL>>", "Move selector",
      "%SEPARATOR",
      "I", "%SPACER", "LABEL>>", "Toggle inventory",
      "%SEPARATOR",
      "P", "%SPACER", "LABEL>>", "Toggle pause",
   });
   return;
}

void Screen::emit_event_to_set_input_hints_bar_to_room_controls()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "emit_event_to_set_input_hints_bar_to_room_controls" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   event_emitter->emit_set_input_hints_bar_event({
      "UP", "%SPACE", "DOWN", "%SPACE", "LEFT", "%SPACE", "RIGHT", "%SPACER", "LABEL>>", "Move pointer",
      "%SEPARATOR",
      "ENTER", "%SPACER", "LABEL>>", "Inspect object",
      "%SEPARATOR",
      //"I", "%SPACER", "LABEL>>", "Toggle Inventory",
      //"%SEPARATOR",
      "P", "%SPACER", "LABEL>>", "Toggle pause",
   });
   return;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


