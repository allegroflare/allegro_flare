
#include <gtest/gtest.h>

#include <AllegroFlare/SceneGraph/Entities/Base.hpp>


class EntitiesBaseTestClass : public AllegroFlare::SceneGraph::Entities::Base
{
public:
   EntitiesBaseTestClass()
      : AllegroFlare::SceneGraph::Entities::Base("EntitiesBaseTestClass")
   {}
};


TEST(AllegroFlare_SceneGraph_Entities_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SceneGraph::Entities::Base base;
}


TEST(AllegroFlare_SceneGraph_Entities_BaseTest, TYPE__has_the_expected_value)
{
   AllegroFlare::SceneGraph::Entities::Base base;
   EXPECT_EQ("Entities/Base", base.get_type());
}


TEST(AllegroFlare_SceneGraph_Entities_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::SceneGraph::Entities::Base base;
   EXPECT_EQ(AllegroFlare::SceneGraph::Entities::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_SceneGraph_Entities_BaseTest, derived_classes_will_have_the_expected_type)
{
   EntitiesBaseTestClass test_class;
   EXPECT_EQ("EntitiesBaseTestClass", test_class.get_type());
}


