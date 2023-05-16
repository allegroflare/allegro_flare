
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/Factory.hpp>


TEST(AllegroFlare_DialogTree_FactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::Factory factory;
}


TEST(AllegroFlare_DialogTree_FactoryTest, build_test_tree__will_return_a_node)
{
   AllegroFlare::DialogTree::Factory factory;
   AllegroFlare::DialogTree::Node* actual_node = factory.build_test_tree();
   EXPECT_NE(nullptr, actual_node);
}


