#pragma once


#include <AllegroFlare/YAMLValidator.hpp>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace AI
   {
      class PromptTemplateYAMLLoader : public AllegroFlare::YAMLValidator
      {
      public:
         static constexpr char* PROMPT_NODE_KEY = (char*)"prompt";

      private:

      protected:


      public:
         PromptTemplateYAMLLoader();
         ~PromptTemplateYAMLLoader();

         std::string load_yaml(std::string yaml_as_string="[unset-yaml_as_string]", std::vector<std::pair<std::string, std::string>> template_arguments={});
      };
   }
}



