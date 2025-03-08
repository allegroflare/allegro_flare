

#include <AllegroFlare/SavingAndLoading/SavingAndLoading.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/SavingAndLoading/StandardSavesPath.hpp>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace SavingAndLoading
{


SavingAndLoading::SavingAndLoading(std::string data_folder_path)
   : data_folder_path(data_folder_path)
   , num_profiles(0)
   , num_manual_save_slots(0)
   , num_autosave_save_slots(0)
   , num_quicksave_save_slots(0)
   , save_slots({})
   , initialized(false)
{
}


SavingAndLoading::~SavingAndLoading()
{
}


void SavingAndLoading::set_data_folder_path(std::string data_folder_path)
{
   if (get_initialized()) throw std::runtime_error("[SavingAndLoading::set_data_folder_path]: error: guard \"get_initialized()\" not met.");
   this->data_folder_path = data_folder_path;
}


void SavingAndLoading::set_num_profiles(int num_profiles)
{
   if (get_initialized()) throw std::runtime_error("[SavingAndLoading::set_num_profiles]: error: guard \"get_initialized()\" not met.");
   this->num_profiles = num_profiles;
}


void SavingAndLoading::set_num_manual_save_slots(int num_manual_save_slots)
{
   if (get_initialized()) throw std::runtime_error("[SavingAndLoading::set_num_manual_save_slots]: error: guard \"get_initialized()\" not met.");
   this->num_manual_save_slots = num_manual_save_slots;
}


void SavingAndLoading::set_num_autosave_save_slots(int num_autosave_save_slots)
{
   if (get_initialized()) throw std::runtime_error("[SavingAndLoading::set_num_autosave_save_slots]: error: guard \"get_initialized()\" not met.");
   this->num_autosave_save_slots = num_autosave_save_slots;
}


void SavingAndLoading::set_num_quicksave_save_slots(int num_quicksave_save_slots)
{
   if (get_initialized()) throw std::runtime_error("[SavingAndLoading::set_num_quicksave_save_slots]: error: guard \"get_initialized()\" not met.");
   this->num_quicksave_save_slots = num_quicksave_save_slots;
}


std::string SavingAndLoading::get_data_folder_path() const
{
   return data_folder_path;
}


int SavingAndLoading::get_num_profiles() const
{
   return num_profiles;
}


int SavingAndLoading::get_num_manual_save_slots() const
{
   return num_manual_save_slots;
}


int SavingAndLoading::get_num_autosave_save_slots() const
{
   return num_autosave_save_slots;
}


int SavingAndLoading::get_num_quicksave_save_slots() const
{
   return num_quicksave_save_slots;
}


bool SavingAndLoading::get_initialized() const
{
   return initialized;
}


std::vector<AllegroFlare::SavingAndLoading::SaveSlot> &SavingAndLoading::get_save_slots_ref()
{
   return save_slots;
}


int SavingAndLoading::num_save_slots()
{
   return save_slots.size();
}

void SavingAndLoading::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!((data_folder_path != DEFAULT_DATA_FOLDER_PATH)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met");
   }
   if (!((num_profiles > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_profiles > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_profiles > 0)\" not met");
   }
   if (!((num_profiles <= 6)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_profiles <= 6)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_profiles <= 6)\" not met");
   }
   if (!((num_manual_save_slots >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_manual_save_slots >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_manual_save_slots >= 0)\" not met");
   }
   if (!((num_manual_save_slots <= 99)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_manual_save_slots <= 99)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_manual_save_slots <= 99)\" not met");
   }
   if (!((num_autosave_save_slots >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_autosave_save_slots >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_autosave_save_slots >= 0)\" not met");
   }
   if (!((num_autosave_save_slots <= 90)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_autosave_save_slots <= 90)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_autosave_save_slots <= 90)\" not met");
   }
   if (!((num_quicksave_save_slots >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_quicksave_save_slots >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_quicksave_save_slots >= 0)\" not met");
   }
   if (!((num_quicksave_save_slots <= 10)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_quicksave_save_slots <= 10)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_quicksave_save_slots <= 10)\" not met");
   }
   // TODO: Test guards
   save_slots.clear();

   int total_save_slots = num_profiles * (num_manual_save_slots + num_autosave_save_slots + num_quicksave_save_slots);
   save_slots.reserve(total_save_slots);

   for (int profile_i=0; profile_i<num_profiles; profile_i++)
   {
      for (int manual_save_i=0; manual_save_i<num_manual_save_slots; manual_save_i++)
      {
         save_slots.emplace_back(AllegroFlare::SavingAndLoading::SaveSlot::construct(
            data_folder_path,
            profile_i + 1,
            manual_save_i + 1,
            AllegroFlare::SavingAndLoading::SaveSlot::SaveSlotType::SAVE_SLOT_TYPE_MANUAL_SAVE
         ));
      }

      for (int autosave_save_i=0; autosave_save_i<num_autosave_save_slots; autosave_save_i++)
      {
         save_slots.emplace_back(AllegroFlare::SavingAndLoading::SaveSlot::construct(
            data_folder_path,
            profile_i + 1,
            autosave_save_i + 1,
            AllegroFlare::SavingAndLoading::SaveSlot::SaveSlotType::SAVE_SLOT_TYPE_AUTO_SAVE
         ));
      }

      for (int quicksave_save_i=0; quicksave_save_i<num_quicksave_save_slots; quicksave_save_i++)
      {
         save_slots.emplace_back(AllegroFlare::SavingAndLoading::SaveSlot::construct(
            data_folder_path,
            profile_i + 1,
            quicksave_save_i + 1,
            AllegroFlare::SavingAndLoading::SaveSlot::SaveSlotType::SAVE_SLOT_TYPE_QUICK_SAVE
         ));
      }
   }

   initialized = true;

   return;
}

void SavingAndLoading::scan_for_existing_save_files_and_load_header_data()
{
   for (auto &save_slot : save_slots)
   {
      save_slot.load_header_from_file_if_exists_or_clear();
   }
   return;
}

void SavingAndLoading::create_save_file_directories_if_they_do_not_exist()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SavingAndLoading::create_save_file_directories_if_they_do_not_exist]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SavingAndLoading::create_save_file_directories_if_they_do_not_exist]: error: guard \"initialized\" not met");
   }
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


} // namespace SavingAndLoading
} // namespace AllegroFlare


