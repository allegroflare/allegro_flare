
#include <gtest/gtest.h>

#include <AllegroFlare/SavingAndLoading/SavingAndLoading.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>
#include <AllegroFlare/Testing/TemporaryDirectoryCreator.hpp>


TEST(AllegroFlare_SavingAndLoading_SavingAndLoadingTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SavingAndLoading::SavingAndLoading saving_and_loading;
}


TEST(AllegroFlare_SavingAndLoading_SavingAndLoadingTest,
   initialize__will_allocate_the_expected_number_of_save_slots)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");

   AllegroFlare::SavingAndLoading::SavingAndLoading saving_and_loading;
   saving_and_loading.set_data_folder_path(deployment_environment.get_data_folder_path());
   saving_and_loading.set_num_profiles(2);
   saving_and_loading.set_num_manual_save_slots(3);
   saving_and_loading.set_num_autosave_save_slots(5);
   saving_and_loading.set_num_quicksave_save_slots(7);
   saving_and_loading.initialize();

   EXPECT_EQ(30, saving_and_loading.num_save_slots());
}


TEST(AllegroFlare_SavingAndLoading_SavingAndLoadingTest,
   create_save_file_directories_if_they_do_not_exist__will_create_the_directories)
{
   std::string temporary_directory = AllegroFlare::Testing::TemporaryDirectoryCreator().create().string();
   AllegroFlare::SavingAndLoading::SavingAndLoading saving_and_loading(temporary_directory);

   saving_and_loading.set_num_profiles(1);
   saving_and_loading.initialize();
   saving_and_loading.create_save_file_directories_if_they_do_not_exist();

   std::string expected_save_directory = temporary_directory + "saves/";
   EXPECT_EQ(true, std::filesystem::exists(expected_save_directory));
}


TEST(AllegroFlare_SavingAndLoading_SavingAndLoadingTest,
   scan_for_existing_save_files_and_load_header_data__will_look_in_the_directory_for_save_files_and_load_the_\
header_data_into_save_slots)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");

   AllegroFlare::SavingAndLoading::SavingAndLoading saving_and_loading;
   saving_and_loading.set_data_folder_path(deployment_environment.get_data_folder_path() + "test_saves/");
   saving_and_loading.set_num_profiles(2);
   saving_and_loading.set_num_manual_save_slots(3);
   saving_and_loading.set_num_autosave_save_slots(5);
   saving_and_loading.set_num_quicksave_save_slots(7);
   saving_and_loading.initialize();

   saving_and_loading.create_save_file_directories_if_they_do_not_exist();
   saving_and_loading.scan_for_existing_save_files_and_load_header_data();

   std::vector<AllegroFlare::SavingAndLoading::SaveSlot> &result_save_slots = saving_and_loading.get_save_slots_ref();
   EXPECT_EQ(30, saving_and_loading.num_save_slots());

   // TODO: Improve this testing robustness, including a test for a malformed save file, and various error cases, and
   // presence of more save files
   // TODO: Consider testing for expected save data fixture files
   int loaded_save_slots = 0;
   for (auto &save_slot : result_save_slots)
   {
      if (save_slot.header_data_exists())
      {
         EXPECT_EQ("The Front Room", save_slot.get_header_data()->location_of_save);
         loaded_save_slots++;
      }
   }
   EXPECT_EQ(1, loaded_save_slots);
}


TEST(AllegroFlare_SavingAndLoading_SavingAndLoadingTest,
   get_autosave_save_slots__will_return_all_save_slots_of_the_type_SAVE_SLOT_TYPE_AUTO_SAVE_belonging_to_a_profile)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");

   AllegroFlare::SavingAndLoading::SavingAndLoading saving_and_loading;
   saving_and_loading.set_data_folder_path(deployment_environment.get_data_folder_path() + "test_saves/");
   saving_and_loading.set_num_profiles(2);
   //saving_and_loading.set_num_manual_save_slots(3);
   saving_and_loading.set_num_autosave_save_slots(5);
   //saving_and_loading.set_num_quicksave_save_slots(7);
   saving_and_loading.initialize();

   //saving_and_loading.create_save_file_directories_if_they_do_not_exist();
   //saving_and_loading.scan_for_existing_save_files_and_load_header_data();

   std::vector<AllegroFlare::SavingAndLoading::SaveSlot*> autosave_save_slots =
      saving_and_loading.get_autosave_save_slots(1);

   EXPECT_EQ(5, autosave_save_slots.size());
   for (auto &save_slot : autosave_save_slots)
   {
      ASSERT_NE(nullptr, save_slot);
      EXPECT_EQ(true, save_slot->is_autosave_save());
      EXPECT_EQ(1, save_slot->get_profile_id());
   }
}


