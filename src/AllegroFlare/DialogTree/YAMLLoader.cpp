

#include <AllegroFlare/DialogTree/YAMLLoader.hpp>

#include <AllegroFlare/BitFlags.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/Base.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <functional>
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


bool YAMLLoader::get_loaded() const
{
   return loaded;
}


AllegroFlare::DialogTree::NodeBank YAMLLoader::get_node_bank()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DialogTree::YAMLLoader::get_node_bank]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DialogTree::YAMLLoader::get_node_bank]: error: guard \"loaded\" not met");
   }
   return node_bank;
}

void YAMLLoader::load_file(std::string filename)
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DialogTree::YAMLLoader::load_file]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DialogTree::YAMLLoader::load_file]: error: guard \"(!loaded)\" not met");
   }
   if (!((AllegroFlare::php::file_exists(filename))))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DialogTree::YAMLLoader::load_file]: error: guard \"(AllegroFlare::php::file_exists(filename))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DialogTree::YAMLLoader::load_file]: error: guard \"(AllegroFlare::php::file_exists(filename))\" not met");
   }
   // TODO: Test this method
   // TODO: Refactor to use YAML's native YAML::LoadFile
   // TODO: Remove "file_exists" using php as dependency
   std::string yaml_as_string = AllegroFlare::php::file_get_contents(filename);
   return load(yaml_as_string);
}

void YAMLLoader::load(std::string yaml_as_string)
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DialogTree::YAMLLoader::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DialogTree::YAMLLoader::load]: error: guard \"(!loaded)\" not met");
   }
   if (!((!yaml_as_string.empty())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DialogTree::YAMLLoader::load]: error: guard \"(!yaml_as_string.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DialogTree::YAMLLoader::load]: error: guard \"(!yaml_as_string.empty())\" not met");
   }
   // TODO: Test guards
   AllegroFlare::DialogTree::NodeBank result;
   YAML::Node root_node = YAML::Load(yaml_as_string);

   // Validate that root_node is a sequence
   if (!root_node.IsSequence())
   {
      // TODO: Test this error path
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DialogTree::YAMLLoader",
         "Expecting the root node to be a sequence, but it is not."
      );
   }

   // TODO: Traverse the nodes, load as nodes
   for (const auto& node : root_node)
   {
      // TODO: Add "type" and load nodes by different types
      YAML::Node hack_node_copy = node;
      bool name_exists = validate_presence_of_key(hack_node_copy, "name", false);
      bool type_exists = validate_presence_of_key(hack_node_copy, "type", false);
      bool data_exists = validate_presence_of_key(hack_node_copy, "data", false);
      std::string DEFAULT_NODE_TYPE = MULTIPAGE_WITH_OPTIONS_KEY;
      std::string node_type = "[undefined-node_type]";

      if (!type_exists) node_type = DEFAULT_NODE_TYPE;
      else node_type = hack_node_copy["type"].as<std::string>();

      if (node_type == MULTIPAGE_WITH_OPTIONS_KEY)
      {
         if (!name_exists)
         {
            std::stringstream error_message;
            error_message << "[YAMLLoader::load]: error: When parsing node of \"type: "
                          << node_type << "\" expecting key of type \"name\" but it does not exist.";
            throw std::runtime_error(error_message.str());
         }
         if (!data_exists)
         {
            std::stringstream error_message;
            error_message << "[YAMLLoader::load]: error: When parsing node of \"type: "
                          << node_type << "\" expecting key of type \"data\" but it does not exist.";
            throw std::runtime_error(error_message.str());
         }

         //YAML::Node name_node = hack_node_copy["name"];
         YAML::Node data_node = hack_node_copy["data"];

         std::pair<std::string, AllegroFlare::DialogTree::Nodes::Base*> created_node_info =
            parse_and_create_MultipageWithOptions_node(&data_node);

         //std::string created_node_name = created_node->name_node;
         std::string created_node_name = hack_node_copy["name"].as<std::string>();
         AllegroFlare::DialogTree::Nodes::Base* created_node = created_node_info.second;

         node_bank.add_node(created_node_name, created_node);
      }
      else
      {
         std::stringstream error_message;
         error_message << "[YAMLLoader::load]: error: Cannot create a node of a \"type: "
                       << node_type << "\". A declaration to handle that type does not exist.";
         throw std::runtime_error(error_message.str());
      }
   }

   loaded = true;

   return;
}

std::pair<std::string, AllegroFlare::DialogTree::Nodes::MultipageWithOptions*> YAMLLoader::parse_and_create_MultipageWithOptions_node(YAML::Node* node_ptr)
{
   // TODO: Remove first element in pair, it was "name" but it is no longer neeed, as this method
   // should only parse data for the MultipageWithOptions object

   YAML::Node &root_node = *node_ptr; // TODO: Rename "root_node" to "node"
   std::string result_node_name = "unused-result_node_name--please_remove";
   AllegroFlare::DialogTree::Nodes::MultipageWithOptions *result_node =
      new AllegroFlare::DialogTree::Nodes::MultipageWithOptions;

   //// Extract a name node (if it is present)
   //bool name_node_is_present = validate_presence_of_key(root_node, NAME_KEY, false);
   //if (name_node_is_present)
   //{
      //validate_node_type(root_node, NAME_KEY, YAML::NodeType::Scalar);
      //result_node_name = root_node[std::string(NAME_KEY)].as<std::string>();
   //}

   // Validate and extract the speaker
   validate_presence_of_key(root_node, SPEAKER_KEY);
   validate_node_type(root_node, SPEAKER_KEY, YAML::NodeType::Scalar);
   std::string speaker = root_node[std::string(SPEAKER_KEY)].as<std::string>();
   result_node->set_speaker(speaker);

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
   result_node->set_pages(pages_vector);

   // Validate and extract the options
   // TODO: "options" node is optional
   bool options_is_present = validate_presence_of_key(root_node, OPTIONS_KEY, false);
   if (options_is_present)
   {
      validate_node_type(root_node, OPTIONS_KEY, YAML::NodeType::Sequence);
      YAML::Node options_node = root_node[std::string(OPTIONS_KEY)];
      std::vector<
            std::tuple<std::string, AllegroFlare::DialogTree::NodeOptions::Base*, AllegroFlare::BitFlags<uint32_t>>
         > options_vector;
      for (const auto& node : options_node)
      {
         std::string result_option_text = "[unset-result_text]";
         std::string result_option_type = "[unset-result_option_type]";
         AllegroFlare::BitFlags<uint32_t> result_option_flags = 0;
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

         options_vector.push_back(std::make_tuple(result_option_text, result_option, result_option_flags));
      }
      result_node->set_options(options_vector);
   }
   else // options_node_is_present is false
   {
      // If there are no "options:" in the YAML, create a default option to exit the script
      std::vector<
            std::tuple<std::string, AllegroFlare::DialogTree::NodeOptions::Base*, AllegroFlare::BitFlags<uint32_t>>
         > exit_dialog_option = {
         { "OK", new AllegroFlare::DialogTree::NodeOptions::ExitDialog, 0 },
      };
      result_node->set_options(exit_dialog_option);
   }

   // Return the result
   return { result_node_name, result_node };
}

AllegroFlare::DialogTree::NodeOptions::Base* YAMLLoader::parse_and_create_result_option(std::string type, YAML::Node* data_node_ptr)
{
   if (!(data_node_ptr))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DialogTree::YAMLLoader::parse_and_create_result_option]: error: guard \"data_node_ptr\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DialogTree::YAMLLoader::parse_and_create_result_option]: error: guard \"data_node_ptr\" not met");
   }
   AllegroFlare::DialogTree::NodeOptions::Base* result = nullptr;

   std::map<std::string, std::function<void()>> result_options_map = {
      { OPTION_TYPE_EXIT_DIALOG_KEY, [this, &result]() mutable {
         result = parse_and_create_ExitDialog_option();
      }},
      { OPTION_TYPE_GO_TO_NODE_KEY, [this, &result, data_node_ptr](){
         result = parse_and_create_GoToNode_option(data_node_ptr);
      }},
      //{ OPTION_TYPE_NODE_KEY, [this, &result, data_node_ptr](){
         //// NOTE: For now, option nodes do not have names. "name" is reserved for nodes on the root
         //result = parse_and_create_Node_option(data_node_ptr);
      //}},
   };

   // Locate and call the function to handle the item
   if (result_options_map.count(type) == 0)
   {
      // Item not found
      std::stringstream error_message;
      error_message << "[YAMLLoader::parse_and_create_result_option]: error: Cannot create an option of a type \""
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
      error_message << "[AllegroFlare::DialogTree::YAMLLoader::parse_and_create_GoToNode_option]: error: guard \"data_node_ptr\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DialogTree::YAMLLoader::parse_and_create_GoToNode_option]: error: guard \"data_node_ptr\" not met");
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


} // namespace DialogTree
} // namespace AllegroFlare


