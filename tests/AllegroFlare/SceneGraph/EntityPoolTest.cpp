
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
   AllegroFlare::SceneGraph::Entities::Base* create_entity(
         std::string name,
         std::string attribute,
         std::string parameter
      )
   {
      AllegroFlare::SceneGraph::Entities::Base* result = new AllegroFlare::SceneGraph::Entities::Base();
      result->set("name", name);
      result->set(attribute, parameter);
      return result;
   }
   AllegroFlare::SceneGraph::Entities::Base* create_entity(std::string name, std::vector<std::string> attributes)
   {
      AllegroFlare::SceneGraph::Entities::Base* result = new AllegroFlare::SceneGraph::Entities::Base();
      result->set("name", name);
      for (auto &attribute : attributes) { result->set(attribute); }
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


TEST_F(AllegroFlare_SceneGraph_EntityPoolTestWithEntities, select_B__will_select_entities_with_the_attribute)
{
   using namespace AllegroFlare::SceneGraph::Entities;

   Base* entity1 = create_entity("entity1", { "cold", "green", "large" });
   Base* entity2 = create_entity("entity2", { "hot", "orange", "large" });
   Base* entity3 = create_entity("entity3", { "cold", "red", "small" });
   Base* entity4 = create_entity("entity4", { "hot", "pink", "small" });
   Base* entity5 = create_entity("entity5", { "hot", "blue", "large" });

   entity_pool.add({ entity1, entity2, entity3, entity4, entity5 });

   std::vector<Base*> expected = { entity2, entity5 };
   std::vector<Base*> actual = entity_pool.select_B({ "large", "hot" });

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


TEST_F(AllegroFlare_SceneGraph_EntityPoolTestWithEntities, select_D__will_select_entities_with_the_attribute)
{
   // TODO: Add test
}


TEST_F(AllegroFlare_SceneGraph_EntityPoolTestWithEntities, select_E__will_select_entities_with_the_attribute)
{
   // TODO: This is a partial test, and does not account for *multiple* attribute<->param pairs used
   // during selection
   using namespace AllegroFlare::SceneGraph::Entities;

   Base* entity1 = create_entity("entity1", "on_map", "map-a"); //
   Base* entity2 = create_entity("entity2", "on_map", "map-b"); //
   Base* entity3 = create_entity("entity3", "on_map", "map-a");
   Base* entity4 = create_entity("entity4", "on_map", "map-b");
   Base* entity5 = create_entity("entity5", "on_map", "map-b"); //

   entity1->set("damages_player");
   entity2->set("damages_player");
   entity5->set("damages_player");

   entity_pool.add({ entity1, entity2, entity3, entity4, entity5 });

   std::vector<Base*> expected = { entity2, entity5 };
   std::vector<Base*> actual = entity_pool.select_E("damages_player", { { "on_map", "map-b" } });

   EXPECT_THAT(expected, testing::UnorderedElementsAreArray(actual));
}


TEST_F(AllegroFlare_SceneGraph_EntityPoolTestWithEntities, select_F__will_select_entities_with_the_attribute)
{
   // TODO: Add test
}


