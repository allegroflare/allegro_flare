
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/Nodes/Base.hpp>


class NodesBaseTestClass : public AllegroFlare::DialogTree::Nodes::Base
{
public:
   NodesBaseTestClass()
      : AllegroFlare::DialogTree::Nodes::Base("NodesBaseTestClass")
   {}
};


TEST(AllegroFlare_DialogTree_Nodes_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::Nodes::Base base;
}


TEST(AllegroFlare_DialogTree_Nodes_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogTree/Nodes/Base",
     AllegroFlare::DialogTree::Nodes::Base::TYPE
   );
}


TEST(AllegroFlare_DialogTree_Nodes_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogTree::Nodes::Base base;
   EXPECT_EQ(AllegroFlare::DialogTree::Nodes::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_DialogTree_Nodes_BaseTest, derived_classes_will_have_the_expected_type)
{
   NodesBaseTestClass test_class;
   EXPECT_EQ("NodesBaseTestClass", test_class.get_type());
}


