#pragma once


#include <AllegroFlare/SavingAndLoading/SaveSlot.hpp>
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
         int num_save_slots();
         void initialize();
         void scan_for_existing_save_files_and_load_header_files();
         void create_save_file_directories_if_they_do_not_exist();
      };
   }
}



