
#include <gtest/gtest.h>

#include <AllegroFlare/SavingAndLoading/SaveSlot.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>
#include <AllegroFlare/Testing/TemporaryDirectoryCreator.hpp>


TEST(AllegroFlare_SavingAndLoading_SaveSlotTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SavingAndLoading::SaveSlot save_slot;
}


TEST(AllegroFlare_SavingAndLoading_SaveSlotTest,
   build_content_basename__will_produce_the_correct_basename_for_the_save_content_file)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string data_folder_path = deployment_environment.get_data_folder_path();
   AllegroFlare::SavingAndLoading::SaveSlot save_slot = AllegroFlare::SavingAndLoading::SaveSlot::construct(
      data_folder_path, 2, 32, AllegroFlare::SavingAndLoading::SaveSlot::SaveSlotType::SAVE_SLOT_TYPE_MANUAL_SAVE
   );
   std::string expected_save_slot_content_basename = "profile_002-manual_save-position_032.sav";
   std::string actual_save_slot_content_basename = save_slot.build_content_basename();
   EXPECT_EQ(expected_save_slot_content_basename, actual_save_slot_content_basename);
}


TEST(AllegroFlare_SavingAndLoading_SaveSlotTest,
   build_header_basename__will_produce_the_correct_basename_for_the_save_header_file)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string data_folder_path = deployment_environment.get_data_folder_path();
   AllegroFlare::SavingAndLoading::SaveSlot save_slot = AllegroFlare::SavingAndLoading::SaveSlot::construct(
      data_folder_path, 2, 32, AllegroFlare::SavingAndLoading::SaveSlot::SaveSlotType::SAVE_SLOT_TYPE_AUTO_SAVE
   );
   std::string expected_save_slot_header_basename = "profile_002-autosave-position_032.header.sav";
   std::string actual_save_slot_header_basename = save_slot.build_header_basename();
   EXPECT_EQ(expected_save_slot_header_basename, actual_save_slot_header_basename);
}


TEST(AllegroFlare_SavingAndLoading_SaveSlotTest,
   save_to_slot__will_save_the_header_file_and_content_file_with_the_expected_data)
{
   std::string temporary_directory = AllegroFlare::Testing::TemporaryDirectoryCreator().create().string();
   std::string data_folder_path = temporary_directory + "/";
   std::cout << "Data folder path: " << data_folder_path << std::endl;
   AllegroFlare::SavingAndLoading::SaveSlot save_slot = AllegroFlare::SavingAndLoading::SaveSlot::construct(
      data_folder_path, 2, 7, AllegroFlare::SavingAndLoading::SaveSlot::SaveSlotType::SAVE_SLOT_TYPE_AUTO_SAVE
   );

   std::cout << "Header file name: " << save_slot.build_full_path_to_content_file() << std::endl;

   save_slot.save_to_slot();

   EXPECT_EQ(true, std::filesystem::exists(save_slot.build_full_path_to_header_file()));
   EXPECT_EQ(true, std::filesystem::exists(save_slot.build_full_path_to_content_file()));
   //std::string expected_save_slot_header_basename = "profile_002-autosave-position_032.header.sav";
   //std::string actual_save_slot_header_basename = save_slot.build_header_basename();
   //EXPECT_EQ(expected_save_slot_header_basename, actual_save_slot_header_basename);
}


TEST(AllegroFlare_SavingAndLoading_SaveSlotTest,
   delete_header_and_content_files_and_clear__will_remove_the_existing_files)
{
   std::string temporary_directory = AllegroFlare::Testing::TemporaryDirectoryCreator().create().string();
   std::string data_folder_path = temporary_directory + "/";
   std::cout << "Data folder path: " << data_folder_path << std::endl;
   AllegroFlare::SavingAndLoading::SaveSlot save_slot = AllegroFlare::SavingAndLoading::SaveSlot::construct(
      data_folder_path, 2, 7, AllegroFlare::SavingAndLoading::SaveSlot::SaveSlotType::SAVE_SLOT_TYPE_AUTO_SAVE
   );

   std::cout << "Header file name: " << save_slot.build_full_path_to_content_file() << std::endl;

   save_slot.save_to_slot();

   ASSERT_EQ(true, std::filesystem::exists(save_slot.build_full_path_to_header_file()));
   ASSERT_EQ(true, std::filesystem::exists(save_slot.build_full_path_to_content_file()));

   save_slot.delete_header_and_content_files_and_clear();
   
   EXPECT_EQ(false, std::filesystem::exists(save_slot.build_full_path_to_header_file()));
   EXPECT_EQ(false, std::filesystem::exists(save_slot.build_full_path_to_content_file()));
}


/*
   std::ofstream file;
   file.open(filename.c_str());
   if (!file.is_open()) return false;
   file << contents.c_str();
   file.close();
   return true;
*/


