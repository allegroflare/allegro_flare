

#include <AllegroFlare/ShaderSourcePoller.hpp>

#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


ShaderSourcePoller::ShaderSourcePoller(std::string vertex_source_filename, std::string fragment_source_filename, std::string path)
   : vertex_source_filename(vertex_source_filename)
   , fragment_source_filename(fragment_source_filename)
   , path(path)
   , last_recorded_vertex_source_file_changed_at()
   , last_recorded_fragment_source_file_changed_at()
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


void ShaderSourcePoller::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ShaderSourcePoller::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShaderSourcePoller::initialize: error: guard \"(!initialized)\" not met");
   }
   initialized = true;
   poll();
   return;
}

bool ShaderSourcePoller::poll()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[ShaderSourcePoller::poll]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShaderSourcePoller::poll: error: guard \"initialized\" not met");
   }
   if (!(std::filesystem::exists(path + vertex_source_filename)))
   {
      std::stringstream error_message;
      error_message << "[ShaderSourcePoller::poll]: error: guard \"std::filesystem::exists(path + vertex_source_filename)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShaderSourcePoller::poll: error: guard \"std::filesystem::exists(path + vertex_source_filename)\" not met");
   }
   if (!(std::filesystem::exists(path + fragment_source_filename)))
   {
      std::stringstream error_message;
      error_message << "[ShaderSourcePoller::poll]: error: guard \"std::filesystem::exists(path + fragment_source_filename)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShaderSourcePoller::poll: error: guard \"std::filesystem::exists(path + fragment_source_filename)\" not met");
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


