

#include <AllegroFlare/ShaderSourcePoller.hpp>

#include <AllegroFlare/UsefulPHP.hpp>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


ShaderSourcePoller::ShaderSourcePoller(ALLEGRO_EVENT_QUEUE* event_queue, std::string vertex_source_filename, std::string fragment_source_filename, std::string path)
   : event_queue(event_queue)
   , vertex_source_filename(vertex_source_filename)
   , fragment_source_filename(fragment_source_filename)
   , path(path)
   , last_recorded_vertex_source_file_changed_at()
   , last_recorded_fragment_source_file_changed_at()
   , polling_timer(nullptr)
   , polling_active(false)
   , initialized(false)
{
}


ShaderSourcePoller::~ShaderSourcePoller()
{
}


void ShaderSourcePoller::set_vertex_source_filename(std::string vertex_source_filename)
{
   this->vertex_source_filename = vertex_source_filename;
}


void ShaderSourcePoller::set_fragment_source_filename(std::string fragment_source_filename)
{
   this->fragment_source_filename = fragment_source_filename;
}


void ShaderSourcePoller::set_path(std::string path)
{
   this->path = path;
}


ALLEGRO_EVENT_QUEUE* ShaderSourcePoller::get_event_queue() const
{
   return event_queue;
}


std::string ShaderSourcePoller::get_vertex_source_filename() const
{
   return vertex_source_filename;
}


std::string ShaderSourcePoller::get_fragment_source_filename() const
{
   return fragment_source_filename;
}


std::string ShaderSourcePoller::get_path() const
{
   return path;
}


std::filesystem::file_time_type ShaderSourcePoller::get_last_recorded_vertex_source_file_changed_at() const
{
   return last_recorded_vertex_source_file_changed_at;
}


std::filesystem::file_time_type ShaderSourcePoller::get_last_recorded_fragment_source_file_changed_at() const
{
   return last_recorded_fragment_source_file_changed_at;
}


ALLEGRO_TIMER* ShaderSourcePoller::get_polling_timer() const
{
   return polling_timer;
}


void ShaderSourcePoller::set_event_queue(ALLEGRO_EVENT_QUEUE* event_queue)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ShaderSourcePoller::set_event_queue]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ShaderSourcePoller::set_event_queue]: error: guard \"(!initialized)\" not met");
   }
   if (!(event_queue))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ShaderSourcePoller::set_event_queue]: error: guard \"event_queue\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ShaderSourcePoller::set_event_queue]: error: guard \"event_queue\" not met");
   }
   this->event_queue = event_queue;
   return;
}

void ShaderSourcePoller::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ShaderSourcePoller::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ShaderSourcePoller::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ShaderSourcePoller::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ShaderSourcePoller::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(event_queue))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ShaderSourcePoller::initialize]: error: guard \"event_queue\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ShaderSourcePoller::initialize]: error: guard \"event_queue\" not met");
   }
   polling_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(1)); // one poll per second
   initialized = true;
   poll();
   return;
}

void ShaderSourcePoller::start_polling()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ShaderSourcePoller::start_polling]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ShaderSourcePoller::start_polling]: error: guard \"initialized\" not met");
   }
   if (!((!polling_active)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ShaderSourcePoller::start_polling]: error: guard \"(!polling_active)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ShaderSourcePoller::start_polling]: error: guard \"(!polling_active)\" not met");
   }
   al_register_event_source(event_queue, al_get_timer_event_source(polling_timer));
   al_start_timer(polling_timer);
   polling_active = true;
   return;
}

void ShaderSourcePoller::stop_polling()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ShaderSourcePoller::stop_polling]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ShaderSourcePoller::stop_polling]: error: guard \"initialized\" not met");
   }
   if (!(polling_active))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ShaderSourcePoller::stop_polling]: error: guard \"polling_active\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ShaderSourcePoller::stop_polling]: error: guard \"polling_active\" not met");
   }
   al_stop_timer(polling_timer);
   al_unregister_event_source(event_queue, al_get_timer_event_source(polling_timer));
   polling_active = false;
   return;
}

std::string ShaderSourcePoller::read_vertex_source_code_from_file()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ShaderSourcePoller::read_vertex_source_code_from_file]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ShaderSourcePoller::read_vertex_source_code_from_file]: error: guard \"initialized\" not met");
   }
   if (!(std::filesystem::exists(path + vertex_source_filename)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ShaderSourcePoller::read_vertex_source_code_from_file]: error: guard \"std::filesystem::exists(path + vertex_source_filename)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ShaderSourcePoller::read_vertex_source_code_from_file]: error: guard \"std::filesystem::exists(path + vertex_source_filename)\" not met");
   }
   return AllegroFlare::php::file_get_contents(path + vertex_source_filename);
}

std::string ShaderSourcePoller::read_fragment_source_code_from_file()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ShaderSourcePoller::read_fragment_source_code_from_file]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ShaderSourcePoller::read_fragment_source_code_from_file]: error: guard \"initialized\" not met");
   }
   if (!(std::filesystem::exists(path + fragment_source_filename)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ShaderSourcePoller::read_fragment_source_code_from_file]: error: guard \"std::filesystem::exists(path + fragment_source_filename)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ShaderSourcePoller::read_fragment_source_code_from_file]: error: guard \"std::filesystem::exists(path + fragment_source_filename)\" not met");
   }
   return AllegroFlare::php::file_get_contents(path + fragment_source_filename);
}

bool ShaderSourcePoller::poll()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ShaderSourcePoller::poll]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ShaderSourcePoller::poll]: error: guard \"initialized\" not met");
   }
   if (!(std::filesystem::exists(path + vertex_source_filename)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ShaderSourcePoller::poll]: error: guard \"std::filesystem::exists(path + vertex_source_filename)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ShaderSourcePoller::poll]: error: guard \"std::filesystem::exists(path + vertex_source_filename)\" not met");
   }
   if (!(std::filesystem::exists(path + fragment_source_filename)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ShaderSourcePoller::poll]: error: guard \"std::filesystem::exists(path + fragment_source_filename)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ShaderSourcePoller::poll]: error: guard \"std::filesystem::exists(path + fragment_source_filename)\" not met");
   }
   // TODO: consider adding better error messages on exists() that would also include the current path
   bool files_have_changed = false;
   std::filesystem::file_time_type vertex_polled_source_time =
      std::filesystem::last_write_time(path + vertex_source_filename);
   std::filesystem::file_time_type fragment_polled_source_time =
      std::filesystem::last_write_time(path + fragment_source_filename);

   if (last_recorded_vertex_source_file_changed_at != vertex_polled_source_time)
   {
      last_recorded_vertex_source_file_changed_at = vertex_polled_source_time;
      files_have_changed = true;
   }

   if (last_recorded_fragment_source_file_changed_at != fragment_polled_source_time)
   {
      last_recorded_fragment_source_file_changed_at = fragment_polled_source_time;
      files_have_changed = true;
   }

   return files_have_changed;
}


} // namespace AllegroFlare


