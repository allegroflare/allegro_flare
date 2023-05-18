

#include <AllegroFlare/DialogTree/YAMLLoader.hpp>




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
   validate_presence_of_key(root_node, "speaker");
   validate_node_type(root_node, "speaker", YAML::NodeType::Scalar);
   std::string speaker = root_node["speaker"].as<std::string>();

   result->set_speaker(speaker);
   //validate_presence_of_key(root_node, "pages");
   return result;
}


} // namespace DialogTree
} // namespace AllegroFlare


