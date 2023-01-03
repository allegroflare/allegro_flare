

#include <AllegroFlare/DeploymentEnvironment.hpp>

#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


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


void DeploymentEnvironment::set_environment(std::string environment)
{
   if (!(is_valid(environment)))
   {
      std::stringstream error_message;
      error_message << "[DeploymentEnvironment::set_environment]: error: guard \"is_valid(environment)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DeploymentEnvironment::set_environment: error: guard \"is_valid(environment)\" not met");
   }
   // TODO: If an invalid argument is passed, include the argument value in an error message
   this->environment = environment;
   return;
}

bool DeploymentEnvironment::is_production()
{
   return environment == ENVIRONMENT_PRODUCTION;
}

bool DeploymentEnvironment::is_undefined()
{
   return environment == ENVIRONMENT_UNDEF;
}

bool DeploymentEnvironment::is_test()
{
   return environment == ENVIRONMENT_TEST;
}

bool DeploymentEnvironment::is_development()
{
   return environment == ENVIRONMENT_DEVELOPMENT;
}

bool DeploymentEnvironment::is_valid(std::string environment)
{
   static std::set<std::string> valid_environments = {
      ENVIRONMENT_PRODUCTION,
      ENVIRONMENT_TEST,
      ENVIRONMENT_DEVELOPMENT,
   };
   // NOTE: Should consider an update to -std=c++20 which has `contains` for a std::set
   // https://en.cppreference.com/w/cpp/container/set/contains

   return valid_environments.find(environment) != valid_environments.end();
}

bool DeploymentEnvironment::is_invalid(std::string environment)
{
   return !is_valid(environment);
}


} // namespace AllegroFlare


