
#include <gtest/gtest.h>

#include <AllegroFlare/SavingAndLoading/SaveSlot.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>


TEST(AllegroFlare_SavingAndLoading_SaveSlotTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SavingAndLoading::SaveSlot save_slot;
}


TEST(AllegroFlare_SavingAndLoading_SaveSlotTest,
   build_content_filename__will_produce_the_correct_filename_for_the_save_content_file)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   AllegroFlare::SavingAndLoading::SaveSlot save_slot = AllegroFlare::SavingAndLoading::SaveSlot::construct(
      deployment_environment.get_data_folder_path(),
      2,
      32,
      AllegroFlare::SavingAndLoading::SaveSlot::SaveSlotType::SAVE_SLOT_TYPE_MANUAL_SAVE
   );
   //AllegroFlare::SavingAndLoading::SaveSlot save_slot = AllegroFlare::SavingAndLoading::SaveSlot::construct(
      //2, 32, AllegroFlare::SavingAndLoading::SaveSlot::SaveSlotType::SAVE_SLOT_TYPE_MANUAL_SAVE
   //);
   std::string expected_save_slot_content_filename = "profile_002-manual_save-position_032.sav";
   std::string actual_save_slot_content_filename = save_slot.build_content_filename();
   EXPECT_EQ(expected_save_slot_content_filename, actual_save_slot_content_filename);
}


TEST(AllegroFlare_SavingAndLoading_SaveSlotTest,
   build_header_filename__will_produce_the_correct_filename_for_the_save_header_file)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   AllegroFlare::SavingAndLoading::SaveSlot save_slot = AllegroFlare::SavingAndLoading::SaveSlot::construct(
      deployment_environment.get_data_folder_path(),
      2,
      32,
      AllegroFlare::SavingAndLoading::SaveSlot::SaveSlotType::SAVE_SLOT_TYPE_AUTO_SAVE
   );
   std::string expected_save_slot_header_filename = "profile_002-autosave-position_032.header.sav";
   std::string actual_save_slot_header_filename = save_slot.build_header_filename();
   EXPECT_EQ(expected_save_slot_header_filename, actual_save_slot_header_filename);
}


