
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


TEST(AllegroFlare_Prototypes_FixedRoom2D_EntityCollectionHelperTest,
   find_entity_by_dictionary_name__if_the_listing_does_not_exist_with_that_name__will_return_nullptr)
{
   std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entity_dictionary;
   AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper entity_collection_helper(&entity_dictionary);

   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base *found_entity =
      entity_collection_helper.find_entity_by_dictionary_name("something_that_does_not_exist");

   EXPECT_EQ(nullptr, found_entity);
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_EntityCollectionHelperTest,
   find_entity_by_dictionary_name__will_return_the_entity_listed_under_the_name)
{
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base gameboy;
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base ball_of_yarn;
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base chair;
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base persian_rug;

   std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entity_dictionary = {
      { "gameboy",       &gameboy },
      { "ball_of_yarn",  &ball_of_yarn },
      { "chair",         &chair },
      { "persian_rug",   &persian_rug },
   };

   AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper entity_collection_helper(&entity_dictionary);

   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base *found_entity =
      entity_collection_helper.find_entity_by_dictionary_name("ball_of_yarn");

   EXPECT_EQ(&ball_of_yarn, found_entity);
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_EntityCollectionHelperTest,
   get_entities_by_entity_names__will_return_entities_matching_names)
{
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base gameboy;
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base ball_of_yarn;
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base chair;
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base persian_rug;

   std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entity_dictionary = {
      { "gameboy",       &gameboy },
      { "ball_of_yarn",  &ball_of_yarn },
      { "chair",         &chair },
      { "persian_rug",   &persian_rug },
   };

   AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper entity_collection_helper(&entity_dictionary);

   std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> returned_entities =
      entity_collection_helper.get_entities_by_entity_names({"ball_of_yarn", "persian_rug"});

   std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> expected_entities = {
      &ball_of_yarn, &persian_rug,
   };

   ASSERT_THAT(returned_entities,
      ::testing::UnorderedElementsAreArray(expected_entities.begin(), expected_entities.end()));
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_EntityCollectionHelperTest,
   get_entities_by_entity_names__if_a_listing_does_not_exist_with_a_provided_name__will_output_an_error_message)
{
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base gameboy;
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base ball_of_yarn;
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base chair;
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base persian_rug;

   std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entity_dictionary = {
      { "gameboy",       &gameboy },
      { "ball_of_yarn",  &ball_of_yarn },
      { "chair",         &chair },
      { "persian_rug",   &persian_rug },
   };

   AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper entity_collection_helper(&entity_dictionary);

   testing::internal::CaptureStdout();

   entity_collection_helper.get_entities_by_entity_names({"ball_of_yarn", "entity-name-that-does-not-exist", "chair"});

   std::string expected_cout_output = "[FixedRoom2D::EntityCollectionHelper::get_entities_from_entity_names]: warning: "
                                      "The provided entity name \"entity-name-that-does-not-exist\" does not have a "
                                      "listing. Ignoring.\n";
   std::string actual_cout_output = testing::internal::GetCapturedStdout();
   EXPECT_EQ(expected_cout_output, actual_cout_output);
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_EntityCollectionHelperTest,
   order_by_id__will_return_the_entities_ordered_by_id)
{
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base entity_1; // note that entities are automatically assigned an
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base entity_2;        // id on creation because they derive from
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base entity_3;        // AllegroFlare::ElementID. Each id will
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base entity_4;        // be sequential in order of creation
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base entity_5;
   AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper entity_collection_helper;

   std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> actual_entities =
      entity_collection_helper.order_by_id( { &entity_5, &entity_2, &entity_3, &entity_1, &entity_4 } );

   std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> expected_ordered_entities = {
      &entity_1, &entity_2, &entity_3, &entity_4, &entity_5,
   };

   EXPECT_EQ(expected_ordered_entities, actual_entities);
}


