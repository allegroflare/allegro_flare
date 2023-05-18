

#include <AllegroFlare/DialogTree/YAMLLoader.hpp>

#include <AllegroFlare/DialogTree/NodeOptions/Base.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>


namespace AllegroFlare
{
namespace DialogTree
{


YAMLLoader::YAMLLoader()
   : AllegroFlare::YAMLValidator()
{
}


YAMLLoader::~YAMLLoader()
{
}


AllegroFlare::DialogTree::Node* YAMLLoader::load(std::string yaml_as_string)
{
   YAML::Node root_node = YAML::Load(yaml_as_string);
   AllegroFlare::DialogTree::Node *result = new AllegroFlare::DialogTree::Node;

   // Validate and extract the speaker
   validate_presence_of_key(root_node, SPEAKER_KEY);
   validate_node_type(root_node, SPEAKER_KEY, YAML::NodeType::Scalar);
   std::string speaker = root_node[std::string(SPEAKER_KEY)].as<std::string>();
   result->set_speaker(speaker);

   // Validate and extract the pages
   validate_presence_of_key(root_node, PAGES_KEY);
   validate_node_type(root_node, PAGES_KEY, YAML::NodeType::Sequence);
   YAML::Node pages_node = root_node[std::string(PAGES_KEY)];
   std::vector<std::string> pages_vector;
   for (const auto& node : pages_node)
   {
      if (node.IsScalar())
      {
         pages_vector.push_back(node.as<std::string>());
      }
      else
      {
         // TODO: Improve this error message
         // TODO: Test this error path
         AllegroFlare::Logger::throw_error("here", "pages node contains a non-scalar element");
      }
   }
   // TODO: Validate content of pages vector
   result->set_pages(pages_vector);

   // Validate and extract the options
   // TODO: "options" node is optional
   validate_presence_of_key(root_node, OPTIONS_KEY);
   validate_node_type(root_node, OPTIONS_KEY, YAML::NodeType::Sequence);
   YAML::Node options_node = root_node[std::string(OPTIONS_KEY)];
   std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> options_vector;
   for (const auto& node : options_node)
   {
      std::string result_option_text = "[unset-result_text]";
      std::string result_option_type = "[unset-result_option_type]";
      AllegroFlare::DialogTree::NodeOptions::Base* result_option = nullptr;

      // Parse out option->text
      // TODO: Improve this error message
      validate_presence_of_key(node, TEXT_KEY);
      validate_node_type(node, TEXT_KEY, YAML::NodeType::Scalar);
      result_option_text = node[std::string(TEXT_KEY)].as<std::string>();

      // TODO: Parse out option->node type
      validate_presence_of_key(node, TYPE_KEY);
      validate_node_type(node, TYPE_KEY, YAML::NodeType::Scalar);
      std::string result_option_type_str = node[std::string(TYPE_KEY)].as<std::string>();
      YAML::Node result_option_data_node = node[std::string(DATA_KEY)];

      result_option = parse_and_create_result_option(result_option_type_str, &result_option_data_node);

      options_vector.push_back(std::make_pair(result_option_text, result_option));
   }
   result->set_options(options_vector);

   // Return our result
   return result;
}

AllegroFlare::DialogTree::NodeOptions::Base* YAMLLoader::parse_and_create_result_option(std::string type, YAML::Node* data_node_ptr)
{
   if (!(data_node_ptr))
   {
      std::stringstream error_message;
      error_message << "[YAMLLoader::parse_and_create_result_option]: error: guard \"data_node_ptr\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("YAMLLoader::parse_and_create_result_option: error: guard \"data_node_ptr\" not met");
   }
   AllegroFlare::DialogTree::NodeOptions::Base* result = nullptr;
   if (type == OPTION_TYPE_EXIT_DIALOG_KEY)
   {
      AllegroFlare::DialogTree::NodeOptions::ExitDialog* exit_dialog_result =
         new AllegroFlare::DialogTree::NodeOptions::ExitDialog;
      result = exit_dialog_result;
   }
   else if (type == OPTION_TYPE_NODE_KEY)
   {
      // TODO: Add a NodeOptions::Node type
      //AllegroFlare::DialogTree::NodeOptions::Node* node_result = new AllegroFlare::DialogTree::NodeOptions::Node;
      //result = node_result;
   }
   else
   {
      // NOTE: Option type is unsupported
      // TODO: Throw on unknown type
   }
   return result;
}


} // namespace DialogTree
} // namespace AllegroFlare


