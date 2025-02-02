
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/ImageLayerLoader.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
//#include <AllegroFlare/Testing/Comparison/AllegroFlare/Tiled/TMJImageLayer.hpp>


class AllegroFlare_Elements_ImageLayerLoaderTest : public ::testing::Test {};
class AllegroFlare_Elements_ImageLayerLoaderWithAllegroRenderingFixtureTest :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};




TEST_F(AllegroFlare_Elements_ImageLayerLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::ImageLayerLoader loader;
}


TEST_F(AllegroFlare_Elements_ImageLayerLoaderWithAllegroRenderingFixtureTest,
   load__on_a_file_that_does_not_exist__throws_an_error)
{
   std::string filename = "some-file-that-does-not-exist.tmj";
   AllegroFlare::Elements::ImageLayerLoader loader(&get_bitmap_bin_ref(), filename);

   std::string expected_error_message = "[AllegroFlare::Tiled::TMJImageLayerLoader::load]: error: The file "
      "\"some-file-that-does-not-exist.tmj\" does not exist.";

   ASSERT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_ImageLayerLoaderWithAllegroRenderingFixtureTest,
   load__will_not_blow_up)
{
   AllegroFlare::Elements::ImageLayerLoader loader(
      &get_bitmap_bin_ref(),
      get_data_folder_path() + "maps/test_map_with_image_layers-02.tmj"
   );

   loader.load();

   // Cleanup
   for (auto &image_layer : loader.get_image_layers_ref()) image_layer.destroy_bitmap_if_owned();
};


TEST_F(AllegroFlare_Elements_ImageLayerLoaderWithAllegroRenderingFixtureTest,
   load__will_load_the_expected_image_layers)
{
   AllegroFlare::Elements::ImageLayerLoader loader(
      &get_bitmap_bin_ref(),
      get_data_folder_path() + "maps/test_map_with_image_layers-02.tmj"
   );

   loader.load();

   std::vector<AllegroFlare::Elements::ImageLayer> expected_image_layers = {
      //AllegroFlare::Tiled::TMJImageLayer(
   //std::vector<AllegroFlare::Tiled::TMJImageLayer> expected_image_layers = {
     //AllegroFlare::Tiled::TMJImageLayer(
        //4, // id
        //"clouds_3", // name
        //"../bitmaps/backgrounds/SkyAndCloud5.png", // image_filename
        //50.0f, // offset_x
        //30.0f, // offset_y
        //0.8f, // parallax_x
        //0.8f, // parallax_y
        //true, // repeat_x
        //false, // repeat_y
        //1.0 // opacity // TODO: Check if this is a float when loaded from TMJ
     //),
     //AllegroFlare::Tiled::TMJImageLayer(
        //2, // id
        //"clouds_2", // name
        //"../bitmaps/backgrounds/Cloud2_resized.png", // image_filename
        //0.0f, // offset_x
        //0.0f, // offset_y
        //1.0f, // parallax_x
        //1.0f, // parallax_y
        //false, // repeat_x
        //false, // repeat_y
        //1.0, // opacity // TODO: Check if this is a float when loaded from TMJ
        //true
        //// TODO: Have AllegroFlare/Testing/Comparison/AllegroFlare/Tiled/TMJImageLayer compare color
        ////ALLEGRO_COLOR{0.2, 0.08, 0.153725, 0.2}
        ////ALLEGRO_COLOR{1.0, 0.5, 0.75, 0.5}
     //),
     //AllegroFlare::Tiled::TMJImageLayer(
        //3, // id
        //"clouds_1", // name
        //"../bitmaps/backgrounds/Cloud9_resized.png", // image_filename
        //50.0f, // offset_x
        //30.0f, // offset_y
        //1.2f, // parallax_x
        //1.2f, // parallax_y
        //true, // repeat_x
        //false, // repeat_y
        //0.75 // opacity // TODO: Check if this is a float when loaded from TMJ
     //),
   };

   std::vector<AllegroFlare::Elements::ImageLayer> &actual_image_layers = loader.get_image_layers_ref();
   //std::vector<AllegroFlare::Tiled::TMJImageLayer> actual_image_layers = loader.get_image_layers();

   EXPECT_EQ(3, actual_image_layers.size());
   // TODO: Continue testing on loaded data

   //EXPECT_EQ(expected_image_layers.size(), actual_image_layers.size());

   //EXPECT_EQ(expected_image_layers[0], actual_image_layers[0]);
   //EXPECT_EQ(expected_image_layers[1], actual_image_layers[1]);
   //EXPECT_EQ(expected_image_layers[2], actual_image_layers[2]);

   // Cleanup
   for (auto &image_layer : loader.get_image_layers_ref()) image_layer.destroy_bitmap_if_owned();
};


/*

AllegroFlare::Elements::ImageLayer

properties:


  - name: tmj_id
    type: int
    init_with: 0
    constructor_arg: true
    exposed: true

  - name: name
    type: std::string
    init_with: '"[unset-name]"'
    constructor_arg: true
    exposed: true

  - name: image_filename
    type: std::string
    init_with: '"[unset-image_filename]"'
    constructor_arg: true
    exposed: true

  - name: bitmap
    type: ALLEGRO_BITMAP*
    init_with: nullptr
    constructor_arg: true
    exposed: true

  - name: bitmap_is_owned
    type: bool
    init_with: false
    constructor_arg: true
    exposed: true

  - name: pixel_scale
    type: int
    init_with: 1
    constructor_arg: true
    exposed: true

  - name: offset_x
    type: float
    init_with: 0.0f
    constructor_arg: true
    exposed: true

  - name: offset_y
    type: float
    init_with: 0.0f
    constructor_arg: true
    exposed: true

  - name: parallax_x
    type: float
    init_with: 0.0f
    constructor_arg: true
    exposed: true

  - name: parallax_y
    type: float
    init_with: 0.0f
    constructor_arg: true
    exposed: true

  - name: repeat_x
    type: bool
    init_with: false
    constructor_arg: true
    exposed: true

  - name: repeat_y
    type: bool
    init_with: false
    constructor_arg: true
    exposed: true

  - name: opacity
    type: float
    init_with: 0.0f
    constructor_arg: true
    exposed: true

  - name: tint_color_is_set
    type: bool
    init_with: false
    constructor_arg: true
    exposed: true

  - name: tint_color
    type: ALLEGRO_COLOR
    init_with: DEFAULT_TINT_COLOR
    constructor_arg: true
    exposed: true

  - name: destroyed
    type: bool
    init_with: false
    constructor_arg: true
    exposed: true

  - name: DEFAULT_TINT_COLOR
    type: ALLEGRO_COLOR
    init_with: 'ALLEGRO_COLOR{1, 1, 1, 1}'
    static: true
    constexpr: true

*/


