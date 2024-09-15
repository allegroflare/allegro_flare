

#include <AllegroFlare/GameProgressAndStateInfos/Base.hpp>

#include <AllegroFlare/Logger.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace GameProgressAndStateInfos
{


Base::Base(std::string type)
   : type(type)
   , save_file_filename(DEFAULT_FILENAME)
{
}


Base::~Base()
{
}


void Base::set_save_file_filename(std::string save_file_filename)
{
   this->save_file_filename = save_file_filename;
}


std::string Base::get_type() const
{
   return type;
}


std::string Base::get_save_file_filename() const
{
   return save_file_filename;
}


void Base::save()
{
   if (!(std::filesystem::exists(save_file_filename)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameProgressAndStateInfos::Base::save]: error: guard \"std::filesystem::exists(save_file_filename)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameProgressAndStateInfos::Base::save]: error: guard \"std::filesystem::exists(save_file_filename)\" not met");
   }
   // TODO: Consider creating the directory if it's not present
   // TODO: Test this
   // For stability reasons, export of the data will be attempted before attempting to open the file for writing
   std::string data = export_to_string();

   // Open a file for writing
   std::ofstream file;
   file.open(save_file_filename);

   // Check if the file opened successfully
   if (file.is_open())
   {
      file << data;
      file.close();
      AllegroFlare::Logger::info_from(
         "AllegroFlare::GameProgressAndStateInfos::Base::save",
         "Save file \"" + save_file_filename + "\" saved." // TODO: Consider not showing the filename
      );
   }
   else
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::GameProgressAndStateInfos::Base::save",
         "Failed to save the progress because the file \"" + save_file_filename + "\" could not be opened."
      );
   }

   return;
}

void Base::load()
{
   if (!(std::filesystem::exists(save_file_filename)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameProgressAndStateInfos::Base::load]: error: guard \"std::filesystem::exists(save_file_filename)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameProgressAndStateInfos::Base::load]: error: guard \"std::filesystem::exists(save_file_filename)\" not met");
   }
   // TODO: Test this
   std::ifstream file(save_file_filename);

   // Check if the file opened successfully
   if (file.is_open())
   {
      // Load the entire file content into the string
      std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
      file.close();
      
      AllegroFlare::Logger::info_from(
         "AllegroFlare::GameProgressAndStateInfos::Base::load",
         "Save file \"" + save_file_filename + "\" read successfully." // TODO: Consider not showing the filename
      );

      import_from_string(data);

      AllegroFlare::Logger::info_from(
         "AllegroFlare::GameProgressAndStateInfos::Base::load",
         "Save file \"" + save_file_filename + "\" loaded." // TODO: Consider not showing the filename
      );
   }
   else
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::GameProgressAndStateInfos::Base::load",
         "Failed to load the save file because the file \"" + save_file_filename + "\" could not be opened."
      );
   }

   return;
}

std::string Base::export_to_string()
{
   AllegroFlare::Logger::throw_error(
         "AllegroFlare::GameProgressAndStateInfos::Base::export_to_string",
         "not implemented"
      );
   return "";
}

void Base::import_from_string(std::string data_string)
{
   AllegroFlare::Logger::throw_error(
         "AllegroFlare::GameProgressAndStateInfos::Base::import_from_string",
         "not implemented"
      );
   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace GameProgressAndStateInfos
} // namespace AllegroFlare


