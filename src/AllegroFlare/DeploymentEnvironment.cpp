

#include <AllegroFlare/DeploymentEnvironment.hpp>

#include <AllegroFlare/Logger.hpp>
#include <allegro5/allegro.h>
#include <filesystem>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


DeploymentEnvironment::DeploymentEnvironment(std::string environment, std::string current_working_directory_before_setup)
   : environment(environment)
   , current_working_directory_before_setup(current_working_directory_before_setup)
   , working_directory_has_been_setup(false)
{
}


DeploymentEnvironment::~DeploymentEnvironment()
{
}


std::string DeploymentEnvironment::get_environment() const
{
   return environment;
}


std::string DeploymentEnvironment::get_current_working_directory_before_setup() const
{
   return current_working_directory_before_setup;
}


bool DeploymentEnvironment::get_working_directory_has_been_setup() const
{
   return working_directory_has_been_setup;
}


void DeploymentEnvironment::set_environment(std::string environment)
{
   if (!(_is_valid(environment)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DeploymentEnvironment::set_environment]: error: guard \"_is_valid(environment)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DeploymentEnvironment::set_environment]: error: guard \"_is_valid(environment)\" not met");
   }
   // TODO: If an invalid argument is passed, include the argument value in an error message
   this->environment = environment;
   return;
}

bool DeploymentEnvironment::is_undefined() const
{
   return environment == ENVIRONMENT_UNDEF;
}

bool DeploymentEnvironment::is_production() const
{
   return environment == ENVIRONMENT_PRODUCTION;
}

bool DeploymentEnvironment::is_test() const
{
   return environment == ENVIRONMENT_TEST;
}

bool DeploymentEnvironment::is_demo() const
{
   return environment == ENVIRONMENT_DEMO;
}

bool DeploymentEnvironment::is_development() const
{
   return environment == ENVIRONMENT_DEVELOPMENT;
}

bool DeploymentEnvironment::environment_should_set_path_to_resources_path() const
{
   return environment == ENVIRONMENT_PRODUCTION;
}

void DeploymentEnvironment::setup_current_working_directory()
{
   if (!((!working_directory_has_been_setup)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DeploymentEnvironment::setup_current_working_directory]: error: guard \"(!working_directory_has_been_setup)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DeploymentEnvironment::setup_current_working_directory]: error: guard \"(!working_directory_has_been_setup)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DeploymentEnvironment::setup_current_working_directory]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DeploymentEnvironment::setup_current_working_directory]: error: guard \"al_is_system_installed()\" not met");
   }
   if (is_undefined())
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DeploymentEnvironment::setup_current_working_directory",
         "The current deployment environment has not been defined. You must define one before calling this function."
      );
   }

   if (is_invalid())
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DeploymentEnvironment::setup_current_working_directory",
         "The current deployment environment is invalid. You must define a valid environment before calling "
            "this function."
      );
   }

   current_working_directory_before_setup = std::filesystem::current_path().string();

   if (environment_should_set_path_to_resources_path()) // NOTE: this happens in PRODUCTION
   {
      ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
      al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
      al_destroy_path(resource_path);
   }
   else
   {
      // Do nothing. Presume that the executable (which is assumed to be a test executable) is being run from the
      // root folder of the project, otherwise there will be undefined behavior.
   }

   AllegroFlare::Logger::info_from(
      "AllegroFlare::DeploymentEnvironment::setup",
      "\n    - Deployment environment is \"" + get_environment() + "\". "
         "\n    - Initial working directory: \"" + current_working_directory_before_setup + "\". "
         "\n    - Current working directory: \"" + std::filesystem::current_path().string() + "\"."
         "\n    - Data folder path: \"" + get_data_folder_path() + "\"."
   );

   working_directory_has_been_setup = true;

   return;
}

void DeploymentEnvironment::restore_initial_working_directory()
{
   if (working_directory_has_been_setup)
   {
      al_change_directory(current_working_directory_before_setup.c_str());
      working_directory_has_been_setup = false;
   }
   return;
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
      error_message << "[AllegroFlare::DeploymentEnvironment::get_data_folder_path]: error: guard \"is_valid()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DeploymentEnvironment::get_data_folder_path]: error: guard \"is_valid()\" not met");
   }
   if (environment == ENVIRONMENT_TEST)
   {
      return "tests/fixtures/";
   }
   else if (environment == ENVIRONMENT_DEVELOPMENT || environment == ENVIRONMENT_DEMO)
   {
      return "bin/data/";
   }
   else if (environment == ENVIRONMENT_PRODUCTION)
   {
      // NOTE: With the production environment, it's expected to have the executable set the path. The data folder
      // will be the "./data" folder that is relative to that.
      return "data/";
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


