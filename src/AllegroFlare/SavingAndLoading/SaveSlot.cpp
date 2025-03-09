

#include <AllegroFlare/SavingAndLoading/SaveSlot.hpp>

#include <filesystem>
#include <iomanip>
#include <iostream>
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


uint32_t SaveSlot::get_save_slot_type() const
{
   return save_slot_type;
}


AllegroFlare::SavingAndLoading::SaveSlot SaveSlot::construct(std::string data_folder_path, int profile_id, int save_slot_position, uint32_t save_slot_type)
{
   if (!((profile_id > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveSlot::construct]: error: guard \"(profile_id > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveSlot::construct]: error: guard \"(profile_id > 0)\" not met");
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

bool SaveSlot::header_file_exists()
{
   // TODO: Test this
   std::string full_path_to_header_filename = data_folder_path + "saves/" + build_header_filename();
   // TODO: Ensure is a file and not a directory or other entry
   return std::filesystem::exists(full_path_to_header_filename);
   return true;
}

bool SaveSlot::content_file_exists()
{
   // TODO: Test this
   std::string full_path_to_content_filename = data_folder_path + "saves/" + build_content_filename();
   // TODO: Ensure is a file and not a directory or other entry
   return std::filesystem::exists(full_path_to_content_filename);
   return true;
}

std::string SaveSlot::build_header_filename()
{
   return build_filename_basename() + ".header.sav";
}

std::string SaveSlot::build_content_filename()
{
   return build_filename_basename() + ".sav";
}

std::string SaveSlot::build_filename_basename()
{
   std::stringstream ss;
   ss << "profile_" << std::setw(3) << std::setfill('0') << profile_id
      << "-"
      << obtain_save_slot_type_string(save_slot_type)
      << "-"
      << "position_" << std::setw(3) << std::setfill('0') << save_slot_position;
   return ss.str();
}

std::string SaveSlot::obtain_save_slot_type_string(uint32_t save_slot_type)
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


} // namespace SavingAndLoading
} // namespace AllegroFlare


