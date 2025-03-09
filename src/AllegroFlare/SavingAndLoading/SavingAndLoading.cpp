

#include <AllegroFlare/SavingAndLoading/SavingAndLoading.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace SavingAndLoading
{


SavingAndLoading::SavingAndLoading()
   : data_folder_path(DEFAULT_DATA_FOLDER_PATH)
   , num_profiles(0)
   , num_manual_save_slots(0)
   , num_auto_save_slots(0)
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


void SavingAndLoading::set_num_auto_save_slots(int num_auto_save_slots)
{
   if (get_initialized()) throw std::runtime_error("[SavingAndLoading::set_num_auto_save_slots]: error: guard \"get_initialized()\" not met.");
   this->num_auto_save_slots = num_auto_save_slots;
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


int SavingAndLoading::get_num_auto_save_slots() const
{
   return num_auto_save_slots;
}


int SavingAndLoading::get_num_quicksave_save_slots() const
{
   return num_quicksave_save_slots;
}


bool SavingAndLoading::get_initialized() const
{
   return initialized;
}


int SavingAndLoading::num_save_slots()
{
   return save_slots.size();
}

void SavingAndLoading::initialize()
{
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
   if (!((num_auto_save_slots >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_auto_save_slots >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_auto_save_slots >= 0)\" not met");
   }
   if (!((num_auto_save_slots <= 90)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_auto_save_slots <= 90)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SavingAndLoading::initialize]: error: guard \"(num_auto_save_slots <= 90)\" not met");
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

   int total_save_slots = num_profiles * (num_manual_save_slots + num_auto_save_slots + num_quicksave_save_slots);
   save_slots.resize(total_save_slots);

   for (int profile_i=0; profile_i<num_profiles; profile_i++)
   {
      for (int manual_save_i=0; manual_save_i<num_manual_save_slots; manual_save_i++)
      {
         AllegroFlare::SavingAndLoading::SaveSlot save_slot = AllegroFlare::SavingAndLoading::SaveSlot::construct(
            data_folder_path,
            profile_i + 1,
            manual_save_i + 1,
            AllegroFlare::SavingAndLoading::SaveSlot::SaveSlotType::SAVE_SLOT_TYPE_MANUAL_SAVE
         );
      }

      for (int auto_save_i=0; auto_save_i<num_auto_save_slots; auto_save_i++)
      {
         AllegroFlare::SavingAndLoading::SaveSlot save_slot = AllegroFlare::SavingAndLoading::SaveSlot::construct(
            data_folder_path,
            profile_i + 1,
            auto_save_i + 1,
            AllegroFlare::SavingAndLoading::SaveSlot::SaveSlotType::SAVE_SLOT_TYPE_AUTO_SAVE
         );
      }

      for (int quicksave_save_i=0; quicksave_save_i<num_quicksave_save_slots; quicksave_save_i++)
      {
         AllegroFlare::SavingAndLoading::SaveSlot save_slot = AllegroFlare::SavingAndLoading::SaveSlot::construct(
            data_folder_path,
            profile_i + 1,
            quicksave_save_i + 1,
            AllegroFlare::SavingAndLoading::SaveSlot::SaveSlotType::SAVE_SLOT_TYPE_QUICK_SAVE
         );
      }
   }

   initialized = true;

   return;
}


} // namespace SavingAndLoading
} // namespace AllegroFlare


