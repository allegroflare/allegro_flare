
#include <gtest/gtest.h>

#include <AllegroFlare/Tiled/TMJImageLayerLoader.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/Tiled/TMJImageLayer.hpp>


TEST(AllegroFlare_Prototypes_Platforming2D_TMJObjectLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Tiled::TMJImageLayerLoader loader;
}


TEST(AllegroFlare_Prototypes_Platforming2D_TMJObjectLoaderTest,
   load__on_a_file_that_does_not_exist__throws_an_error)
{
   std::string filename = "some-file-that-does-not-exist.tmj";
   AllegroFlare::Tiled::TMJImageLayerLoader loader(filename);

   std::string expected_error_message = "[AllegroFlare::Tiled::TMJImageLayerLoader::load]: error: The file "
      "\"some-file-that-does-not-exist.tmj\" does not exist.";

   ASSERT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_Prototypes_Platforming2D_TMJObjectLoaderTest,
   load__when_no_image_layers_are_present_in_the_map__will_throw_an_error)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string maps_data_folder_path = deployment_environment.get_data_folder_path() + "maps/";
   AllegroFlare::Tiled::TMJImageLayerLoader loader(maps_data_folder_path + "test_map_with_no_layers-01.tmj");

   std::string expected_error_message = "[AllegroFlare::Tiled::TMJImageLayerLoader::load]: error: Layer of type "
      "\"imagelayer\" not found";

   ASSERT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
};


TEST(AllegroFlare_Prototypes_Platforming2D_TMJObjectLoaderTest, load__will_not_blow_up)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string maps_data_folder_path = deployment_environment.get_data_folder_path() + "maps/";

   AllegroFlare::Tiled::TMJImageLayerLoader loader(maps_data_folder_path + "test_map_with_image_layers-01.tmj");

   loader.load();
};


TEST(AllegroFlare_Prototypes_Platforming2D_TMJObjectLoaderTest, load__will_load_the_expected_image_layers)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string maps_data_folder_path = deployment_environment.get_data_folder_path() + "maps/";
   AllegroFlare::Tiled::TMJImageLayerLoader loader(maps_data_folder_path + "test_map_with_image_layers-01.tmj");

   loader.load();

   std::vector<AllegroFlare::Tiled::TMJImageLayer> expected_image_layers = {
     AllegroFlare::Tiled::TMJImageLayer(
        4, // id
        "clouds_3", // name
        "../bitmaps/backgrounds/SkyAndCloud5.png", // image_filename
        50.0f, // offset_x
        30.0f, // offset_y
        0.8f, // parallax_x
        0.8f, // parallax_y
        true, // repeat_x
        false, // repeat_y
        1.0 // opacity // TODO: Check if this is a float when loaded from TMJ
     ),
     AllegroFlare::Tiled::TMJImageLayer(
        2, // id
        "clouds_2", // name
        "../bitmaps/backgrounds/Cloud2_resized.png", // image_filename
        0.0f, // offset_x
        0.0f, // offset_y
        1.0f, // parallax_x
        1.0f, // parallax_y
        false, // repeat_x
        false, // repeat_y
        1.0, // opacity // TODO: Check if this is a float when loaded from TMJ
        true
        // TODO: Have AllegroFlare/Testing/Comparison/AllegroFlare/Tiled/TMJImageLayer compare color
        //ALLEGRO_COLOR{0.2, 0.08, 0.153725, 0.2}
        //ALLEGRO_COLOR{1.0, 0.5, 0.75, 0.5}
     ),
     AllegroFlare::Tiled::TMJImageLayer(
        3, // id
        "clouds_1", // name
        "../bitmaps/backgrounds/Cloud9_resized.png", // image_filename
        50.0f, // offset_x
        30.0f, // offset_y
        1.2f, // parallax_x
        1.2f, // parallax_y
        true, // repeat_x
        false, // repeat_y
        0.75 // opacity // TODO: Check if this is a float when loaded from TMJ
     ),
   };

   std::vector<AllegroFlare::Tiled::TMJImageLayer> actual_image_layers = loader.get_image_layers();

   EXPECT_EQ(3, expected_image_layers.size());
   EXPECT_EQ(expected_image_layers.size(), actual_image_layers.size());

   EXPECT_EQ(expected_image_layers[0], actual_image_layers[0]);
   EXPECT_EQ(expected_image_layers[1], actual_image_layers[1]);
   EXPECT_EQ(expected_image_layers[2], actual_image_layers[2]);
};


