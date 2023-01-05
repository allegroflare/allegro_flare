
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AllegroFlare/SceneGraph/EntityPool.hpp>


class AllegroFlare_SceneGraph_EntityPoolTest : public ::testing::Test {};

class AllegroFlare_SceneGraph_EntityPoolTestWithEntities : public ::testing::Test
{
public:
   AllegroFlare::SceneGraph::EntityPool entity_pool;

   AllegroFlare::SceneGraph::Entities::Base* create_entity(std::string name, std::string tag)
   {
      AllegroFlare::SceneGraph::Entities::Base* result = new AllegroFlare::SceneGraph::Entities::Base();
      result->set("name", name);
      result->set(tag);
      return result;
   }
   AllegroFlare::SceneGraph::Entities::Base* create_entity(std::string name, std::string attribute, std::string parameter)
   {
      AllegroFlare::SceneGraph::Entities::Base* result = new AllegroFlare::SceneGraph::Entities::Base();
      result->set("name", name);
      result->set(attribute, parameter);
      return result;
   }
};



TEST_F(AllegroFlare_SceneGraph_EntityPoolTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SceneGraph::EntityPool entity_pool;
}


TEST_F(AllegroFlare_SceneGraph_EntityPoolTestWithEntities, select_A__will_select_entities_with_the_attribute)
{
   using namespace AllegroFlare::SceneGraph::Entities;

   Base* duck_entity = create_entity("duck_entity", "duck");
   Base* tree_entity1 = create_entity("tree_entity1", "tree");
   Base* tree_entity2 = create_entity("tree_entity2", "tree");
   Base* piece_of_sky_entity = create_entity("piece_of_sky_entity", "piece_of_sky");

   entity_pool.add({ duck_entity, tree_entity1, tree_entity2, piece_of_sky_entity });

   std::vector<Base*> expected = { tree_entity1, tree_entity2 };
   std::vector<Base*> actual = entity_pool.select_A("tree");

   EXPECT_THAT(expected, testing::UnorderedElementsAreArray(actual));
}


TEST_F(AllegroFlare_SceneGraph_EntityPoolTestWithEntities, select_C__will_select_entities_with_the_attribute)
{
   using namespace AllegroFlare::SceneGraph::Entities;

   Base* entity1 = create_entity("entity1", "on_map", "map-a");
   Base* entity2 = create_entity("entity2", "on_map", "map-b");
   Base* entity3 = create_entity("entity3", "on_map", "map-a");
   Base* entity4 = create_entity("entity4", "on_map", "map-b");

   entity_pool.add({ entity1, entity2, entity3, entity4, });

   std::vector<Base*> expected = { entity1, entity3 };
   std::vector<Base*> actual = entity_pool.select_C("on_map", "map-a");

   EXPECT_THAT(expected, testing::UnorderedElementsAreArray(actual));
}


