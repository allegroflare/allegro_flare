
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Prototypes/TileDrive/TerrainMeshTMJDataLoader.hpp>


#if defined(_WIN32) || defined(_WIN64)
#define TMJ_FIXTURE_PATH "/msys64/home/Mark/Repos/allegro_flare/tests/fixtures/"
#else
#define TMJ_FIXTURE_PATH "/Users/markoates/Repos/allegro_flare/tests/fixtures/"
#endif


#define TMJ_FIXTURE_WITH_MISSING_COLLISION_LAYER_FILENAME "map1.tmj"
//#define TMJ_FIXTURE_FILENAME "map1-02.tmj"
#define TMJ_FIXTURE_FILENAME "tunnel_mesh-02.tmj"
#define TMJ_MALFORMED_JSON_FIXTURE_FILENAME "file-with-malformed-json.tmj"
#define TMJ_FIXTURE_PATH_AND_FILENAME (TMJ_FIXTURE_PATH TMJ_FIXTURE_FILENAME)
#define TMJ_FIXTURE_WITH_MISSING_COLLISION_LAYER_PATH_AND_FILENAME (TMJ_FIXTURE_PATH TMJ_FIXTURE_WITH_MISSING_COLLISION_LAYER_FILENAME)
#define TMJ_MALFORMED_JSON_FIXTURE_PATH_AND_FILENAME (TMJ_FIXTURE_PATH TMJ_MALFORMED_JSON_FIXTURE_FILENAME)


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshTMJDataLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::TileDrive::TerrainMeshTMJDataLoader loader;
}


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshTMJDataLoaderTest, get_loaded__before_calling_load__returns_false)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   AllegroFlare::Prototypes::TileDrive::TerrainMeshTMJDataLoader loader(filename);
   ASSERT_EQ(false, loader.get_loaded());
}


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshTMJDataLoaderTest, get_loaded__after_calling_load__returns_true)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   AllegroFlare::Prototypes::TileDrive::TerrainMeshTMJDataLoader loader(filename);
   loader.load();
   ASSERT_EQ(true, loader.get_loaded());
}


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshTMJDataLoaderTest,
   load__on_a_file_that_does_not_exist__throws_an_error)
{
   std::string filename = "some-file-that-does-not-exist.tmj";
   AllegroFlare::Prototypes::TileDrive::TerrainMeshTMJDataLoader loader(filename);

   std::string expected_error_message = "[TileDrive::TerrainMeshTMJDataLoader] load() error: the file \""
                                        + filename + "\" does not exist.";

   EXPECT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshTMJDataLoaderTest,
   load__on_a_file_with_malformed_json__throws_an_error)
{
   std::string filename = TMJ_MALFORMED_JSON_FIXTURE_PATH_AND_FILENAME;
   AllegroFlare::Prototypes::TileDrive::TerrainMeshTMJDataLoader loader(filename);

   std::stringstream expected_error_message;
   expected_error_message << "[TileDrive::TerrainMeshTMJDataLoader] load() error: the file "
                           "\"" << filename << "\" appears to have malformed JSON. The following error was "
                           "thrown by nlohmann::json: \"[json.exception.parse_error.101] parse error at line "
                           "1, column 10: syntax error while parsing value - unexpected '}'; expected '[', "
                           "'{', or a literal\"";

   EXPECT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message.str());
}


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshTMJDataLoaderTest, load__returns_true)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   AllegroFlare::Prototypes::TileDrive::TerrainMeshTMJDataLoader loader(filename);

   ASSERT_EQ(true, loader.load());
}


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshTMJDataLoaderTest,
   load__if_load_has_already_been_called__throws_an_error)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   AllegroFlare::Prototypes::TileDrive::TerrainMeshTMJDataLoader loader(filename);
   loader.load();

   std::string expected_error_message = "TerrainMeshTMJDataLoader::load: error: guard \"(!loaded)\" not met";

   EXPECT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshTMJDataLoaderTest,
   load__will_set_the_properties_to_the_expected_values_for_the_layer)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   AllegroFlare::Prototypes::TileDrive::TerrainMeshTMJDataLoader loader(filename);

   loader.load();

   ASSERT_EQ(12, loader.get_num_columns());
   ASSERT_EQ(96, loader.get_num_rows());
   ASSERT_EQ(12, loader.get_layer_num_columns());
   ASSERT_EQ(96, loader.get_layer_num_rows());
   ASSERT_EQ(50, loader.get_tile_width());
   ASSERT_EQ(50, loader.get_tile_height());

   std::vector<int> expected_tile_layer_data = {
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 3, 2, 3, 3, 2, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 3, 2, 3, 3, 2,
      3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 2, 3, 3, 2, 3, 3, 2, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 3,
      3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3,
      3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3,
      3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3,
      0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3,
      3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3,
      3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0,
      0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 3, 0, 3, 3, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 3, 3, 0, 3, 0, 0, 0, 0,
      0, 0, 3, 0, 3, 3, 0, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0,
      0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0,
      0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 1, 1, 3, 3, 3, 3, 3,
      3, 1, 1, 0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 0, 0, 1, 1, 3, 3, 3, 3,
      3, 3, 1, 1, 0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
   };

   ASSERT_EQ(expected_tile_layer_data, loader.get_layer_tile_data());
}


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshTMJDataLoaderTest,
   get_num_columns__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::TileDrive::TerrainMeshTMJDataLoader loader;
   std::string expected_error_message = "TerrainMeshTMJDataLoader::get_num_columns: error: guard \"loaded\" not met";
   EXPECT_THROW_WITH_MESSAGE(loader.get_num_columns(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshTMJDataLoaderTest,
   get_num_rows__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::TileDrive::TerrainMeshTMJDataLoader loader;
   std::string expected_error_message = "TerrainMeshTMJDataLoader::get_num_rows: error: guard \"loaded\" not met";
   EXPECT_THROW_WITH_MESSAGE(loader.get_num_rows(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshTMJDataLoaderTest,
   get_tile_width__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::TileDrive::TerrainMeshTMJDataLoader loader;
   std::string expected_error_message = "TerrainMeshTMJDataLoader::get_tile_width: error: guard \"loaded\" not met";
   EXPECT_THROW_WITH_MESSAGE(loader.get_tile_width(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshTMJDataLoaderTest,
   get_tile_height__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::TileDrive::TerrainMeshTMJDataLoader loader;
   std::string expected_error_message = "TerrainMeshTMJDataLoader::get_tile_height: error: guard \"loaded\" not met";
   EXPECT_THROW_WITH_MESSAGE(loader.get_tile_height(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshTMJDataLoaderTest,
   get_layer_num_columns__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::TileDrive::TerrainMeshTMJDataLoader loader;
   std::string expected_error_message =
      "TerrainMeshTMJDataLoader::get_layer_num_columns: error: guard \"loaded\" not met";
   EXPECT_THROW_WITH_MESSAGE(loader.get_layer_num_columns(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshTMJDataLoaderTest,
   get_layer_num_rows__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::TileDrive::TerrainMeshTMJDataLoader loader;
   std::string expected_error_message = "TerrainMeshTMJDataLoader::get_layer_num_rows: error: guard \"loaded\" not met";
   EXPECT_THROW_WITH_MESSAGE(loader.get_layer_num_rows(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshTMJDataLoaderTest,
   get_layer_tile_data__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::TileDrive::TerrainMeshTMJDataLoader loader;
   std::string expected_error_message =
      "TerrainMeshTMJDataLoader::get_layer_tile_data: error: guard \"loaded\" not met";
   EXPECT_THROW_WITH_MESSAGE(loader.get_layer_tile_data(), std::runtime_error, expected_error_message);
}




