
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <AllegroFlare/Prototypes/MindDive/TunnelMeshTMJDataLoader.hpp>

// TODO: improve this:
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


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTMJDataLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader loader;
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTMJDataLoaderTest, get_loaded__before_calling_load__returns_false)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader loader(filename);
   ASSERT_EQ(false, loader.get_loaded());
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTMJDataLoaderTest, get_loaded__after_calling_load__returns_true)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader loader(filename);
   loader.load();
   ASSERT_EQ(true, loader.get_loaded());
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTMJDataLoaderTest, load__on_a_file_that_does_not_exist__throws_an_error)
{
   std::string filename = "some-file-that-does-not-exist.tmj";
   AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader loader(filename);

   std::string expected_error_message = "[MindDive::TunnelMeshTMJDataLoader] load() error: the file \""
                                        + filename + "\" does not exist.";

   ASSERT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTMJDataLoaderTest, load__on_a_file_with_malformed_json__throws_an_error)
{
   std::string filename = TMJ_MALFORMED_JSON_FIXTURE_PATH_AND_FILENAME;
   AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader loader(filename);

   std::stringstream expected_error_message;
   expected_error_message << "[MindDive::TunnelMeshTMJDataLoader] load() error: the file "
      "\"" << TMJ_MALFORMED_JSON_FIXTURE_PATH_AND_FILENAME << "\" "
      "appears to have malformed "
      "JSON. The following error was thrown by nlohmann::json: \"[json.exception.parse_error.101] parse error at line "
      "1, column 10: syntax error while parsing value - unexpected '}'; expected '[', '{', or a literal\"";

   ASSERT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message.str());
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTMJDataLoaderTest, load__returns_true)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader loader(filename);

   ASSERT_EQ(true, loader.load());
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTMJDataLoaderTest,
   load__if_load_has_already_been_called__throws_an_error)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader loader(filename);
   loader.load();

   std::string expected_error_message = "TunnelMeshTMJDataLoader::load: error: guard \"(!loaded)\" not met";

   ASSERT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTMJDataLoaderTest,
   load__will_set_the_properties_to_the_expected_values_for_the_layer)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader loader(filename);

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


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTMJDataLoaderTest,
   get_num_columns__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader loader;
   std::string expected_error_message = "TunnelMeshTMJDataLoader::get_num_columns: error: guard \"loaded\" not met";
   ASSERT_THROW_WITH_MESSAGE(loader.get_num_columns(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTMJDataLoaderTest,
   get_num_rows__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader loader;
   std::string expected_error_message = "TunnelMeshTMJDataLoader::get_num_rows: error: guard \"loaded\" not met";
   ASSERT_THROW_WITH_MESSAGE(loader.get_num_rows(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTMJDataLoaderTest,
   get_tile_width__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader loader;
   std::string expected_error_message = "TunnelMeshTMJDataLoader::get_tile_width: error: guard \"loaded\" not met";
   ASSERT_THROW_WITH_MESSAGE(loader.get_tile_width(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTMJDataLoaderTest,
   get_tile_height__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader loader;
   std::string expected_error_message = "TunnelMeshTMJDataLoader::get_tile_height: error: guard \"loaded\" not met";
   ASSERT_THROW_WITH_MESSAGE(loader.get_tile_height(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTMJDataLoaderTest,
   get_layer_num_columns__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader loader;
   std::string expected_error_message = "TunnelMeshTMJDataLoader::get_layer_num_columns: error: guard \"loaded\" not met";
   ASSERT_THROW_WITH_MESSAGE(loader.get_layer_num_columns(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTMJDataLoaderTest,
   get_layer_num_rows__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader loader;
   std::string expected_error_message = "TunnelMeshTMJDataLoader::get_layer_num_rows: error: guard \"loaded\" not met";
   ASSERT_THROW_WITH_MESSAGE(loader.get_layer_num_rows(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTMJDataLoaderTest,
   get_layer_tile_data__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader loader;
   std::string expected_error_message = "TunnelMeshTMJDataLoader::get_layer_tile_data: error: guard \"loaded\" not met";
   ASSERT_THROW_WITH_MESSAGE(loader.get_layer_tile_data(), std::runtime_error, expected_error_message);
}



