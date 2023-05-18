

#include <AllegroFlare/DialogTree/YAMLLoader.hpp>

#include <AllegroFlare/DialogTree/NodeOptions/Base.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
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
   , node_bank({})
   , loaded(false)
{
}


YAMLLoader::~YAMLLoader()
{
}


void YAMLLoader::load(std::string yaml_as_string)
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[YAMLLoader::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("YAMLLoader::load: error: guard \"(!loaded)\" not met");
   }
   AllegroFlare::DialogTree::NodeBank result;
   YAML::Node root_node = YAML::Load(yaml_as_string);

   // Validate that root_node is a sequence
   if (!root_node.IsSequence())
   {
      // TODO: Improve this error message
      // TODO: Test this error path
      AllegroFlare::Logger::throw_error("here", "Expecting this node to be of type scalar.");
   }

   // TODO: Traverse the nodes, load as nodes
   for (const auto& node : root_node)
   {
      YAML::Node hack_node_copy = node;
      std::pair<std::string, AllegroFlare::DialogTree::Node*> created_node_info =
         parse_and_create_node(&hack_node_copy);

      std::string created_node_name = created_node_info.first;
      AllegroFlare::DialogTree::Node* created_node = created_node_info.second;

      //TODO: Check if node_exists_by_name, throw if already exists

      node_bank.add_node(created_node_name, created_node);
   }

   return;
}

std::pair<std::string, AllegroFlare::DialogTree::Node*> YAMLLoader::parse_and_create_node(YAML::Node* node_ptr)
{
   YAML::Node &root_node = *node_ptr; // TODO: Rename "root_node" to "node"
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

   // Return the result
   return { "unnamed-node", result };
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

   std::map<std::string, std::function<void()>> result_options_map = {
      { OPTION_TYPE_EXIT_DIALOG_KEY, [this, &result]() mutable {
         result = parse_and_create_ExitDialog_option();
      }},
      { OPTION_TYPE_GO_TO_NODE_KEY, [this, &result, data_node_ptr](){
         result = parse_and_create_GoToNode_option(data_node_ptr);
      }},
      { OPTION_TYPE_NODE_KEY, [this, &result, data_node_ptr](){
         // NOTE: For now, option nodes do not have names. "name" is reserved for nodes on the root
         result = parse_and_create_Node_option(data_node_ptr);
      }},
   };

   // Locate and call the function to handle the item
   if (result_options_map.count(type) == 0)
   {
      // Item not found
      std::stringstream error_message;
      error_message << "[YamlLoader::parse_and_create_result_option]: error: Cannot create an option of a type \""
                    << type << "\". A declaration to handle that type does not exist.";
      throw std::runtime_error(error_message.str());
   }
   else
   {
      // Call the item
      result_options_map[type]();
   }

   return result;
}

AllegroFlare::DialogTree::NodeOptions::ExitDialog* YAMLLoader::parse_and_create_ExitDialog_option()
{
   AllegroFlare::DialogTree::NodeOptions::ExitDialog* result =
      new AllegroFlare::DialogTree::NodeOptions::ExitDialog;
   return result;
}

AllegroFlare::DialogTree::NodeOptions::GoToNode* YAMLLoader::parse_and_create_GoToNode_option(YAML::Node* data_node_ptr)
{
   if (!(data_node_ptr))
   {
      std::stringstream error_message;
      error_message << "[YAMLLoader::parse_and_create_GoToNode_option]: error: guard \"data_node_ptr\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("YAMLLoader::parse_and_create_GoToNode_option: error: guard \"data_node_ptr\" not met");
   }
   YAML::Node &node = *data_node_ptr;
   AllegroFlare::DialogTree::NodeOptions::GoToNode* result = new AllegroFlare::DialogTree::NodeOptions::GoToNode;

   // Validate the data
   validate_presence_of_key(node, OPTION_DATA_TARGET_NODE_NAME_KEY);
   validate_node_type(node, OPTION_DATA_TARGET_NODE_NAME_KEY, YAML::NodeType::Scalar);
   std::string result_target_node_name = node[std::string(OPTION_DATA_TARGET_NODE_NAME_KEY)].as<std::string>();

   // Assign the data to the result
   result->set_target_node_name(result_target_node_name);

   // Return the result
   return result;
}

AllegroFlare::DialogTree::NodeOptions::Node* YAMLLoader::parse_and_create_Node_option(YAML::Node* data_node_ptr)
{
   if (!(data_node_ptr))
   {
      std::stringstream error_message;
      error_message << "[YAMLLoader::parse_and_create_Node_option]: error: guard \"data_node_ptr\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("YAMLLoader::parse_and_create_Node_option: error: guard \"data_node_ptr\" not met");
   }
   YAML::Node &node = *data_node_ptr;
   AllegroFlare::DialogTree::NodeOptions::Node* result = new AllegroFlare::DialogTree::NodeOptions::Node;
    
   std::pair<std::string, AllegroFlare::DialogTree::Node*> created_node_for_option =
      parse_and_create_node(&node);
   //std::string option_node_name = created_node_for_option.first; // NOTE: For now, option nodes do not have names
   AllegroFlare::DialogTree::Node* option_node = created_node_for_option.second;
   result->set_node(option_node);

   // Return the result
   return result;
}


} // namespace DialogTree
} // namespace AllegroFlare


