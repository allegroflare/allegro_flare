
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <Tileo/TMJDataLoader.hpp>

#define TMJ_FIXTURE_PATH "/Users/markoates/Repos/tileo/tests/fixtures/"
#define TMJ_FIXTURE_WITH_MISSING_COLLISION_LAYER_FILENAME "map1.tmj"
#define TMJ_FIXTURE_FILENAME "map1-02.tmj"
#define TMJ_MALFORMED_JSON_FIXTURE_FILENAME "file-with-malformed-json.tmj"
#define TMJ_FIXTURE_PATH_AND_FILENAME (TMJ_FIXTURE_PATH TMJ_FIXTURE_FILENAME)
#define TMJ_FIXTURE_WITH_MISSING_COLLISION_LAYER_PATH_AND_FILENAME (TMJ_FIXTURE_PATH TMJ_FIXTURE_WITH_MISSING_COLLISION_LAYER_FILENAME)
#define TMJ_MALFORMED_JSON_FIXTURE_PATH_AND_FILENAME (TMJ_FIXTURE_PATH TMJ_MALFORMED_JSON_FIXTURE_FILENAME)


TEST(Tileo_TMJDataLoaderTest, can_be_created_without_blowing_up)
{
   Tileo::TMJDataLoader loader;
}


TEST(Tileo_TMJDataLoaderTest, get_loaded__before_calling_load__returns_false)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   Tileo::TMJDataLoader loader(filename);
   ASSERT_EQ(false, loader.get_loaded());
}


TEST(Tileo_TMJDataLoaderTest, get_loaded__after_calling_load__returns_true)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   Tileo::TMJDataLoader loader(filename);
   true, loader.load();
   ASSERT_EQ(true, loader.get_loaded());
}


TEST(Tileo_TMJDataLoaderTest, load__on_a_file_that_does_not_exist__throws_an_error)
{
   std::string filename = "some-file-that-does-not-exist.tmj";
   Tileo::TMJDataLoader loader(filename);

   std::string expected_error_message = "[Tileo/TMJDataLoader] load() error: the file \""
                                        + filename + "\" does not exist.";

   ASSERT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TMJDataLoaderTest, load__on_a_file_with_malformed_json__throws_an_error)
{
   std::string filename = TMJ_MALFORMED_JSON_FIXTURE_PATH_AND_FILENAME;
   Tileo::TMJDataLoader loader(filename);

   std::string expected_error_message = "[Tileo/TMJDataLoader] load() error: the file \""
      "/Users/markoates/Repos/tileo/tests/fixtures/file-with-malformed-json.tmj\" appears to have malformed JSON. "
      "The following error was thrown by nlohmann::json: \"[json.exception.parse_error.101] parse error at line 1, "
      "column 10: syntax error while parsing value - unexpected '}'; expected '[', '{', or a literal\"";

   ASSERT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TMJDataLoaderTest, load__returns_true)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   Tileo::TMJDataLoader loader(filename);

   ASSERT_EQ(true, loader.load());
}


TEST(Tileo_TMJDataLoaderTest, load__if_load_has_already_been_called__throws_an_error)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   Tileo::TMJDataLoader loader(filename);
   loader.load();

   std::string expected_error_message = "TMJDataLoader::load: error: guard \"(!loaded)\" not met";

   ASSERT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TMJDataLoaderTest, load__will_set_the_properties_to_the_expected_values_for_the_layer)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   Tileo::TMJDataLoader loader(filename);

   loader.load();

   ASSERT_EQ(25, loader.get_num_columns());
   ASSERT_EQ(15, loader.get_num_rows());
   ASSERT_EQ(25, loader.get_layer_num_columns());
   ASSERT_EQ(15, loader.get_layer_num_rows());
   ASSERT_EQ(16, loader.get_tile_width());
   ASSERT_EQ(16, loader.get_tile_height());

   std::vector<int> expected_tile_layer_data = {
      81, 102, 123, 123, 103, 82, 104, 114, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131, 131,
      131, 113, 103, 104, 122, 82, 103, 103, 82, 83, 82, 124, 132, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 130, 113, 123, 101, 84, 84, 84, 84, 84, 102, 123, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 130, 131, 131, 84, 84, 84, 84, 84, 104, 102, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 121, 83, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 122, 123, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 81, 101, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 81, 124, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 81, 104, 84, 84, 84, 181, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 90, 91, 91, 91, 91, 84, 84, 84, 84, 84, 103, 121, 84, 84, 84, 201, 84,
      84, 84, 161, 161, 84, 84, 84, 90, 93, 447, 91, 407, 427, 84, 84, 84, 84, 84, 124, 123, 84, 84, 84,
      201, 84, 84, 162, 163, 163, 164, 84, 90, 93, 408, 427, 447, 408, 427, 121, 123, 103, 101, 102, 124,
      122, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 93, 408, 446, 427, 446, 408, 446, 124, 124, 101,
      104, 103, 81, 121, 122, 102, 124, 123, 101, 101, 101, 122, 101, 121, 427, 81, 427, 408, 407, 407,
      447, 408, 82, 123, 101, 123, 103, 121, 124, 103, 121, 101, 124, 121, 103, 123, 104, 82, 406, 428,
      447, 406, 447, 447, 81, 426, 81, 81, 121, 103, 101, 101, 104, 104, 101, 104, 124, 122, 122, 104,
      102, 104, 408, 408, 81, 447, 408, 427, 408, 447, 446, 408
   };

   ASSERT_EQ(expected_tile_layer_data, loader.get_layer_tile_data());
}


TEST(Tileo_TMJDataLoaderTest, load__will_set_the_properties_to_the_expected_values_for_the_collision_layer)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   Tileo::TMJDataLoader loader(filename);

   loader.load();

   ASSERT_EQ(25, loader.get_collision_layer_num_columns());
   ASSERT_EQ(15, loader.get_collision_layer_num_rows());

   std::vector<int> expected_collision_layer_tile_data = {
      1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
      1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1
   };

   ASSERT_EQ(expected_collision_layer_tile_data, loader.get_collision_layer_tile_data());
}


TEST(Tileo_TMJDataLoaderTest,
   load__when_a_tilelayer_named_collision_is_not_present__throws_an_error_and_outputs_the_existing_layer_info)
{
   std::string filename = TMJ_FIXTURE_WITH_MISSING_COLLISION_LAYER_PATH_AND_FILENAME;
   Tileo::TMJDataLoader loader(filename);

std::string expected_error_message = R"(TMJMeshLoader: error: collision_tilelayer type not found. Expecting a layer of type "tilelayer" that also has a "name" property of "collision". Note that only the following layers present: "
  - layer 1:
    - type: ""tilelayer""
    - name: ""Tile Layer 1""
  - layer 2:
    - type: ""objectgroup""
    - name: ""Object Layer 1""
)";

   ASSERT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TMJDataLoaderTest, get_num_columns__before_load_has_been_called__will_throw_an_error)
{
   Tileo::TMJDataLoader loader;
   std::string expected_error_message = "TMJDataLoader::get_num_columns: error: guard \"loaded\" not met";
   ASSERT_THROW_WITH_MESSAGE(loader.get_num_columns(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TMJDataLoaderTest, get_num_rows__before_load_has_been_called__will_throw_an_error)
{
   Tileo::TMJDataLoader loader;
   std::string expected_error_message = "TMJDataLoader::get_num_rows: error: guard \"loaded\" not met";
   ASSERT_THROW_WITH_MESSAGE(loader.get_num_rows(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TMJDataLoaderTest, get_tile_width__before_load_has_been_called__will_throw_an_error)
{
   Tileo::TMJDataLoader loader;
   std::string expected_error_message = "TMJDataLoader::get_tile_width: error: guard \"loaded\" not met";
   ASSERT_THROW_WITH_MESSAGE(loader.get_tile_width(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TMJDataLoaderTest, get_tile_height__before_load_has_been_called__will_throw_an_error)
{
   Tileo::TMJDataLoader loader;
   std::string expected_error_message = "TMJDataLoader::get_tile_height: error: guard \"loaded\" not met";
   ASSERT_THROW_WITH_MESSAGE(loader.get_tile_height(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TMJDataLoaderTest, get_layer_num_columns__before_load_has_been_called__will_throw_an_error)
{
   Tileo::TMJDataLoader loader;
   std::string expected_error_message = "TMJDataLoader::get_layer_num_columns: error: guard \"loaded\" not met";
   ASSERT_THROW_WITH_MESSAGE(loader.get_layer_num_columns(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TMJDataLoaderTest, get_layer_num_rows__before_load_has_been_called__will_throw_an_error)
{
   Tileo::TMJDataLoader loader;
   std::string expected_error_message = "TMJDataLoader::get_layer_num_rows: error: guard \"loaded\" not met";
   ASSERT_THROW_WITH_MESSAGE(loader.get_layer_num_rows(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TMJDataLoaderTest, get_layer_tile_data__before_load_has_been_called__will_throw_an_error)
{
   Tileo::TMJDataLoader loader;
   std::string expected_error_message = "TMJDataLoader::get_layer_tile_data: error: guard \"loaded\" not met";
   ASSERT_THROW_WITH_MESSAGE(loader.get_layer_tile_data(), std::runtime_error, expected_error_message);
}


