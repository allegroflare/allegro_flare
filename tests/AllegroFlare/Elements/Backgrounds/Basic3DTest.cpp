
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/Elements/Backgrounds/Basic3D.hpp>

class AllegroFlare_Elements_Backgrounds_Basic3DTest : public ::testing::Test {};
class AllegroFlare_Elements_Backgrounds_Basic3DWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST_F(AllegroFlare_Elements_Backgrounds_Basic3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Backgrounds::Basic3D basic_3d;
}


TEST_F(AllegroFlare_Elements_Backgrounds_Basic3DTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/Backgrounds/Basic3D",
     AllegroFlare::Elements::Backgrounds::Basic3D::TYPE
   );
}


TEST_F(AllegroFlare_Elements_Backgrounds_Basic3DTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::Backgrounds::Basic3D basic3d;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::Basic3D::TYPE, basic3d.get_type());
}


TEST_F(AllegroFlare_Elements_Backgrounds_Basic3DWithAllegroRenderingFixtureTest,
   CAPTURE__render__will_render_the_image)
{
   AllegroFlare::ModelBin model_bin;
   model_bin.set_full_path(get_fixtures_path() + "models");

   AllegroFlare::Elements::Backgrounds::Basic3D background;
   background.set_bitmap_bin(&get_bitmap_bin_ref());
   background.set_model_bin(&model_bin);
   background.initialize();

   AllegroFlare::GraphicsPipelines::Basic3D::Scene &scene = background.get_scene_ref();

   // Do some modifications to our scene
   {
      // Add 3 hearts to our scene
      scene.add_entity("heart_item-01.obj", "heart_item-02.png", { 0, 0, 0 });
      scene.add_entity("heart_item-01.obj", "heart_item-02.png", { -3, 0, 0 });
      scene.add_entity("heart_item-01.obj", "heart_item-02.png", { 3, 0, 0 });

      // Grab a reference to the camera so we can spin it
      AllegroFlare::Camera3D &camera = scene.get_camera_ref();

      // Use a different "camera lens"
      camera.zoom = 3.0;
      camera.stepout = { 0.0, 0.0, 20.0 };
   } //

   for (int i=0; i<300; i++)
   {
      // Update the scene
      AllegroFlare::Camera3D &camera = scene.get_camera_ref();
      camera.spin += 0.01;

      // Draw the scene
      al_clear_to_color(ALLEGRO_COLOR{0.001, 0.004, 0.01, 1.0});
      scene.render();
      al_flip_display();
   }
}


