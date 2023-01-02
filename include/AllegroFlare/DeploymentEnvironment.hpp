#pragma once


#include <string>


namespace AllegroFlare
{
   class DeploymentEnvironment
   {
   public:
      static constexpr char* ENVIRONMENT_TEST = "test";
      static constexpr char* ENVIRONMENT_DEVELOPMENT = "development";
      static constexpr char* ENVIRONMENT_PRODUCTION = "production";

   private:
      std::string environment;

   protected:


   public:
      DeploymentEnvironment(std::string environment=ENVIRONMENT_PRODUCTION);
      ~DeploymentEnvironment();

      std::string get_environment() const;
      bool is_production();
      bool is_test();
      bool is_development();
   };
}



