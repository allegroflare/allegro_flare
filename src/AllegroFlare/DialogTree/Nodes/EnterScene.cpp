

#include <AllegroFlare/DialogTree/Nodes/EnterScene.hpp>




namespace AllegroFlare
{
namespace DialogTree
{
namespace Nodes
{


EnterScene::EnterScene(std::string property)
   : AllegroFlare::DialogTree::Nodes::Base(AllegroFlare::DialogTree::Nodes::EnterScene::TYPE)
   , property(property)
{
}


EnterScene::~EnterScene()
{
}


std::string EnterScene::get_property() const
{
   return property;
}


bool EnterScene::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace Nodes
} // namespace DialogTree
} // namespace AllegroFlare


