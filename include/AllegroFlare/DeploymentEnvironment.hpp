#pragma once


#include <string>


namespace AllegroFlare
{
   class DeploymentEnvironment
   {
   public:
      static constexpr char* ENVIRONMENT_UNDEF = (char*)"undefined";
      static constexpr char* ENVIRONMENT_TEST = (char*)"test";
      static constexpr char* ENVIRONMENT_DEVELOPMENT = (char*)"development";
      static constexpr char* ENVIRONMENT_DEMO = (char*)"demo";
      static constexpr char* ENVIRONMENT_PRODUCTION = (char*)"production";

   private:
      std::string environment;
      std::string current_working_directory_before_setup;
      bool working_directory_has_been_setup;

   protected:


   public:
      DeploymentEnvironment(std::string environment=ENVIRONMENT_UNDEF, std::string current_working_directory_before_setup="[unset-current_working_directory_before_setup]");
      ~DeploymentEnvironment();

      std::string get_environment() const;
      std::string get_current_working_directory_before_setup() const;
      bool get_working_directory_has_been_setup() const;
      void set_environment(std::string environment=ENVIRONMENT_UNDEF);
      bool is_undefined() const;
      bool is_production() const;
      bool is_test() const;
      bool is_demo() const;
      bool is_development() const;
      bool environment_should_set_path_to_resources_path() const;
      void setup_current_working_directory();
      void restore_initial_working_directory();
      bool _is_valid(std::string environment="[unset-environment]");
      bool is_valid();
      bool is_invalid();
      std::string get_data_folder_path();
   };
}



