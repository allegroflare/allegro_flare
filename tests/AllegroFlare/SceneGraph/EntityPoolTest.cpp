
#include <gtest/gtest.h>

#include <AllegroFlare/SceneGraph/EntityPool.hpp>


TEST(AllegroFlare_SceneGraph_EntityPoolTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SceneGraph::EntityPool entity_pool;
}


TEST(AllegroFlare_SceneGraph_EntityPoolTest, run__returns_the_expected_response)
{
   AllegroFlare::SceneGraph::EntityPool entity_pool;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, entity_pool.run());
}


