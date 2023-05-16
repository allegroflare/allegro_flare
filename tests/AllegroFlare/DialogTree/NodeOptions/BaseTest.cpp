
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/NodeOptions/Base.hpp>


class NodeOptionsBaseTestClass : public AllegroFlare::DialogTree::NodeOptions::Base
{
public:
   NodeOptionsBaseTestClass()
      : AllegroFlare::DialogTree::NodeOptions::Base("NodeOptionsBaseTestClass")
   {}
};


TEST(AllegroFlare_DialogTree_NodeOptions_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::NodeOptions::Base base;
}


TEST(AllegroFlare_DialogTree_NodeOptions_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogTree/NodeOptions/Base",
     AllegroFlare::DialogTree::NodeOptions::Base::TYPE
   );
}


TEST(AllegroFlare_DialogTree_NodeOptions_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogTree::NodeOptions::Base base;
   EXPECT_EQ(AllegroFlare::DialogTree::NodeOptions::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_DialogTree_NodeOptions_BaseTest, derived_classes_will_have_the_expected_type)
{
   NodeOptionsBaseTestClass test_class;
   EXPECT_EQ("NodeOptionsBaseTestClass", test_class.get_type());
}


