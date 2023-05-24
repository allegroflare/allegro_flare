

#include <AllegroFlare/AI/PromptTemplateYAMLLoader.hpp>

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


std::string PromptTemplateYAMLLoader::load_yaml(std::string yaml_as_string)
{
   if (!((!yaml_as_string.empty())))
   {
      std::stringstream error_message;
      error_message << "[PromptTemplateYAMLLoader::load_yaml]: error: guard \"(!yaml_as_string.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PromptTemplateYAMLLoader::load_yaml: error: guard \"(!yaml_as_string.empty())\" not met");
   }
   std::string result;
   YAML::Node root_node = YAML::Load(yaml_as_string);

   validate_presence_of_key(root_node, TEXT_NODE_KEY);

   return result;
}


} // namespace AI
} // namespace AllegroFlare


