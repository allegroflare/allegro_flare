
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>


TEST(AllegroFlare_Prototypes_FixedRoom2D_EntityCollectionHelperTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper entity_collection_helper;
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_EntityCollectionHelperTest,
   select_all_entity_names_in_room_name__will_return_all_entity_names_that_are_currently_associated_with_the_room_name)
{
   std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entity_dictionary = {
      { "gameboy",       nullptr },
      { "ball_of_yarn",  nullptr },
      { "chair",         nullptr },
      { "persian_rug",   nullptr },
      { "garden_gnome",  nullptr },
      { "headphones",    nullptr },
      { "record_player", nullptr },
      { "vinyl_record",  nullptr },
   };
   std::map<std::string, std::string> entity_room_associations = {
      { "gameboy",       "playroom" },
      { "ball_of_yarn",  "terrace" },
      { "chair",         "terrace" },
      { "persian_rug",   "terrace" },
      { "garden_gnome",  "front_porch" },
      { "headphones",    "playroom" },
      { "record_player", "playroom"},
      { "vinyl_record",  "playroom" },
   };
   
   AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper entity_collection_helper(
      &entity_dictionary, &entity_room_associations);

   std::vector<std::string> expected_entity_names = { "ball_of_yarn", "chair", "persian_rug" };
   std::vector<std::string> actual_entity_names =
      entity_collection_helper.select_all_entity_names_in_room_name("terrace");

   ASSERT_THAT(actual_entity_names,
      ::testing::UnorderedElementsAreArray(expected_entity_names.begin(), expected_entity_names.end()));
}


