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

   protected:


   public:
      DeploymentEnvironment(std::string environment=ENVIRONMENT_UNDEF);
      ~DeploymentEnvironment();

      std::string get_environment() const;
      void set_environment(std::string environment=ENVIRONMENT_UNDEF);
      bool is_undefined();
      bool is_production();
      bool is_test();
      bool is_demo();
      bool is_development();
      bool environment_should_set_path_to_resources_path();
      void setup_current_working_directory();
      bool _is_valid(std::string environment="[unset-environment]");
      bool is_valid();
      bool is_invalid();
      std::string get_data_folder_path();
   };
}



