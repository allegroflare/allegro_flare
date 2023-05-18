

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
   YAML::Node node = YAML::Load(yaml_as_string);
   AllegroFlare::DialogTree::Node *result = new AllegroFlare::DialogTree::Node;
   // TODO: Extract DialogTree::Node data from YAML
   return result;
}


} // namespace DialogTree
} // namespace AllegroFlare


