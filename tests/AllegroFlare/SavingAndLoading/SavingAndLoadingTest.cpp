
#include <gtest/gtest.h>

#include <AllegroFlare/SavingAndLoading/SavingAndLoading.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>


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
   saving_and_loading.set_num_auto_save_slots(5);
   saving_and_loading.set_num_quicksave_save_slots(7);
   saving_and_loading.initialize();

   EXPECT_EQ(30, saving_and_loading.num_save_slots());
}


