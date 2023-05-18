

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


AllegroFlare::DialogTree::Node* YAMLLoader::load(std::string yaml_string)
{
   // TODO
   AllegroFlare::DialogTree::Node *result = new AllegroFlare::DialogTree::Node;
   return result;
}


} // namespace DialogTree
} // namespace AllegroFlare


