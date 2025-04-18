#pragma once


#include <AllegroFlare/LoadASavedGame/SaveSlots/Common.hpp>
#include <AllegroFlare/SavingAndLoading/SaveSlot.hpp>
#include <cstdint>
#include <string>


namespace AllegroFlare
{
   namespace SavingAndLoading
   {
      class SaveSlot
      {
      public:

         enum SaveSlotType
         {
            SAVE_SLOT_TYPE_UNDEF = 0,
            SAVE_SLOT_TYPE_MANUAL_SAVE,
            SAVE_SLOT_TYPE_AUTO_SAVE,
            SAVE_SLOT_TYPE_QUICK_SAVE,
         };
      private:
         std::string data_folder_path;
         int profile_id;
         int save_slot_position;
         AllegroFlare::LoadASavedGame::SaveSlots::Common* header_data;
         uint32_t save_slot_type;
         std::string build_filename_basename();
         bool write_file(std::string filename="[unset-filename]", std::string content="[unset-content]");
         std::string read_file(std::string filename="[unset-filename]");

      protected:


      public:
         SaveSlot();
         ~SaveSlot();

         void set_data_folder_path(std::string data_folder_path);
         std::string get_data_folder_path() const;
         int get_profile_id() const;
         int get_save_slot_position() const;
         AllegroFlare::LoadASavedGame::SaveSlots::Common* get_header_data() const;
         uint32_t get_save_slot_type() const;
         bool is_manual_save();
         bool is_autosave_save();
         bool is_quicksave_save();
         bool is_profile_id(int profile_id=0);
         bool is_empty();
         bool header_data_exists();
         static AllegroFlare::SavingAndLoading::SaveSlot construct(std::string data_folder_path="[unset-data_folder_path]", int profile_id=0, int save_slot_position=0, uint32_t save_slot_type=SAVE_SLOT_TYPE_UNDEF);
         std::string obtain_header_file_data();
         void save_to_slot(std::string* content_for_content_file=nullptr);
         void load_header_from_file_if_exists_or_clear();
         std::string load_data_from_content_file();
         void delete_header_data();
         void delete_header_and_content_files_and_clear();
         bool header_file_exists();
         bool content_file_exists();
         std::string build_full_path_to_header_file();
         std::string build_full_path_to_content_file();
         std::string build_header_basename();
         std::string build_content_basename();
         static std::string obtain_save_slot_type_string_for_filename(uint32_t save_slot_type=SAVE_SLOT_TYPE_UNDEF);
         void create_save_file_directories_if_they_do_not_exist();
         static bool is_valid_type(uint32_t type=SAVE_SLOT_TYPE_UNDEF);
      };
   }
}



