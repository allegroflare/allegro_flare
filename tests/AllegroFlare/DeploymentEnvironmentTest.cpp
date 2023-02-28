
#include <gtest/gtest.h>

#include <AllegroFlare/DeploymentEnvironment.hpp>
#include <allegro5/allegro.h> // for al_init(), al_uninstall_system()

#include <filesystem>


TEST(AllegroFlare_DeploymentEnvironmentTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DeploymentEnvironment deployment_environment;
}


TEST(AllegroFlare_DeploymentEnvironmentTest, is_production__returns_true_when_the_environment_is_production)
{
   auto ENVIRONMENT_PRODUCTION = AllegroFlare::DeploymentEnvironment::ENVIRONMENT_PRODUCTION;
   AllegroFlare::DeploymentEnvironment deployment_environment(ENVIRONMENT_PRODUCTION);
   EXPECT_EQ(true, deployment_environment.is_production());
}


TEST(AllegroFlare_DeploymentEnvironmentTest, is_test__returns_true_when_the_environment_is_test)
{
   auto ENVIRONMENT_TEST = AllegroFlare::DeploymentEnvironment::ENVIRONMENT_TEST;
   AllegroFlare::DeploymentEnvironment deployment_environment(ENVIRONMENT_TEST);
   EXPECT_EQ(true, deployment_environment.is_test());
}


TEST(AllegroFlare_DeploymentEnvironmentTest, is_development__returns_true_when_the_environment_is_development)
{
   auto ENVIRONMENT_DEVELOPMENT = AllegroFlare::DeploymentEnvironment::ENVIRONMENT_DEVELOPMENT;
   AllegroFlare::DeploymentEnvironment deployment_environment(ENVIRONMENT_DEVELOPMENT);
   EXPECT_EQ(true, deployment_environment.is_development());
}


TEST(AllegroFlare_DeploymentEnvironmentTest,
   is_valid__returns_true_when_the_environment_is_one_of_the_valid_environments)
{
   auto ENVIRONMENT_DEVELOPMENT = AllegroFlare::DeploymentEnvironment::ENVIRONMENT_DEVELOPMENT;
   AllegroFlare::DeploymentEnvironment deployment_environment(ENVIRONMENT_DEVELOPMENT);
   EXPECT_EQ(true, deployment_environment.is_valid());
}


TEST(AllegroFlare_DeploymentEnvironmentTest,
   environment_should_set_path_to_resources_path__returns_true_when_the_environment_path_is_expected_to_be_rebased)
{
   auto ENVIRONMENT_PRODUCTION = AllegroFlare::DeploymentEnvironment::ENVIRONMENT_PRODUCTION;
   AllegroFlare::DeploymentEnvironment deployment_environment(ENVIRONMENT_PRODUCTION);
   EXPECT_EQ(true, deployment_environment.environment_should_set_path_to_resources_path());
}


TEST(AllegroFlare_DeploymentEnvironmentTest,
   setup_current_working_directory__will_set_the_working_directory_to_the_expected_value)
{
   std::string working_directory_at_start_of_test = std::filesystem::current_path().string();
   al_init();

   auto ENVIRONMENT_PRODUCTION = AllegroFlare::DeploymentEnvironment::ENVIRONMENT_PRODUCTION;
   AllegroFlare::DeploymentEnvironment deployment_environment(ENVIRONMENT_PRODUCTION);
   deployment_environment.setup_current_working_directory();
   std::string current_path = std::filesystem::current_path().string();
   EXPECT_EQ("/Users/markoates/Repos/allegro_flare/bin/tests/AllegroFlare", current_path);
   deployment_environment.restore_initial_working_directory();

   al_uninstall_system();
   std::string working_directory_at_end_of_test = std::filesystem::current_path().string();
   ASSERT_EQ(
      working_directory_at_start_of_test,
      working_directory_at_end_of_test
   ) << "This failure could indicate a leaky test.";
}


