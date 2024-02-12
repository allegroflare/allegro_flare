

#include <AllegroFlare/Screens/Version.hpp>

#include <AllegroFlare/Elements/RollingCredits/SectionFactory.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <BuildInfo.hpp>
#include <ReleaseInfo.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


Version::Version(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin, float surface_width, float surface_height)
   : AllegroFlare::Screens::Base(AllegroFlare::Screens::Version::TYPE)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
   , surface_width(surface_width)
   , surface_height(surface_height)
   , cached_calculated_height(0.0f)
   , rolling_credits_component({})
   , on_exit_callback_func()
   , on_exit_callback_func_user_data(nullptr)
   , game_event_name_to_emit_on_exit(DEFAULT_EVENT_NAME_ON_EXIT)
   , initialized(false)
{
}


Version::~Version()
{
}


void Version::set_surface_width(float surface_width)
{
   this->surface_width = surface_width;
}


void Version::set_surface_height(float surface_height)
{
   this->surface_height = surface_height;
}


void Version::set_on_exit_callback_func(std::function<void(AllegroFlare::Screens::Version*, void*)> on_exit_callback_func)
{
   this->on_exit_callback_func = on_exit_callback_func;
}


void Version::set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data)
{
   this->on_exit_callback_func_user_data = on_exit_callback_func_user_data;
}


void Version::set_game_event_name_to_emit_on_exit(std::string game_event_name_to_emit_on_exit)
{
   this->game_event_name_to_emit_on_exit = game_event_name_to_emit_on_exit;
}


float Version::get_surface_width() const
{
   return surface_width;
}


float Version::get_surface_height() const
{
   return surface_height;
}


float Version::get_cached_calculated_height() const
{
   return cached_calculated_height;
}


std::function<void(AllegroFlare::Screens::Version*, void*)> Version::get_on_exit_callback_func() const
{
   return on_exit_callback_func;
}


void* Version::get_on_exit_callback_func_user_data() const
{
   return on_exit_callback_func_user_data;
}


std::string Version::get_game_event_name_to_emit_on_exit() const
{
   return game_event_name_to_emit_on_exit;
}


void Version::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Version::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Version::set_event_emitter: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
}

void Version::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Version::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Version::set_bitmap_bin: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void Version::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Version::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Version::set_font_bin: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void Version::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Version::set_model_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Version::set_model_bin: error: guard \"(!initialized)\" not met");
   }
   this->model_bin = model_bin;
   return;
}

void Version::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Version::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Version::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Version::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Version::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Version::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Version::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Version::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Version::initialize: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Version::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Version::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Version::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Version::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Version::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Version::initialize: error: guard \"font_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[Version::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Version::initialize: error: guard \"model_bin\" not met");
   }
   rolling_credits_component.set_surface_height(surface_height);
   rolling_credits_component.set_surface_width(surface_width);
   rolling_credits_component.set_font_bin(font_bin);
   rolling_credits_component.initialize();

   AllegroFlare::Elements::RollingCredits::SectionFactory section_factory;

   ReleaseInfo release_info;
   BuildInfo build_info;

   rolling_credits_component.set_sections({
      section_factory.create_header("Version"),
      section_factory.create_column_with_labels({
         // TODO: Fill out these values
         {
            "Version",
            release_info.get_version()
         },
         {
            "Allegro Flare",
            truncate_to_n_characters(release_info.get_allegro_flare_version_git_hash())
         },
         {
            "Blast",
            truncate_to_n_characters(release_info.get_blast_version_git_hash())
         },
         //{ "Allegro Flare", release_info.get_allegro_flare_version_git_hash() },
         //{ "Allegro", "5.2.8.0" },
         //{ "Allegro", "5.2.8.0" },
         //{ "AllegroFlare", "0.8.11-wip" },
      }),
      section_factory.create_header("Build"),
      section_factory.create_column_with_labels({
         // TODO: Fill out these values
         {
            "Time of Build",
            build_info.get_time_of_build()
         },
         {
            "Allegro 5",
            truncate_to_n_characters(build_info.get_allegro_version_git_hash())
         },
         {
            "C++ Version",
            build_info.get_cpp_version_string()
         },
      }),
   });
   cached_calculated_height = rolling_credits_component.calculate_height();
   initialized = true;
   //AllegroFlare::Elements::RollingCredits::SectionFactory section_factory;
   return;
}

void Version::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Version::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Version::on_activate: error: guard \"initialized\" not met");
   }
   //emit_event_to_update_input_hints_bar();
   //emit_show_and_size_input_hints_bar_event();
   return;
}

void Version::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Version::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Version::on_deactivate: error: guard \"initialized\" not met");
   }
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void Version::update()
{
   return;
}

void Version::render()
{
   rolling_credits_component.set_y_offset(surface_height/2 - cached_calculated_height/2);
   rolling_credits_component.render();
   return;
}

void Version::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Version::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Version::primary_timer_func: error: guard \"initialized\" not met");
   }
   update();
   render();
   return;
}

void Version::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   // NOTE: Some examples:
   //if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_UP)
      //move_scrollbar_position_up();
   //if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_DOWN)
      //move_scrollbar_position_down();

   event_emitter->emit_game_event(game_event_name_to_emit_on_exit);

   // TODO: Test this
   if (on_exit_callback_func) on_exit_callback_func(this, on_exit_callback_func_user_data);
}

std::string Version::truncate_to_n_characters(std::string str, std::size_t num_characters)
{
   if (!((num_characters >= 1)))
   {
      std::stringstream error_message;
      error_message << "[Version::truncate_to_n_characters]: error: guard \"(num_characters >= 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Version::truncate_to_n_characters: error: guard \"(num_characters >= 1)\" not met");
   }
   if (str.length() <= num_characters) return str;
   return str.substr(0, num_characters);
}


} // namespace Screens
} // namespace AllegroFlare


