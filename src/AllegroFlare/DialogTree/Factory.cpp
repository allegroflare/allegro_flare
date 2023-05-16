

#include <AllegroFlare/DialogTree/Factory.hpp>




namespace AllegroFlare
{
namespace DialogTree
{


Factory::Factory()
{
}


Factory::~Factory()
{
}


AllegroFlare::DialogTree::Node* Factory::build_test_tree()
{
   AllegroFlare::DialogTree::Node* result = new AllegroFlare::DialogTree::Node;
   return result;
}


} // namespace DialogTree
} // namespace AllegroFlare


