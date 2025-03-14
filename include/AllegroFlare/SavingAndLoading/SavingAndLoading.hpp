#pragma once


#include <AllegroFlare/SavingAndLoading/SaveSlot.hpp>
#include <cstdint>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace SavingAndLoading
   {
      class SavingAndLoading
      {
      public:
         static constexpr char* DEFAULT_DATA_FOLDER_PATH = (char*)"[unset-data_folder_path]";

      private:
         std::string data_folder_path;
         int num_profiles;
         int num_manual_save_slots;
         int num_autosave_save_slots;
         int num_quicksave_save_slots;
         std::vector<AllegroFlare::SavingAndLoading::SaveSlot> save_slots;
         bool initialized;
         void save_to_save_slot(int profile_id=0, int save_slot_position=0, uint32_t save_slot_type=AllegroFlare::SavingAndLoading::SaveSlot::SAVE_SLOT_TYPE_UNDEF, std::string content="[unset-content]");

      protected:


      public:
         SavingAndLoading(std::string data_folder_path=DEFAULT_DATA_FOLDER_PATH);
         ~SavingAndLoading();

         void set_data_folder_path(std::string data_folder_path);
         void set_num_profiles(int num_profiles);
         void set_num_manual_save_slots(int num_manual_save_slots);
         void set_num_autosave_save_slots(int num_autosave_save_slots);
         void set_num_quicksave_save_slots(int num_quicksave_save_slots);
         std::string get_data_folder_path() const;
         int get_num_profiles() const;
         int get_num_manual_save_slots() const;
         int get_num_autosave_save_slots() const;
         int get_num_quicksave_save_slots() const;
         bool get_initialized() const;
         std::vector<AllegroFlare::SavingAndLoading::SaveSlot> &get_save_slots_ref();
         int num_save_slots();
         std::vector<AllegroFlare::SavingAndLoading::SaveSlot*> get_manual_save_slots(int profile_id=1);
         std::vector<AllegroFlare::SavingAndLoading::SaveSlot*> get_autosave_save_slots(int profile_id=1);
         std::vector<AllegroFlare::SavingAndLoading::SaveSlot*> get_quicksave_save_slots(int profile_id=1);
         static void sort_by_empty_then_oldest(std::vector<AllegroFlare::SavingAndLoading::SaveSlot*>* unsorted_save_slots=nullptr);
         void initialize();
         void scan_for_existing_save_files_and_load_header_data();
         void save_to_manual_save_slot(int profile_id=0, int save_slot_position=0, std::string content="[unset-content]");
         void save_to_autosave(int profile_id=0, std::string content="[unset-content]");
         void save_to_quicksave(int profile_id=0, std::string content="[unset-content]");
         std::string load_content_from_manual_save_content_file(int profile_id=0, int save_slot_position=0);
         AllegroFlare::SavingAndLoading::SaveSlot* find_save_slot(int profile_id=0, int save_slot_position=0, uint32_t save_slot_type=AllegroFlare::SavingAndLoading::SaveSlot::SAVE_SLOT_TYPE_UNDEF);
         bool has_quicksave_save_slots();
         bool has_autosave_save_slots();
         void create_save_file_directories_if_they_do_not_exist();
      };
   }
}



