
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>
#include <AllegroFlare/Tiled/TMJDataLoader.hpp>
#include <AllegroFlare/Testing/Comparison/ALLEGRO_COLOR.hpp>


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Tiled::TMJDataLoader loader;
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, get_loaded__before_calling_load__returns_false)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/test_world-01.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   ASSERT_EQ(false, loader.get_loaded());
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, get_loaded__after_calling_load__returns_true)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/test_world-01.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   loader.load();
   ASSERT_EQ(true, loader.get_loaded());
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest,
   load__on_a_file_that_does_not_exist__throws_an_error)
{
   std::string filename = "some-file-that-does-not-exist.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);

   std::string expected_error_message = 
     R"([AllegroFlare::Tiled::TMJDataLoader::load]: error: The expected tmj file does not exist. Looking for )"
     R"("some-file-that-does-not-exist.tmj" from the current path "/Users/markoates/Repos/allegro_flare".)";

   EXPECT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, load__will_load_the_expected_objects_into_an_object_layer)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/test_world_with_object_layer-01.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   loader.load();
   ASSERT_EQ(2, loader.get_objects_ref().size());

   auto entity1 = loader.get_objects_ref()[0];
   EXPECT_EQ(entity1.type, "main_exit");
   EXPECT_EQ(true, entity1.custom_properties.exists("gravity_orientation"));
   EXPECT_EQ(true, entity1.custom_properties.is_string("gravity_orientation"));
   EXPECT_EQ("left", entity1.custom_properties.get_string("gravity_orientation"));

   auto entity2 = loader.get_objects_ref()[1];
   EXPECT_EQ(entity2.type, "player_spawn");
   EXPECT_EQ(true, entity2.custom_properties.empty());
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, load__will_load_polygon_data)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/golf_hole_with_polygons-01.tmj";

   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   loader.load();
   ASSERT_EQ(10, loader.get_objects_ref().size());

   auto entity1 = loader.get_objects_ref()[0];
   EXPECT_EQ(11, entity1.polygon.size());
   EXPECT_EQ("fairway", entity1.type);
   EXPECT_EQ(400.0f, entity1.x);
   EXPECT_EQ(896.0f, entity1.y);
   EXPECT_EQ(0.0f, entity1.width);
   EXPECT_EQ(0.0f, entity1.height);
   EXPECT_EQ("field", entity1.object_layer_name);
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, load__will_load_text_data)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/map_with_text_objects-03.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   loader.load();
   ASSERT_EQ(5, loader.get_objects_ref().size());

   // Entity that does have text with default alignment
   auto entity1 = loader.get_objects_ref()[0];
   EXPECT_EQ(true, entity1.text__is_present);
   EXPECT_EQ("Hello World", entity1.text__text);
   EXPECT_EQ("left", entity1.text__align_horizontal);
   EXPECT_EQ("top", entity1.text__align_vertical);

   // Entity that does not have text (and should have empty text__* values
   auto entity2 = loader.get_objects_ref()[1];
   EXPECT_EQ(false, entity2.text__is_present);
   EXPECT_EQ("", entity2.text__text);
   EXPECT_EQ("", entity2.text__align_horizontal);
   EXPECT_EQ("", entity2.text__align_vertical);

   // Entity that does have text and custom alignment
   auto entity3 = loader.get_objects_ref()[2];
   EXPECT_EQ(true, entity3.text__is_present);
   EXPECT_EQ("Hello Alignment", entity3.text__text);
   EXPECT_EQ("center", entity3.text__align_horizontal);
   EXPECT_EQ("bottom", entity3.text__align_vertical);

   // Entity that does have text and custom alignment
   auto entity4 = loader.get_objects_ref()[3];
   EXPECT_EQ(true, entity4.text__is_present);
   EXPECT_EQ("Custom Font", entity4.text__text);
   EXPECT_EQ("Trajan Pro 3", entity4.text__font_name);
   EXPECT_EQ(30, entity4.text__font_size);

   // Entity that does have text and custom color (and opacity)
   ALLEGRO_COLOR expected_color = ALLEGRO_COLOR{1.0f, 0.25f, 1.0f, 1.0f};
   auto entity5 = loader.get_objects_ref()[4];
   EXPECT_EQ(true, entity5.text__is_present);
   EXPECT_EQ("Magenta Color", entity5.text__text);
   EXPECT_FLOAT_EQ(expected_color.r, entity5.text__color.r);
   EXPECT_NEAR(expected_color.g, entity5.text__color.g, 0.001);
   EXPECT_FLOAT_EQ(expected_color.b, entity5.text__color.b);
   EXPECT_FLOAT_EQ(expected_color.a, entity5.text__color.a);
   EXPECT_NEAR(0.75, entity5.text__opacity, 0.001);
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, convert_hex_to_rgba_f__will_handle_6_character_hexes)
{
   std::tuple<float, float, float, float> result = AllegroFlare::Tiled::TMJDataLoader::convert_hex_to_rgba_f("#ff3366");
   EXPECT_FLOAT_EQ(1.0, std::get<0>(result));
   EXPECT_FLOAT_EQ(0.2, std::get<1>(result));
   EXPECT_FLOAT_EQ(0.4, std::get<2>(result));
   EXPECT_FLOAT_EQ(1.0, std::get<3>(result));
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, convert_hex_to_rgba_f__will_handle_8_character_hexes_and_premultiply_alpha)
{
   std::tuple<float, float, float, float> result = AllegroFlare::Tiled::TMJDataLoader::convert_hex_to_rgba_f("#80ff3366");
   EXPECT_FLOAT_EQ(1.0, std::get<0>(result));
   EXPECT_FLOAT_EQ(0.2, std::get<1>(result));
   EXPECT_FLOAT_EQ(0.4, std::get<2>(result));
   EXPECT_FLOAT_EQ((float)128 / 255, std::get<3>(result)); // NOTE: less precision on 0.5 because 128/255
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, load__will_load_multiple_tilemap_layers)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/test_world_with_visual_layer-01.tmj";

   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   loader.load();

   // Validate the size
   ASSERT_EQ(20, loader.get_num_columns());
   ASSERT_EQ(20, loader.get_num_rows());
   ASSERT_EQ(3, loader.get_tilelayers_tile_data().size());

   // Check the layer names
   std::map<std::string, std::vector<int>> tilelayers_tile_data = loader.get_tilelayers_tile_data();
   std::set<std::string> actual_layer_names;
   for (const auto &pair : tilelayers_tile_data) actual_layer_names.insert(pair.first);
   std::set<std::string> expected_layer_names = { "collision", "visual", "visual_prototype" };
   ASSERT_EQ(expected_layer_names, actual_layer_names);

   // TODO: Cherry-pick some specific tiles for validation
   auto &visual_layer_tile_data = tilelayers_tile_data["visual"];
   int num_columns = loader.get_num_columns();
   EXPECT_EQ(0, visual_layer_tile_data[2]);
   EXPECT_EQ(2, visual_layer_tile_data[3]);
   EXPECT_EQ(3, visual_layer_tile_data[4 + 7*num_columns]);
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, tilelayer_exists__will_return_true_when_the_layer_is_present)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/test_world_with_visual_layer-01.tmj";

   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   loader.load();

   EXPECT_EQ(true, loader.tilelayer_exists("visual"));
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, tilelayer_exists__will_return_false_when_the_layer_is_not_present)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/test_world_with_visual_layer-01.tmj";

   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   loader.load();

   EXPECT_EQ(false, loader.tilelayer_exists("a_layer_name_that_is_not_present"));
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest,
   for_each_object__will_call_the_provided_function_with_each_object_as_an_argument)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/test_world_with_object_layer-01.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   loader.load();
   ASSERT_EQ(2, loader.get_objects_ref().size());

   int call_count = 0;
   std::set<std::string> object_types_to_exhaust = { "main_exit", "player_spawn" };

   loader.for_each_object([&call_count, &object_types_to_exhaust](AllegroFlare::Tiled::TMJObject* object, void*){
      call_count++;
      ASSERT_NE(nullptr, object);
      auto it = object_types_to_exhaust.find(object->type);
      ASSERT_NE(it, object_types_to_exhaust.end());
      object_types_to_exhaust.erase(it);
   });

   EXPECT_EQ(2, call_count);
   EXPECT_EQ(true, object_types_to_exhaust.empty());
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, load__on_a_file_with_malformed_json__throws_an_error)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "file-with-malformed-json.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);

   std::stringstream expected_error_message;
   expected_error_message << "[AllegroFlare::Tiled::TMJDataLoader::load()]: error: The file "
      "\"" << filename << "\""
      " appears to have malformed "
      "JSON. The following error was thrown by nlohmann::json: \"[json.exception.parse_error.101] parse error at line "
      "1, column 10: syntax error while parsing value - unexpected '}'; expected '[', '{', or a literal\"";

   EXPECT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message.str());
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, load__returns_true)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/test_world-01.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);

   ASSERT_EQ(true, loader.load());
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, load__if_load_has_already_been_called__throws_an_error)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/test_world-01.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   loader.load();

   EXPECT_THROW_GUARD_ERROR(
      loader.load(),
      "AllegroFlare::Tiled::TMJDataLoader::load",
      "(!loaded)"
   );
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, load__on_this_specific_map__will_load_as_expected)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/stone_stage-01.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);

   ASSERT_EQ(true, loader.load());
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, load__will_load_map_custom_properties)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/map_with_custom_properties-02.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   ASSERT_EQ(true, loader.load());

   AllegroFlare::Tiled::TMJObjectCustomProperties map_custom_properties = loader.get_map_custom_properties();
   EXPECT_EQ(true, map_custom_properties.exists("width_in_tiles"));
   ASSERT_EQ(true, map_custom_properties.is_int("width_in_tiles"));
   EXPECT_EQ(7, map_custom_properties.get_int("width_in_tiles"));
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, load__when_a_map_class_is_present__will_assign_the_value_to_map_class)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/map_with_custom_properties-02.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   ASSERT_EQ(true, loader.load());
   EXPECT_EQ("room_with_walls", loader.get_map_class());
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, load__when_a_map_class_is_not_present__will_set_map_class_to_blank)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/stone_stage-01.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   ASSERT_EQ(true, loader.load());
   EXPECT_EQ("", loader.get_map_class());
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, load__will_capture_tilesets)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/room_with_different_tilesets-01.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   ASSERT_EQ(true, loader.load());

   std::vector<std::tuple<int, std::string, std::string>> tilesets = loader.get_tilesets();
   ASSERT_EQ(2, tilesets.size());

   std::tuple<int, std::string, std::string> expected_tileset_1{
      1, 
      "../../../project_files/tiles_dungeon_v1.1.tsj",
      "tiles_dungeon_v1.1.tsj"
   };
   EXPECT_EQ(expected_tileset_1, tilesets[0]);

   std::tuple<int, std::string, std::string> expected_tileset_2{
      721, 
      "..\/..\/..\/project_files\/Village_Tileset.tsj",
      "Village_Tileset.tsj"
   };
   EXPECT_EQ(expected_tileset_2, tilesets[1]);
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest,
   load__when_no_background_color_is_present__will_use_the_DEFAULT_BACKGROUND_COLOR)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/map_with_no_background_color-01.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   ASSERT_EQ(true, loader.load());

   ALLEGRO_COLOR expected_background_color = AllegroFlare::Tiled::TMJDataLoader::DEFAULT_BACKGROUND_COLOR;
   ALLEGRO_COLOR actual_background_color = loader.get_background_color();

   EXPECT_EQ(expected_background_color.r, actual_background_color.r);
   EXPECT_EQ(expected_background_color.g, actual_background_color.g);
   EXPECT_EQ(expected_background_color.b, actual_background_color.b);
   EXPECT_EQ(expected_background_color.a, actual_background_color.a);
}


TEST(AllegroFlare_Tiled_TMJDataLoaderTest, load__will_extract_the_background_color)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "maps/map_with_background_color-01.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   ASSERT_EQ(true, loader.load());

   ALLEGRO_COLOR actual_background_color = loader.get_background_color();

   EXPECT_EQ(0.2f, actual_background_color.r);
   EXPECT_EQ(0.4f, actual_background_color.g);
   EXPECT_EQ(0.6f, actual_background_color.b);
   EXPECT_EQ(1.0f, actual_background_color.a);
}


//map_with_custom_properties-02.tmj


// TODO: Uncomment these tests


/*
TEST(AllegroFlare_Tiled_TMJDataLoaderTest,
   load__will_set_the_properties_to_the_expected_values_for_the_layer)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string filename = deployment_environment.get_data_folder_path() + "map1-02.tmj";
   AllegroFlare::Tiled::TMJDataLoader loader(filename);
   //std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   //AllegroFlare::Tiled::TMJDataLoader loader(filename);

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
*/


/*
TEST(AllegroFlare_Prototypes_Platforming2D_TMJDataLoaderTest,
   load__will_set_the_properties_to_the_expected_values_for_the_collision_layer)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   AllegroFlare::Prototypes::Platforming2D::TMJDataLoader loader(filename);

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


TEST(AllegroFlare_Prototypes_Platforming2D_TMJDataLoaderTest,
   load__when_a_tilelayer_named_collision_is_not_present__throws_an_error_and_outputs_the_existing_layer_info)
{
   std::string filename = TMJ_FIXTURE_WITH_MISSING_COLLISION_LAYER_PATH_AND_FILENAME;
   AllegroFlare::Prototypes::Platforming2D::TMJDataLoader loader(filename);

std::string expected_error_message = R"(TMJMeshLoader: error: collision_tilelayer type not found. Expecting a layer of type "tilelayer" that also has a "name" property of "collision". Note that only the following layers present: "
  - layer 1:
    - type: ""tilelayer""
    - name: ""Tile Layer 1""
  - layer 2:
    - type: ""objectgroup""
    - name: ""Object Layer 1""
)";

   EXPECT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_Platforming2D_TMJDataLoaderTest,
   get_num_columns__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::Platforming2D::TMJDataLoader loader;
   EXPECT_THROW_GUARD_ERROR(
      loader.get_num_columns(),
      "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_num_columns",
      "loaded"
   );
}


TEST(AllegroFlare_Prototypes_Platforming2D_TMJDataLoaderTest,
   get_num_rows__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::Platforming2D::TMJDataLoader loader;
   EXPECT_THROW_GUARD_ERROR(
      loader.get_num_rows(),
      "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_num_rows",
      "loaded"
   );
}


TEST(AllegroFlare_Prototypes_Platforming2D_TMJDataLoaderTest,
   get_tile_width__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::Platforming2D::TMJDataLoader loader;
   EXPECT_THROW_GUARD_ERROR(
      loader.get_tile_width(),
      "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_tile_width",
      "loaded"
   );
}


TEST(AllegroFlare_Prototypes_Platforming2D_TMJDataLoaderTest,
   get_tile_height__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::Platforming2D::TMJDataLoader loader;
   EXPECT_THROW_GUARD_ERROR(
      loader.get_tile_height(),
      "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_tile_height",
      "loaded"
   );
}


TEST(AllegroFlare_Prototypes_Platforming2D_TMJDataLoaderTest,
   get_layer_num_columns__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::Platforming2D::TMJDataLoader loader;
   EXPECT_THROW_GUARD_ERROR(
      loader.get_layer_num_columns(),
      "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_layer_num_columns",
      "loaded"
   );
}


TEST(AllegroFlare_Prototypes_Platforming2D_TMJDataLoaderTest,
   get_layer_num_rows__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::Platforming2D::TMJDataLoader loader;
   EXPECT_THROW_GUARD_ERROR(
      loader.get_layer_num_rows(),
      "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_layer_num_rows",
      "loaded"
   );
}


TEST(AllegroFlare_Prototypes_Platforming2D_TMJDataLoaderTest,
   get_layer_tile_data__before_load_has_been_called__will_throw_an_error)
{
   AllegroFlare::Prototypes::Platforming2D::TMJDataLoader loader;
   EXPECT_THROW_GUARD_ERROR(
      loader.get_layer_tile_data(),
      "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_layer_tile_data",
      "loaded"
   );
}
*/


