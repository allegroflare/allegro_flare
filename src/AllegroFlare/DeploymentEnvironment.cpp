

#include <AllegroFlare/DeploymentEnvironment.hpp>

#include <AllegroFlare/Logger.hpp>
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
   if (!(_is_valid(environment)))
   {
      std::stringstream error_message;
      error_message << "[DeploymentEnvironment::set_environment]: error: guard \"_is_valid(environment)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DeploymentEnvironment::set_environment: error: guard \"_is_valid(environment)\" not met");
   }
   // TODO: If an invalid argument is passed, include the argument value in an error message
   this->environment = environment;
   return;
}

bool DeploymentEnvironment::is_undefined()
{
   return environment == ENVIRONMENT_UNDEF;
}

bool DeploymentEnvironment::is_production()
{
   return environment == ENVIRONMENT_PRODUCTION;
}

bool DeploymentEnvironment::is_test()
{
   return environment == ENVIRONMENT_TEST;
}

bool DeploymentEnvironment::is_demo()
{
   return environment == ENVIRONMENT_DEMO;
}

bool DeploymentEnvironment::is_development()
{
   return environment == ENVIRONMENT_DEVELOPMENT;
}

bool DeploymentEnvironment::environment_should_set_path_to_resources_path()
{
   return environment == ENVIRONMENT_PRODUCTION;
}

bool DeploymentEnvironment::_is_valid(std::string environment)
{
   // TODO: Require a param, and do not have a default
   static std::set<std::string> valid_environments = {
      ENVIRONMENT_PRODUCTION,
      ENVIRONMENT_TEST,
      ENVIRONMENT_DEMO,
      ENVIRONMENT_DEVELOPMENT,
   };
   // NOTE: Should consider an update to -std=c++20 eventually, which has `contains` for a std::set
   // https://en.cppreference.com/w/cpp/container/set/contains

   // DEBUG:

   return valid_environments.find(environment) != valid_environments.end();
}

bool DeploymentEnvironment::is_valid()
{
   static std::set<std::string> valid_environments = {
      ENVIRONMENT_PRODUCTION,
      ENVIRONMENT_TEST,
      ENVIRONMENT_DEMO,
      ENVIRONMENT_DEVELOPMENT,
   };
   // NOTE: Should consider an update to -std=c++20 eventually, which has `contains` for a std::set
   // https://en.cppreference.com/w/cpp/container/set/contains

   // DEBUG:

   return valid_environments.find(environment) != valid_environments.end();
}

bool DeploymentEnvironment::is_invalid()
{
   return !is_valid();
}

std::string DeploymentEnvironment::get_data_folder_path()
{
   if (!(is_valid()))
   {
      std::stringstream error_message;
      error_message << "[DeploymentEnvironment::get_data_folder_path]: error: guard \"is_valid()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DeploymentEnvironment::get_data_folder_path: error: guard \"is_valid()\" not met");
   }
   if (environment == ENVIRONMENT_TEST)
   {
      return "./tests/fixtures/";
   }
   else if (environment == ENVIRONMENT_DEVELOPMENT || environment == ENVIRONMENT_DEMO)
   {
      return "./bin/data/";
   }
   else if (environment == ENVIRONMENT_PRODUCTION)
   {
      // NOTE: With the production environment, it's expected to have the executable set the path. The data folder
      // will be the "./data" folder that is relative to that.
      return "./data/";
   }
   else
   {
      AllegroFlare::Logger::throw_error("AllegroFlare::DeploymentEnvironment::get_base_data_path",
            "Unexpected error occurred where a path was requested on an invalid deployment environment."
            + AllegroFlare::Logger::build_unhandled_case_message(environment)
         );
   }
   return "";
}


} // namespace AllegroFlare


