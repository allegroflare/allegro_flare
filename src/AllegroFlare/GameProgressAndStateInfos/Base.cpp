

#include <AllegroFlare/GameProgressAndStateInfos/Base.hpp>

#include <AllegroFlare/Logger.hpp>
#include <filesystem>
#include <fstream>
#include <iterator>


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
   // TODO: Test this method
   AllegroFlare::Logger::warn_from(
      "AllegroFlare::GameProgressAndStateInfos::Base::save",
      "This method currently does not check if the location is a valid location for saving, as well as other "
         "overwriting and save file backup scenarios. Please review safety checks for save files."
   );

   // Create the directory if it's not present
   create_directories_to_save_file_if_they_do_not_exist();

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
   // TODO: Test this method
   if (!std::filesystem::exists(save_file_filename))
   {
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::GameProgressAndStateInfos::Base::load",
         "The save file \"" + save_file_filename + "\" is not present. This may be expected behavior if no "
            "save file has been created yet. Note that import_from_string() will not be called. Development todo: "
            "Update this class to expect no file, or create a new file, or optionally hide this warning if it is "
            "expected behavior."
      );
      return;
   }

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
         // TODO: Consider not showing the filename
         "Save file \"" + save_file_filename + "\" import_from_string was successful."
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

void Base::create_directories_to_save_file_if_they_do_not_exist()
{
   // Extract the directory part from the file path
   std::filesystem::path dir_path = std::filesystem::path(save_file_filename).parent_path();

   // Create directories if they do not exist
   if (!dir_path.empty() && !std::filesystem::exists(dir_path))
   {
      if (std::filesystem::create_directories(dir_path))
      {
         AllegroFlare::Logger::info_from(
            "AllegroFlare::GameProgressAndStateInfos::Base::create_directories_to_save_file_if_they_do_not_exist",
            "The expected directories to the save file were not initially present, but were created successfully."
         );
      }
      else
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::GameProgressAndStateInfos::Base::create_directories_to_save_file_if_they_do_not_exist",
            "Failed to load the save file."
         );
         //std::cerr << "Failed to create directories!" << std::endl;
         return;  // Exit if directory creation fails
      }
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


