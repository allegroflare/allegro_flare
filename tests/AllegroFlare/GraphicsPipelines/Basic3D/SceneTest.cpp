#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/GraphicsPipelines/Basic3D/Scene.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_GraphicsPipelines_Basic3D_SceneTest : public ::testing::Test {};
class AllegroFlare_GraphicsPipelines_Basic3D_SceneTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



// TODO: These commented tests:
/*
TEST_F(AllegroFlare_GraphicsPipelines_Basic3D_SceneTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GraphicsPipelines::Basic3D::Scene scene;
}


TEST_F(AllegroFlare_GraphicsPipelines_Basic3D_SceneTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::GraphicsPipelines::Basic3D::Scene scene;
   std::string expected_error_message =
      "Scene::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(scene.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_GraphicsPipelines_Basic3D_SceneTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::GraphicsPipelines::Basic3D::Scene scene;
   std::string expected_error_message =
      "Scene::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(scene.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_GraphicsPipelines_Basic3D_SceneTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::GraphicsPipelines::Basic3D::Scene scene;
   std::string expected_error_message =
      "Scene::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(scene.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_GraphicsPipelines_Basic3D_SceneTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::GraphicsPipelines::Basic3D::Scene scene;
   std::string expected_error_message =
      "Scene::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(scene.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   
*/


TEST_F(AllegroFlare_GraphicsPipelines_Basic3D_SceneTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::ModelBin model_bin;
   model_bin.set_full_path(get_fixtures_path() + "models");

   AllegroFlare::GraphicsPipelines::Basic3D::Scene scene;
   scene.set_bitmap_bin(&get_bitmap_bin_ref());
   scene.set_model_bin(&model_bin);
   scene.initialize();

   // Add 3 hearts to our scene
   scene.add_entity("heart_item-01.obj", "heart_item-02.png", { 0, 0, 0 });
   scene.add_entity("heart_item-01.obj", "heart_item-02.png", { -3, 0, 0 });
   scene.add_entity("heart_item-01.obj", "heart_item-02.png", { 3, 0, 0 });

   // Grab a reference to the camera so we can spin it
   AllegroFlare::Camera3D &camera = scene.get_camera_ref();

   // Use a different "camera lens"
   camera.zoom = 3.0;
   camera.stepout = { 0.0, 0.0, 20.0 };

   for (int i=0; i<300; i++)
   {
      // Update the scene
      camera.spin += 0.01;

      // Draw the scene
      al_clear_to_color(ALLEGRO_COLOR{0.001, 0.004, 0.01, 1.0});
      scene.render();
      al_flip_display();
   }
}


