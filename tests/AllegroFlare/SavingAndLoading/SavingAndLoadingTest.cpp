
#include <gtest/gtest.h>

#include <AllegroFlare/SavingAndLoading/SavingAndLoading.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>
#include <AllegroFlare/Testing/TemporaryDirectoryCreator.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


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
   saving_and_loading.set_start_style(AllegroFlare::SavingAndLoading::SavingAndLoading::StartStyle::GAME_START_STYLE_A);
   saving_and_loading.set_save_style(AllegroFlare::SavingAndLoading::SavingAndLoading::SaveStyle::GAME_SAVE_STYLE_4);
   saving_and_loading.set_load_style(AllegroFlare::SavingAndLoading::SavingAndLoading::LoadStyle::GAME_LOAD_STYLE_0);
   saving_and_loading.initialize();

   EXPECT_EQ(30, saving_and_loading.num_save_slots());
}


TEST(AllegroFlare_SavingAndLoading_SavingAndLoadingTest,
   create_save_file_directories_if_they_do_not_exist__will_create_the_directories)
{
   std::string temporary_directory = AllegroFlare::Testing::TemporaryDirectoryCreator().create().string();
   AllegroFlare::SavingAndLoading::SavingAndLoading saving_and_loading(temporary_directory);

   saving_and_loading.set_num_profiles(1);
   saving_and_loading.set_start_style(AllegroFlare::SavingAndLoading::SavingAndLoading::StartStyle::GAME_START_STYLE_A);
   saving_and_loading.set_save_style(AllegroFlare::SavingAndLoading::SavingAndLoading::SaveStyle::GAME_SAVE_STYLE_4);
   saving_and_loading.set_load_style(AllegroFlare::SavingAndLoading::SavingAndLoading::LoadStyle::GAME_LOAD_STYLE_0);
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
   saving_and_loading.set_start_style(AllegroFlare::SavingAndLoading::SavingAndLoading::StartStyle::GAME_START_STYLE_A);
   saving_and_loading.set_save_style(AllegroFlare::SavingAndLoading::SavingAndLoading::SaveStyle::GAME_SAVE_STYLE_4);
   saving_and_loading.set_load_style(AllegroFlare::SavingAndLoading::SavingAndLoading::LoadStyle::GAME_LOAD_STYLE_0);
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
   saving_and_loading.set_start_style(AllegroFlare::SavingAndLoading::SavingAndLoading::StartStyle::GAME_START_STYLE_A);
   saving_and_loading.set_save_style(AllegroFlare::SavingAndLoading::SavingAndLoading::SaveStyle::GAME_SAVE_STYLE_4);
   saving_and_loading.set_load_style(AllegroFlare::SavingAndLoading::SavingAndLoading::LoadStyle::GAME_LOAD_STYLE_0);
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


TEST(AllegroFlare_SavingAndLoading_SavingAndLoadingTest,
   get_manual_save_slots__will_return_all_save_slots_of_the_type_SAVE_SLOT_TYPE_MANUAL_SAVE_belonging_to_a_profile)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");

   AllegroFlare::SavingAndLoading::SavingAndLoading saving_and_loading;
   saving_and_loading.set_data_folder_path(deployment_environment.get_data_folder_path() + "test_saves/");
   saving_and_loading.set_num_profiles(2);
   saving_and_loading.set_num_manual_save_slots(3);
   //saving_and_loading.set_num_autosave_save_slots(5);
   //saving_and_loading.set_num_quicksave_save_slots(7);
   saving_and_loading.set_start_style(AllegroFlare::SavingAndLoading::SavingAndLoading::StartStyle::GAME_START_STYLE_A);
   saving_and_loading.set_save_style(AllegroFlare::SavingAndLoading::SavingAndLoading::SaveStyle::GAME_SAVE_STYLE_4);
   saving_and_loading.set_load_style(AllegroFlare::SavingAndLoading::SavingAndLoading::LoadStyle::GAME_LOAD_STYLE_0);
   saving_and_loading.initialize();

   //saving_and_loading.create_save_file_directories_if_they_do_not_exist();
   //saving_and_loading.scan_for_existing_save_files_and_load_header_data();

   std::vector<AllegroFlare::SavingAndLoading::SaveSlot*> manual_save_slots =
      saving_and_loading.get_manual_save_slots(1);

   EXPECT_EQ(3, manual_save_slots.size());
   for (auto &save_slot : manual_save_slots)
   {
      ASSERT_NE(nullptr, save_slot);
      EXPECT_EQ(true, save_slot->is_manual_save());
      EXPECT_EQ(1, save_slot->get_profile_id());
   }
}


TEST(AllegroFlare_SavingAndLoading_SavingAndLoadingTest,
   save_to_manual_save_slot__will_save_the_content_to_the_expected_save_slot)
{
   std::string temporary_directory = AllegroFlare::Testing::TemporaryDirectoryCreator().create().string();
   std::cout << "NOTE: This test is saving to temporary directory: \"" + temporary_directory + "\"." << std::endl;

   AllegroFlare::SavingAndLoading::SavingAndLoading saving_and_loading(temporary_directory + "/");
   saving_and_loading.set_num_profiles(2);
   saving_and_loading.set_num_manual_save_slots(3);
   //saving_and_loading.set_num_autosave_save_slots(5);
   //saving_and_loading.set_num_quicksave_save_slots(7);
   saving_and_loading.set_start_style(AllegroFlare::SavingAndLoading::SavingAndLoading::StartStyle::GAME_START_STYLE_A);
   saving_and_loading.set_save_style(AllegroFlare::SavingAndLoading::SavingAndLoading::SaveStyle::GAME_SAVE_STYLE_4);
   saving_and_loading.set_load_style(AllegroFlare::SavingAndLoading::SavingAndLoading::LoadStyle::GAME_LOAD_STYLE_0);
   saving_and_loading.initialize();

   saving_and_loading.save_to_manual_save_slot(2, 1, "{\"foo\":\"bar\"}");

   // TODO: Check for existene of file, or other stubbed save behavior
}


TEST(AllegroFlare_SavingAndLoading_SavingAndLoadingTest,
   save_to_manual_save_slot__on_a_save_slot_that_is_outside_the_range__will_throw_an_error__1)
{
   std::string temporary_directory = AllegroFlare::Testing::TemporaryDirectoryCreator().create().string();
   std::cout << "NOTE: This test is saving to temporary directory: \"" + temporary_directory + "\"." << std::endl;

   AllegroFlare::SavingAndLoading::SavingAndLoading saving_and_loading(temporary_directory + "/");
   saving_and_loading.set_num_profiles(2);
   saving_and_loading.set_num_manual_save_slots(3);
   //saving_and_loading.set_num_autosave_save_slots(5);
   //saving_and_loading.set_num_quicksave_save_slots(7);
   saving_and_loading.set_start_style(AllegroFlare::SavingAndLoading::SavingAndLoading::StartStyle::GAME_START_STYLE_A);
   saving_and_loading.set_save_style(AllegroFlare::SavingAndLoading::SavingAndLoading::SaveStyle::GAME_SAVE_STYLE_4);
   saving_and_loading.set_load_style(AllegroFlare::SavingAndLoading::SavingAndLoading::LoadStyle::GAME_LOAD_STYLE_0);
   saving_and_loading.initialize();

   std::string expected_error_message =
      "[AllegroFlare::SavingAndLoading::SavingAndLoading::save_to_manual_save_slot]: error: "
      "guard \"(profile_id <= num_profiles)\" not met";
   EXPECT_THROW_WITH_MESSAGE(
      saving_and_loading.save_to_manual_save_slot(999, 123, "{}"),
      std::runtime_error,
      expected_error_message
   );
}


TEST(AllegroFlare_SavingAndLoading_SavingAndLoadingTest,
   save_to_manual_save_slot__on_a_save_slot_that_is_outside_the_range__will_throw_an_error__2)
{
   std::string temporary_directory = AllegroFlare::Testing::TemporaryDirectoryCreator().create().string();
   std::cout << "NOTE: This test is saving to temporary directory: \"" + temporary_directory + "\"." << std::endl;

   AllegroFlare::SavingAndLoading::SavingAndLoading saving_and_loading(temporary_directory + "/");
   saving_and_loading.set_num_profiles(1);
   saving_and_loading.set_num_manual_save_slots(1);
   //saving_and_loading.set_num_autosave_save_slots(5);
   //saving_and_loading.set_num_quicksave_save_slots(7);
   saving_and_loading.set_start_style(AllegroFlare::SavingAndLoading::SavingAndLoading::StartStyle::GAME_START_STYLE_A);
   saving_and_loading.set_save_style(AllegroFlare::SavingAndLoading::SavingAndLoading::SaveStyle::GAME_SAVE_STYLE_4);
   saving_and_loading.set_load_style(AllegroFlare::SavingAndLoading::SavingAndLoading::LoadStyle::GAME_LOAD_STYLE_0);
   saving_and_loading.initialize();

   std::string expected_error_message =
      "[AllegroFlare::SavingAndLoading::SavingAndLoading::save_to_manual_save_slot]: error: "
      "guard \"(save_slot_position <= num_manual_save_slots)\" not met";
   EXPECT_THROW_WITH_MESSAGE(
      saving_and_loading.save_to_manual_save_slot(1, 999, "{}"),
      std::runtime_error,
      expected_error_message
   );
}


TEST(AllegroFlare_SavingAndLoading_SavingAndLoadingTest,
   DISABLED____delete_header_and_content_files_and_clear_save_slot__will_delete_save_slot_data)
{
   // TODO
}


TEST(AllegroFlare_SavingAndLoading_SavingAndLoadingTest,
   DISABLED____delete_all_save_data__will_remove_all_existing_save_files_and_clear_save_slot_headers)
{
   // TODO
}


