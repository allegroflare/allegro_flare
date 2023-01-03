#pragma once


#include <string>


namespace AllegroFlare
{
   class DeploymentEnvironment
   {
   public:
      static constexpr char* ENVIRONMENT_UNDEF = "undefined";
      static constexpr char* ENVIRONMENT_TEST = "test";
      static constexpr char* ENVIRONMENT_DEVELOPMENT = "development";
      static constexpr char* ENVIRONMENT_PRODUCTION = "production";

   private:
      std::string environment;

   protected:


   public:
      DeploymentEnvironment(std::string environment=ENVIRONMENT_UNDEF);
      ~DeploymentEnvironment();

      std::string get_environment() const;
      void set_environment(std::string environment=ENVIRONMENT_UNDEF);
      bool is_production();
      bool is_undefined();
      bool is_test();
      bool is_development();
      static bool is_valid(std::string environment=ENVIRONMENT_UNDEF);
      static bool is_invalid(std::string environment=ENVIRONMENT_UNDEF);
   };
}



