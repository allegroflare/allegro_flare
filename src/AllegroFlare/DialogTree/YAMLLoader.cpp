

#include <AllegroFlare/DialogTree/YAMLLoader.hpp>

#include <AllegroFlare/DialogTree/NodeOptions/Base.hpp>
#include <AllegroFlare/Logger.hpp>
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
      std::string result_text = "foobar";
      AllegroFlare::DialogTree::NodeOptions::Base* result_option = nullptr;

      // TODO: Parse out each option->node type

      options_vector.push_back(std::make_pair(result_text, result_option));

      //if (node.IsScalar())
      //{
         //options_vector.push_back(node.as<std::string>());
      //}
      //else
      //{
         // TODO: Improve this error message
         // TODO: Test this error path
         //AllegroFlare::Logger::throw_error("here", "pages node contains a non-scalar element");
      //}
   }
   result->set_options(options_vector);

   // Return our result
   return result;
}


} // namespace DialogTree
} // namespace AllegroFlare


