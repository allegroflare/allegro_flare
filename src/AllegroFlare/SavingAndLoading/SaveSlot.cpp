

#include <AllegroFlare/SavingAndLoading/SaveSlot.hpp>

#include <AllegroFlare/JSONLoaders/AllegroFlare/LoadASavedGame/SaveSlots/Common.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/SavingAndLoading/StandardSavesPath.hpp>
#include <AllegroFlare/TimeStamper.hpp>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <lib/nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>
#include <unordered_map>


namespace AllegroFlare
{
namespace SavingAndLoading
{


SaveSlot::SaveSlot()
   : data_folder_path("[unset-data_folder_path]")
   , profile_id(0)
   , save_slot_position(0)
   , header_data(nullptr)
   , save_slot_type(SAVE_SLOT_TYPE_UNDEF)
{
}


SaveSlot::~SaveSlot()
{
}


void SaveSlot::set_data_folder_path(std::string data_folder_path)
{
   this->data_folder_path = data_folder_path;
}


std::string SaveSlot::get_data_folder_path() const
{
   return data_folder_path;
}


int SaveSlot::get_profile_id() const
{
   return profile_id;
}


int SaveSlot::get_save_slot_position() const
{
   return save_slot_position;
}


AllegroFlare::LoadASavedGame::SaveSlots::Common* SaveSlot::get_header_data() const
{
   return header_data;
}


uint32_t SaveSlot::get_save_slot_type() const
{
   return save_slot_type;
}


bool SaveSlot::is_manual_save()
{
   return save_slot_type == SAVE_SLOT_TYPE_MANUAL_SAVE;
}

bool SaveSlot::is_autosave_save()
{
   return save_slot_type == SAVE_SLOT_TYPE_AUTO_SAVE;
}

bool SaveSlot::is_quicksave_save()
{
   return save_slot_type == SAVE_SLOT_TYPE_QUICK_SAVE;
}

bool SaveSlot::is_profile_id(int profile_id)
{
   if (!((profile_id >= 1)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveSlot::is_profile_id]: error: guard \"(profile_id >= 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveSlot::is_profile_id]: error: guard \"(profile_id >= 1)\" not met");
   }
   return this->profile_id == profile_id;
}

bool SaveSlot::is_empty()
{
   return !header_data_exists();
}

bool SaveSlot::header_data_exists()
{
   return header_data != nullptr;
}

AllegroFlare::SavingAndLoading::SaveSlot SaveSlot::construct(std::string data_folder_path, int profile_id, int save_slot_position, uint32_t save_slot_type)
{
   if (!((profile_id >= 1)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveSlot::construct]: error: guard \"(profile_id >= 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveSlot::construct]: error: guard \"(profile_id >= 1)\" not met");
   }
   if (!((save_slot_position > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveSlot::construct]: error: guard \"(save_slot_position > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveSlot::construct]: error: guard \"(save_slot_position > 0)\" not met");
   }
   if (!(is_valid_type(save_slot_type)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveSlot::construct]: error: guard \"is_valid_type(save_slot_type)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveSlot::construct]: error: guard \"is_valid_type(save_slot_type)\" not met");
   }
   AllegroFlare::SavingAndLoading::SaveSlot result_save_slot;
   result_save_slot.data_folder_path = data_folder_path;
   result_save_slot.profile_id = profile_id;
   result_save_slot.save_slot_position = save_slot_position;
   result_save_slot.save_slot_type = save_slot_type;
   return result_save_slot;
}

std::string SaveSlot::obtain_header_file_data()
{
   if (!(header_file_exists()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveSlot::obtain_header_file_data]: error: guard \"header_file_exists()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveSlot::obtain_header_file_data]: error: guard \"header_file_exists()\" not met");
   }
   std::string file_path = build_full_path_to_header_file();
   std::ifstream file(file_path);
   if (!file)
   {
      AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME,
         "Could not open file: \"" + file_path + "\". This is unexpected because the logic flow up to this point "
           "is expected to have already validated the presence of the file."
      );
   }
   std::ostringstream buffer;
   buffer << file.rdbuf();
   return buffer.str();
}

void SaveSlot::save_to_slot(std::string* content_for_content_file)
{
   // Create new header data if it does not exist
   if (!header_data) header_data = new AllegroFlare::LoadASavedGame::SaveSlots::Common;

   // Create the directory for the save files if it does not exist
   create_save_file_directories_if_they_do_not_exist();

   // Fill header data with this current save data
   std::time_t save_time_since_epoch = AllegroFlare::TimeStamper::generate_time_now_since_epoch();
   std::string user_friendly_time = AllegroFlare::TimeStamper::user_friendly_time(save_time_since_epoch);

   // Populate the header data
   header_data->screenshot_of_gameplay_at_save_identifier = "scene3-01.jpg";
   header_data->location_of_save = "Unknown Location";
   header_data->date_and_time_of_save = user_friendly_time;
   header_data->time_since_text = "[unset-time_since_text]"; // TODO: Remove this property from the class
   header_data->save_time__seconds_since_epoch = save_time_since_epoch;

   // TODO: Consider a write-to-temp-then swap
   // Build the header file
   nlohmann::json j = *header_data;
   std::string content_for_header_file = j.dump(2);
   std::string filename_for_header_file = build_full_path_to_header_file();
   if (!write_file(filename_for_header_file, content_for_header_file))
   {
      AllegroFlare::Logger::warn_from(THIS_CLASS_AND_METHOD_NAME, "header file did not not save successfully");
   }

   // Build the content file
   // TODO: Save content from injected
   // TODO: Optimize this to avoid duplication of content;
   std::string content_file_content = (content_for_content_file == nullptr) ? "{}" : *content_for_content_file;
   std::string filename_for_content_file = build_full_path_to_content_file();
   if (!write_file(filename_for_content_file, content_file_content))
   {
      AllegroFlare::Logger::warn_from(THIS_CLASS_AND_METHOD_NAME, "content file did not not save successfully");
   }
   return;
}

void SaveSlot::load_header_from_file_if_exists_or_clear()
{
   // TODO: Test this
   // Cleaer header data if some has already been loaded into this slot
   if (header_data_exists()) delete_header_data();

   bool _header_file_exists = header_file_exists();
   bool _content_file_exists = content_file_exists();
   if (!_header_file_exists && !_content_file_exists)
   {
      // Neither header nor content files exist
      // Do nothing
   }
   else if ((_header_file_exists && !_content_file_exists) || (!_header_file_exists && _content_file_exists))
   {
      // Either header or content files exists, but not both
      AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME,
         "When loading header data, either the header OR the content file is present but not both. It's expected "
            "that both files are present. Please improve this error message to output filenames for easier "
            "debugging."
      );
   }
   else if (_header_file_exists && _content_file_exists)
   {
      // Both header and content files exist
      std::string file_content = obtain_header_file_data();
      nlohmann::json parsed_json = nlohmann::json::parse(file_content);
      header_data = new AllegroFlare::LoadASavedGame::SaveSlots::Common;
      parsed_json.get_to(*header_data); // TODO: Good enough?
   }
   else
   {
      // Either header or content files exists, but not both
      AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME, "Unexpected code path");
   }

   return;
}

std::string SaveSlot::load_data_from_content_file()
{
   // TODO: Test this
   // Cleaer header data if some has already been loaded into this slot
   if (!header_data_exists())
   {
      AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME,
         "When loading content data, there is not any header data created on this save slot, indicating that no "
         "save exists on this save slot."
      );
   }

   bool _content_file_exists = content_file_exists();
   if (!_content_file_exists)
   {
      AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME,
         "It appears that no content file exists for this save slot, despite that header data does exist. It "
         "appears something may have gone wrong with the saving/loading system."
      );
   }

   // Load the actual file content
   std::string full_path_to_content_filename = build_full_path_to_content_file();
   return read_file(full_path_to_content_filename);
}

void SaveSlot::delete_header_data()
{
   if (header_data == nullptr) return;
   delete header_data;
   header_data = nullptr;
   return;
}

void SaveSlot::delete_header_and_content_files_and_clear()
{
   // NOTE: If no files are present, no result or warning output, currently. If there's reason to change this
   // then feel free to.

   // Delete data file for header data
   std::string full_path_to_header_file = build_full_path_to_header_file();
   bool header_file_exists = std::filesystem::exists(full_path_to_header_file);
   if (!header_file_exists)
   {
      // TODO: Nothing
   }
   else
   {
      // TODO: Logging?
      bool header_file_removed = std::filesystem::remove(full_path_to_header_file);
      bool header_file_exists_after_removal = std::filesystem::exists(full_path_to_header_file);
      if (!header_file_exists_after_removal)
      {
         AllegroFlare::Logger::warn_from(THIS_CLASS_AND_METHOD_NAME,
            "When trying to delete the save header file at \"" + full_path_to_header_file + "\", it was not "
            "deleted when this system attempted to delete it. There may be another application using the file. "
            "It may need to be deleted manually."
         );
      }
      else
      {
         AllegroFlare::Logger::info_from(THIS_CLASS_AND_METHOD_NAME,
            "Save header file at \"" + full_path_to_header_file + "\" was deleted successfully."
         );
      }
   }

   // Delete data file for content data
   std::string full_path_to_content_file = build_full_path_to_content_file();
   bool content_file_exists = std::filesystem::exists(full_path_to_content_file);
   if (!content_file_exists)
   {
      // TODO: Nothing
   }
   else
   {
      // TODO: Logging?
      bool content_file_removed = std::filesystem::remove(full_path_to_content_file);
      bool content_file_exists_after_removal = std::filesystem::exists(full_path_to_content_file);
      if (!content_file_exists_after_removal)
      {
         AllegroFlare::Logger::warn_from(THIS_CLASS_AND_METHOD_NAME,
            "When trying to delete the save content file at \"" + full_path_to_content_file + "\", it was not "
            "deleted when this system attempted to delete it. There may be another application using the file. "
            "It may need to be deleted manually."
         );
      }
      else
      {
         AllegroFlare::Logger::info_from(THIS_CLASS_AND_METHOD_NAME,
            "Save content file at \"" + full_path_to_content_file + "\" was deleted successfully."
         );
      }
   }

   // Clear header data
   delete_header_data();
   return;
}

bool SaveSlot::header_file_exists()
{
   // TODO: Test this
   std::string full_path_to_header_filename = build_full_path_to_header_file();
   // TODO: Ensure is a file and not a directory or other entry
   return std::filesystem::exists(full_path_to_header_filename);
   return true;
}

bool SaveSlot::content_file_exists()
{
   // TODO: Test this
   std::string full_path_to_content_filename = build_full_path_to_content_file();
   // TODO: Ensure is a file and not a directory or other entry
   return std::filesystem::exists(full_path_to_content_filename);
   return true;
}

std::string SaveSlot::build_full_path_to_header_file()
{
   std::string standard_saves_path =
      AllegroFlare::SavingAndLoading::StandardSavesPath::build_standard_path(data_folder_path);
   return standard_saves_path + build_header_basename();
}

std::string SaveSlot::build_full_path_to_content_file()
{
   std::string standard_saves_path =
      AllegroFlare::SavingAndLoading::StandardSavesPath::build_standard_path(data_folder_path);
   return standard_saves_path + build_content_basename();
}

std::string SaveSlot::build_header_basename()
{
   return build_filename_basename() + ".header.sav";
}

std::string SaveSlot::build_content_basename()
{
   return build_filename_basename() + ".sav";
}

std::string SaveSlot::build_filename_basename()
{
   std::stringstream ss;
   ss << "profile_" << std::setw(3) << std::setfill('0') << profile_id
      << "-"
      << obtain_save_slot_type_string_for_filename(save_slot_type)
      << "-"
      << "position_" << std::setw(3) << std::setfill('0') << save_slot_position;
   return ss.str();
}

std::string SaveSlot::obtain_save_slot_type_string_for_filename(uint32_t save_slot_type)
{
   static const std::unordered_map<uint32_t, std::string> event_names {
      { SAVE_SLOT_TYPE_MANUAL_SAVE, "manual_save" },
      { SAVE_SLOT_TYPE_AUTO_SAVE, "autosave" },
      { SAVE_SLOT_TYPE_QUICK_SAVE, "quicksave" },
   };

   auto it = event_names.find(save_slot_type);

   if (it == event_names.end())
   {
      return "SAVE_SLOT_TYPE_UNKNOWN";
   }
   else
   {
      return it->second;
   }
}

void SaveSlot::create_save_file_directories_if_they_do_not_exist()
{
   // TODO: Test this with a temporary directory
   std::string standard_saves_path = AllegroFlare::SavingAndLoading::StandardSavesPath::build_standard_path(
      data_folder_path
   );
   // Extract the directory part from the file path
   std::filesystem::path dir_path = std::filesystem::path(standard_saves_path).parent_path();

   // Create directories if they do not exist
   if (!dir_path.empty() && !std::filesystem::exists(dir_path))
   {
      if (std::filesystem::create_directories(dir_path))
      {
         AllegroFlare::Logger::info_from(THIS_CLASS_AND_METHOD_NAME,
            "The expected directories to the save file were not initially present, but were created successfully."
         );
      }
      else
      {
         AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME,
            "Failed to load the save file."
         );
         //std::cerr << "Failed to create directories!" << std::endl;
         return;  // Exit if directory creation fails
      }
   }
   return;
}

bool SaveSlot::is_valid_type(uint32_t type)
{
   static const std::unordered_map<uint32_t, std::string> event_names {
      { SAVE_SLOT_TYPE_MANUAL_SAVE, "manual_save" },
      { SAVE_SLOT_TYPE_AUTO_SAVE, "autosave" },
      { SAVE_SLOT_TYPE_QUICK_SAVE, "quicksave" },
   };

   auto it = event_names.find(type);
   if (it == event_names.end()) return false;
   return true;
}

bool SaveSlot::write_file(std::string filename, std::string content)
{
   AllegroFlare::Logger::info_from(THIS_CLASS_AND_METHOD_NAME,
      "Writing file \"" + filename + "\"."
   );
   //std::cout << "Writing file \"" << filename << "\"." << std::endl;
   // TODO: Find some way to avoid the *content duplication into this method
   std::ofstream file;
   file.open(filename.c_str());
   if (!file.is_open()) return false;
   file << content.c_str();
   file.close();
   return true;
}

std::string SaveSlot::read_file(std::string filename)
{
   if (!(std::filesystem::exists(filename)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveSlot::read_file]: error: guard \"std::filesystem::exists(filename)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveSlot::read_file]: error: guard \"std::filesystem::exists(filename)\" not met");
   }
   AllegroFlare::Logger::info_from(THIS_CLASS_AND_METHOD_NAME,
      "Reading file \"" + filename + "\"."
   );
   //std::cout << "Reading file \"" << filename << "\"." << std::endl;
   std::ifstream file(filename.c_str());
   if (!file.is_open()) return "[error: unable to open file]";
   std::stringstream buffer;
   buffer << file.rdbuf();
   file.close();
   return buffer.str();
}


} // namespace SavingAndLoading
} // namespace AllegroFlare


