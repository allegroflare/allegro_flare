
#include <gtest/gtest.h>

#include <AllegroFlare/SceneGraph/EntityPool.hpp>


class AllegroFlare_SceneGraph_EntityPoolTest : public ::testing::Test {};

class AllegroFlare_SceneGraph_EntityPoolTestWithEntities : public ::testing::Test
{
public:
   AllegroFlare::SceneGraph::EntityPool entity_pool;

private:
   void SetUp() override
   {
      entity_pool.add();
   }
};



TEST_F(AllegroFlare_SceneGraph_EntityPoolTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SceneGraph::EntityPool entity_pool;
}


TEST_F(AllegroFlare_SceneGraph_EntityPoolTestWithEntities, DISABLED__select_A__will_select_entities_with_the_attribute)
{
   using namespace AllegroFlare::SceneGraph;

   //AllegroFlare::SceneGraph::EntityPool entity_pool;

   std::vector<Entities::Base*> expected = {};
   std::vector<Entities::Base*> actual = entity_pool.select_A("blob");

   EXPECT_EQ(expected, actual);
}


