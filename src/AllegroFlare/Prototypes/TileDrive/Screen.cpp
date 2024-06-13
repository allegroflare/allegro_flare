

#include <AllegroFlare/Prototypes/TileDrive/Screen.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace TileDrive
{


Screen::Screen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::SampleBin* sample_bin)
   : AllegroFlare::Screens::Base("Prototypes::TileDrive::Screen")
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , sample_bin(sample_bin)
   , tile_drive()
   , initialized(false)
{
}


Screen::~Screen()
{
}


AllegroFlare::Prototypes::TileDrive::TileDrive &Screen::get_tile_drive_ref()
{
   return tile_drive;
}


void Screen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::Screen::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::Screen::set_bitmap_bin]: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   tile_drive.set_bitmap_bin(bitmap_bin);
   return;
}

void Screen::set_sample_bin(AllegroFlare::SampleBin* sample_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::Screen::set_sample_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::Screen::set_sample_bin]: error: guard \"(!initialized)\" not met");
   }
   this->sample_bin = sample_bin;
   tile_drive.set_sample_bin(sample_bin);
   return;
}

void Screen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::Screen::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::Screen::set_font_bin]: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   tile_drive.set_font_bin(font_bin);
   return;
}

void Screen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::Screen::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::Screen::set_event_emitter]: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   tile_drive.set_event_emitter(event_emitter);
   return;
}

void Screen::set_maps_folder(std::string maps_folder)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::Screen::set_maps_folder]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::Screen::set_maps_folder]: error: guard \"(!initialized)\" not met");
   }
   tile_drive.set_maps_folder(maps_folder);
   return;
}

void Screen::set_terrain_mesh_dictionary(std::map<std::string, AllegroFlare::Prototypes::TileDrive::TerrainMeshDictionaryRecord> terrain_mesh_dictionary)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::Screen::set_terrain_mesh_dictionary]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::Screen::set_terrain_mesh_dictionary]: error: guard \"(!initialized)\" not met");
   }
   tile_drive.set_terrain_mesh_dictionary(terrain_mesh_dictionary);
   return;
}

void Screen::set_current_map_identifier(std::string current_map_identifier)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::Screen::set_current_map_identifier]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::Screen::set_current_map_identifier]: error: guard \"(!initialized)\" not met");
   }
   tile_drive.set_current_map_identifier(current_map_identifier);
   return;
}

void Screen::set_collision_stepper_step_result_callback(std::function<void(AllegroFlare::Physics::TileMapCollisionStepperStepResult*,AllegroFlare::Prototypes::TileDrive::TileDrive*,void*)> collision_stepper_step_result_callback, void* collision_stepper_step_result_callback_user_data)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::Screen::set_collision_stepper_step_result_callback]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::Screen::set_collision_stepper_step_result_callback]: error: guard \"(!initialized)\" not met");
   }
   tile_drive.set_collision_stepper_step_result_callback(collision_stepper_step_result_callback);
   tile_drive.set_collision_stepper_step_result_callback_user_data(collision_stepper_step_result_callback_user_data);
   return;
}

void Screen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::Screen::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::Screen::initialize]: error: guard \"(!initialized)\" not met");
   }
   // initialize tile_drive
   tile_drive.set_bitmap_bin(bitmap_bin);
   tile_drive.set_font_bin(font_bin);
   tile_drive.set_event_emitter(event_emitter);
   tile_drive.set_sample_bin(sample_bin);
   tile_drive.initialize();

   // start the level
   tile_drive.reset();

   initialized = true;
   return;
}

void Screen::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::Screen::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::Screen::primary_timer_func]: error: guard \"initialized\" not met");
   }
   tile_drive.update();
   tile_drive.render();
   return;
}

void Screen::key_down_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::Screen::key_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::Screen::key_down_func]: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::Screen::key_down_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::Screen::key_down_func]: error: guard \"event\" not met");
   }
   switch(event->keyboard.keycode)
   {
     case ALLEGRO_KEY_UP:
       tile_drive.driver_press_accelerator();
       break;

     case ALLEGRO_KEY_DOWN:
       tile_drive.driver_press_break();
       break;

     case ALLEGRO_KEY_RIGHT:
       tile_drive.driver_turn_right();
       break;

     case ALLEGRO_KEY_LEFT:
       tile_drive.driver_turn_left();
       break;

     case ALLEGRO_KEY_R:
       tile_drive.reset();
       break;

     case ALLEGRO_KEY_X:
       // TODO: re-evaluate this, consider adding an injectable list of emittable game events
       // HACK:
       if (!event_emitter) throw std::runtime_error("TileDrive/Screen error: KEY_X without an event_emitter");
       event_emitter->emit_game_event(AllegroFlare::GameEvent("open_chronicle_screen"));
       break;
   }
   return;
}

void Screen::key_up_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::Screen::key_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::Screen::key_up_func]: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::Screen::key_up_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::Screen::key_up_func]: error: guard \"event\" not met");
   }
   switch(event->keyboard.keycode)
   {
      case ALLEGRO_KEY_UP:
        tile_drive.driver_unpress_accelerator();
      break;

      case ALLEGRO_KEY_DOWN:
        tile_drive.driver_unpress_break();
      break;

      case ALLEGRO_KEY_RIGHT:
        tile_drive.driver_turn_none();
      break;

      case ALLEGRO_KEY_LEFT:
         tile_drive.driver_turn_none();
      break;
   }
   return;
}


} // namespace TileDrive
} // namespace Prototypes
} // namespace AllegroFlare


