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
         static constexpr char* PARAMETERS_NODE_KEY = (char*)"parameters";
         static constexpr char* PARAMETER_NAME_NODE_KEY = (char*)"name";

      private:

      protected:


      public:
         PromptTemplateYAMLLoader();
         ~PromptTemplateYAMLLoader();

         std::string load_yaml(std::string yaml_as_string="[unset-yaml_as_string]", std::vector<std::pair<std::string, std::string>> template_arguments={});
         static std::vector<std::pair<std::string, std::string>> assemble_parameter_arguments(std::vector<std::string> template_parameters={}, std::vector<std::pair<std::string, std::string>> template_arguments={});
      };
   }
}



