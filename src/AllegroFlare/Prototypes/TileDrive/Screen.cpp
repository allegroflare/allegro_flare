

#include <AllegroFlare/Prototypes/TileDrive/Screen.hpp>

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
      error_message << "Screen" << "::" << "set_bitmap_bin" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
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
      error_message << "Screen" << "::" << "set_sample_bin" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
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
      error_message << "Screen" << "::" << "set_font_bin" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
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
      error_message << "Screen" << "::" << "set_event_emitter" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
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
      error_message << "Screen" << "::" << "set_maps_folder" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   tile_drive.set_maps_folder(maps_folder);
   return;
}

void Screen::set_terrain_mesh_dictionary(std::map<std::string, AllegroFlare::Prototypes::TileDrive::TerrainMeshDictionaryRecord> terrain_mesh_dictionary)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "set_terrain_mesh_dictionary" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   tile_drive.set_terrain_mesh_dictionary(terrain_mesh_dictionary);
   return;
}

void Screen::set_current_map_identifier(std::string current_map_identifier)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "set_current_map_identifier" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   tile_drive.set_current_map_identifier(current_map_identifier);
   return;
}

void Screen::set_collision_stepper_step_result_callback(std::function<void(AllegroFlare::Physics::TileMapCollisionStepperStepResult*,AllegroFlare::Prototypes::TileDrive::TileDrive*,void*)> collision_stepper_step_result_callback, void* collision_stepper_step_result_callback_user_data)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "set_collision_stepper_step_result_callback" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
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
      error_message << "Screen" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
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
      error_message << "Screen" << "::" << "primary_timer_func" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
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
      error_message << "Screen" << "::" << "key_down_func" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "key_down_func" << ": error: " << "guard \"event\" not met";
      throw std::runtime_error(error_message.str());
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
   }
   return;
}

void Screen::key_up_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "key_up_func" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "key_up_func" << ": error: " << "guard \"event\" not met";
      throw std::runtime_error(error_message.str());
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


