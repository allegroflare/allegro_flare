

#include <AllegroFlare/AI/PromptTemplateYAMLLoader.hpp>

#include <AllegroFlare/AI/PromptTemplate.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace AI
{


PromptTemplateYAMLLoader::PromptTemplateYAMLLoader()
   : AllegroFlare::YAMLValidator()
{
}


PromptTemplateYAMLLoader::~PromptTemplateYAMLLoader()
{
}


std::string PromptTemplateYAMLLoader::load_yaml(std::string yaml_as_string, std::vector<std::pair<std::string, std::string>> template_arguments)
{
   if (!((!yaml_as_string.empty())))
   {
      std::stringstream error_message;
      error_message << "[PromptTemplateYAMLLoader::load_yaml]: error: guard \"(!yaml_as_string.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PromptTemplateYAMLLoader::load_yaml: error: guard \"(!yaml_as_string.empty())\" not met");
   }
   std::string result;

   // Parse our string to a YAML object
   YAML::Node root_node = YAML::Load(yaml_as_string);

   // Prepare result variables
   std::string template_text = "[unset-template_text]";
   std::vector<std::pair<std::string, std::string>> template_insertion_variables;

   // Extract the variables from the YAML
   validate_presence_of_key(root_node, PROMPT_NODE_KEY);
   //validate_node_type(root_node, PROMPT_NODE_KEY, );
   template_text = root_node[std::string(PROMPT_NODE_KEY)].as<std::string>();
   //template_text = root_node[TEXT_NODE_KEY];
   //validate_presence_of_key(root_node, TEXT_NODE_KEY);
   //validate_node_type(root_node[TEXT_NODE_KEY]


   // Create the template object and fill it in
   AllegroFlare::AI::PromptTemplate prompt_template;
   prompt_template.set_template_content(template_text);
   prompt_template.set_insertion_variables(template_insertion_variables);

   // Build the finalized prompt
   result = prompt_template.generate_content();

   return result;
}


} // namespace AI
} // namespace AllegroFlare


