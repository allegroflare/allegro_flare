

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


bool ShaderSourcePoller::poll()
{
   if (!(std::filesystem::exists(vertex_source_filename)))
   {
      std::stringstream error_message;
      error_message << "[ShaderSourcePoller::poll]: error: guard \"std::filesystem::exists(vertex_source_filename)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShaderSourcePoller::poll: error: guard \"std::filesystem::exists(vertex_source_filename)\" not met");
   }
   if (!(std::filesystem::exists(fragment_source_filename)))
   {
      std::stringstream error_message;
      error_message << "[ShaderSourcePoller::poll]: error: guard \"std::filesystem::exists(fragment_source_filename)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShaderSourcePoller::poll: error: guard \"std::filesystem::exists(fragment_source_filename)\" not met");
   }
   bool files_have_changed = true;
   std::filesystem::file_time_type vertex_polled_source_time =
      std::filesystem::last_write_time(vertex_source_filename);
   std::filesystem::file_time_type fragment_polled_source_time =
      std::filesystem::last_write_time(fragment_source_filename);

   if (last_recorded_vertex_source_file_changed_at < vertex_polled_source_time)
   {
      last_recorded_vertex_source_file_changed_at = vertex_polled_source_time;
      files_have_changed = true;
   }

   if (last_recorded_fragment_source_file_changed_at < fragment_polled_source_time)
   {
      last_recorded_fragment_source_file_changed_at = fragment_polled_source_time;
      files_have_changed = true;
   }

   // Get actual last modified time of vertex_source_file
   // if actual last modified time is more recent, prepare an event to update, set return value to true;
   // Get actual last modified time of fragment_source_file
   // if actual last modified time is more recent, prepare an event to update, set return value to true;
   return files_have_changed;
}


} // namespace AllegroFlare


