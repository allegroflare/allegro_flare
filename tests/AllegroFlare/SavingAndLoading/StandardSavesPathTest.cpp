
#include <gtest/gtest.h>

#include <AllegroFlare/SavingAndLoading/StandardSavesPath.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>


TEST(AllegroFlare_SavingAndLoading_StandardSavesPathTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SavingAndLoading::StandardSavesPath standard_saves_path;
}


TEST(AllegroFlare_SavingAndLoading_StandardSavesPathTest,
   build_standard_path__will_return_the_full_path_to_the_standard_saves_folder)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string actual_path = AllegroFlare::SavingAndLoading::StandardSavesPath::build_standard_path(
      deployment_environment.get_data_folder_path()
   );
   expected_path = "..";
   EXPECT_EQ(expected_path, actual_path);
}



