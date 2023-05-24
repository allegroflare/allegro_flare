#pragma once


#include <AllegroFlare/YAMLValidator.hpp>
#include <string>


namespace AllegroFlare
{
   namespace AI
   {
      class PromptTemplateYAMLLoader : public AllegroFlare::YAMLValidator
      {
      public:
         static constexpr char* TEXT_NODE_KEY = (char*)"go_to_node";

      private:

      protected:


      public:
         PromptTemplateYAMLLoader();
         ~PromptTemplateYAMLLoader();

         std::string load_yaml(std::string yaml_as_string="[unset-yaml_as_string]");
      };
   }
}



