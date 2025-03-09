
#include <gtest/gtest.h>

#include <AllegroFlare/SavingAndLoading/SaveSlot.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>


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


