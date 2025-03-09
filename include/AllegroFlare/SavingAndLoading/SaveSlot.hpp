#pragma once


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
         uint32_t save_slot_type;
         std::string build_filename_basename();

      protected:


      public:
         SaveSlot();
         ~SaveSlot();

         void set_data_folder_path(std::string data_folder_path);
         std::string get_data_folder_path() const;
         int get_profile_id() const;
         int get_save_slot_position() const;
         uint32_t get_save_slot_type() const;
         static AllegroFlare::SavingAndLoading::SaveSlot construct(std::string data_folder_path="[unset-data_folder_path]", int profile_id=0, int save_slot_position=0, uint32_t save_slot_type=SAVE_SLOT_TYPE_UNDEF);
         bool header_file_exists();
         bool content_file_exists();
         std::string build_header_filename();
         std::string build_content_filename();
         static std::string obtain_save_slot_type_string(uint32_t save_slot_type=SAVE_SLOT_TYPE_UNDEF);
         static bool is_valid_type(uint32_t type=SAVE_SLOT_TYPE_UNDEF);
      };
   }
}



