

#include <AllegroFlare/DeploymentEnvironment.hpp>




namespace AllegroFlare
{


DeploymentEnvironment::DeploymentEnvironment(std::string environment)
   : environment(environment)
{
}


DeploymentEnvironment::~DeploymentEnvironment()
{
}


std::string DeploymentEnvironment::get_environment() const
{
   return environment;
}


bool DeploymentEnvironment::is_production()
{
   return environment == ENVIRONMENT_PRODUCTION;
}

bool DeploymentEnvironment::is_test()
{
   return environment == ENVIRONMENT_TEST;
}

bool DeploymentEnvironment::is_development()
{
   return environment == ENVIRONMENT_DEVELOPMENT;
}


} // namespace AllegroFlare


