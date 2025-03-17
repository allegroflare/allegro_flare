#pragma once


#include <AllegroFlare/SavingAndLoading/SaveSlot.hpp>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace SavingAndLoading
   {
      class SavingAndLoading
      {
      public:
         static constexpr char* DEFAULT_DATA_FOLDER_PATH = (char*)"[unset-data_folder_path]";

      public:

         enum class StartStyle
         {
            GAME_START_STYLE_UNDEF = 0,
            GAME_START_STYLE_A,
            GAME_START_STYLE_B,
            GAME_START_STYLE_C,
            GAME_START_STYLE_D,
            GAME_START_STYLE_E,
            GAME_START_STYLE_F,
            GAME_START_STYLE_G,
         };
         enum class SaveStyle
         {
            GAME_SAVE_STYLE_UNDEF = 0,
            GAME_SAVE_STYLE_1,
            GAME_SAVE_STYLE_2,
            GAME_SAVE_STYLE_3,
            GAME_SAVE_STYLE_4,
            GAME_SAVE_STYLE_5,
            GAME_SAVE_STYLE_6,
            GAME_SAVE_STYLE_7,
            GAME_SAVE_STYLE_8,
            GAME_SAVE_STYLE_9,
         };
         enum class LoadStyle
         {
            GAME_LOAD_STYLE_UNDEF = 0,
            GAME_LOAD_STYLE_0,
            GAME_LOAD_STYLE_1,
            GAME_LOAD_STYLE_2,
            GAME_LOAD_STYLE_3,
            GAME_LOAD_STYLE_4,
            GAME_LOAD_STYLE_5,
            GAME_LOAD_STYLE_6,
            GAME_LOAD_STYLE_7,
            GAME_LOAD_STYLE_8,
         };
      private:
         std::string data_folder_path;
         AllegroFlare::SavingAndLoading::SavingAndLoading::StartStyle start_style;
         AllegroFlare::SavingAndLoading::SavingAndLoading::SaveStyle save_style;
         AllegroFlare::SavingAndLoading::SavingAndLoading::LoadStyle load_style;
         int num_profiles;
         int num_manual_save_slots;
         int num_autosave_save_slots;
         int num_quicksave_save_slots;
         std::vector<AllegroFlare::SavingAndLoading::SaveSlot> save_slots;
         bool initialized;
         void save_to_save_slot(int profile_id=0, int save_slot_position=0, uint32_t save_slot_type=AllegroFlare::SavingAndLoading::SaveSlot::SAVE_SLOT_TYPE_UNDEF, std::string content="[unset-content]");
         void __delete_header_and_content_files_and_clear_save_slot__DEPRECATED(int profile_id=0, int save_slot_position=0, uint32_t save_slot_type=AllegroFlare::SavingAndLoading::SaveSlot::SAVE_SLOT_TYPE_UNDEF);

      protected:


      public:
         SavingAndLoading(std::string data_folder_path=DEFAULT_DATA_FOLDER_PATH, AllegroFlare::SavingAndLoading::SavingAndLoading::StartStyle start_style=AllegroFlare::SavingAndLoading::SavingAndLoading::StartStyle::GAME_START_STYLE_UNDEF, AllegroFlare::SavingAndLoading::SavingAndLoading::SaveStyle save_style=AllegroFlare::SavingAndLoading::SavingAndLoading::SaveStyle::GAME_SAVE_STYLE_UNDEF, AllegroFlare::SavingAndLoading::SavingAndLoading::LoadStyle load_style=AllegroFlare::SavingAndLoading::SavingAndLoading::LoadStyle::GAME_LOAD_STYLE_UNDEF);
         ~SavingAndLoading();

         void set_data_folder_path(std::string data_folder_path);
         void set_start_style(AllegroFlare::SavingAndLoading::SavingAndLoading::StartStyle start_style);
         void set_save_style(AllegroFlare::SavingAndLoading::SavingAndLoading::SaveStyle save_style);
         void set_load_style(AllegroFlare::SavingAndLoading::SavingAndLoading::LoadStyle load_style);
         void set_num_profiles(int num_profiles);
         void set_num_manual_save_slots(int num_manual_save_slots);
         void set_num_autosave_save_slots(int num_autosave_save_slots);
         void set_num_quicksave_save_slots(int num_quicksave_save_slots);
         std::string get_data_folder_path() const;
         AllegroFlare::SavingAndLoading::SavingAndLoading::StartStyle get_start_style() const;
         AllegroFlare::SavingAndLoading::SavingAndLoading::SaveStyle get_save_style() const;
         AllegroFlare::SavingAndLoading::SavingAndLoading::LoadStyle get_load_style() const;
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
         std::vector<std::pair<std::string, std::string>> obtain_context_sensitive_menu_items_for_starting_or_loading_the_game();
         bool infer_existing_save_data_exists();
      };
   }
}



