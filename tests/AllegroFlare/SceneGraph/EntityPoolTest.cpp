
#include <gtest/gtest.h>

#include <AllegroFlare/SceneGraph/EntityPool.hpp>


TEST(AllegroFlare_SceneGraph_EntityPoolTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SceneGraph::EntityPool entity_pool;
}


TEST(AllegroFlare_SceneGraph_EntityPoolTest, select__will_select_entities_with_the_attribute)
{
   using namespace AllegroFlare::SceneGraph;

   AllegroFlare::SceneGraph::EntityPool entity_pool;
   // TODO: sort out this ambiguous call:
   //std::vector<Entities::Base*> actual = entity_pool.select("blob");
}


TEST(AllegroFlare_SceneGraph_EntityPoolTest, DISABLED__select_A__will_select_entities_with_the_attribute)
{
   using namespace AllegroFlare::SceneGraph;

   AllegroFlare::SceneGraph::EntityPool entity_pool;

   std::vector<Entities::Base*> expected = {};
   std::vector<Entities::Base*> actual = entity_pool.select_A("blob");

   EXPECT_EQ(expected, actual);
}


