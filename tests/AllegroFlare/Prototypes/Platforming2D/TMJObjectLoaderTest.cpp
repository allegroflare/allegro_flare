
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/Platforming2D/TMJObjectLoader.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


// TODO: Replace these hard-coded defines
#if defined(_WIN32) || defined(_WIN64)
#define TEST_FIXTURES_PATH "/msys64/home/Mark/Repos/allegro_flare/tests/fixtures/"
#else
#define TEST_FIXTURES_PATH "/Users/markoates/Repos/allegro_flare/tests/fixtures/"
#endif


TEST(AllegroFlare_Prototypes_Platforming2D_TMJObjectLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::TMJObjectLoader tmjobject_loader;
}


TEST(AllegroFlare_Prototypes_Platforming2D_TMJObjectLoaderTest, load__on_a_file_that_does_not_exist__throws_an_error)
{
   std::string filename = "some-file-that-does-not-exist.tmj";
   AllegroFlare::Prototypes::Platforming2D::TMJObjectLoader loader(filename);

   std::string expected_error_message = "[AllegroFlare::Prototypes::Platforming2D::TMJObjectLoader::load]: error: The file \""
                                        + filename + "\" does not exist.";

   ASSERT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_Platforming2D_TMJObjectLoaderTest, load__will_not_blow_up)
{
   //using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;
   std::string data_folder_path = TEST_FIXTURES_PATH;

   AllegroFlare::Prototypes::Platforming2D::TMJObjectLoader loader(
      TEST_FIXTURES_PATH "maps/map_with_objects-x.tmj"
   );

   //tmjobject_loader.object_parsed_callback();

   loader.load();
    
   //lod
   //AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory basic2d_factory(&get_bitmap_bin_ref());
   //std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> entities =
      //basic2d_factory.create_entities_from_map(TEST_FIXTURES_PATH "maps/map_with_objects-x.tmj", "map_a");
      //loader.set_(

//TEST_FIXTURES_PATH "maps/map_with_objects-x.tmj"

   // TODO: Test the created entities
   //ASSERT_EQ(2, entities.size());

   //AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D &entity1 = *entities[0];
   //EXPECT_EQ(true, entity1.exists("tmj_object_class", "door"));
   //EXPECT_EQ(true, entity1.exists(ON_MAP_NAME, "map_a"));

   //AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D &entity2 = *entities[1];
   //EXPECT_EQ(true, entity2.exists("tmj_object_class", "hopper"));
   //EXPECT_EQ(true, entity2.exists(ON_MAP_NAME, "map_a"));

   //for (auto &entity : entities) delete entity;
   //entities.clear();
};


