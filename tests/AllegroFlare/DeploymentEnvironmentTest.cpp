
#include <gtest/gtest.h>

#include <AllegroFlare/DeploymentEnvironment.hpp>


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


