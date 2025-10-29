
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/Cubemap.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/CubemapBuilder.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <cmath>


class AllegroFlare_Shaders_CubemapTest: public ::testing::Test {};
class AllegroFlare_Shaders_CubemapWithAllegroRenderingFixtureTest :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_Shaders_CubemapTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shaders::Cubemap shader;
}


TEST_F(AllegroFlare_Shaders_CubemapTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Shaders::Cubemap shader;
   EXPECT_EQ("AllegroFlare/Shaders/Cubemap", shader.get_type());
}


TEST_F(AllegroFlare_Shaders_CubemapTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Shaders::Cubemap shader;
   EXPECT_EQ(AllegroFlare::Shaders::Cubemap::TYPE, shader.get_type());
}


TEST_F(AllegroFlare_Shaders_CubemapWithAllegroRenderingFixtureTest, initialize__will_not_blow_up)
{
   AllegroFlare::Shaders::Cubemap shader;
   shader.initialize();
}


TEST_F(AllegroFlare_Shaders_CubemapWithAllegroRenderingFixtureTest,
   VISUAL__when_reflecting__will_appear_as_expected)
{
   AllegroFlare::Shaders::Cubemap shader;
   AllegroFlare::Camera3D camera;
   AllegroFlare::ModelBin model_bin;
   AllegroFlare::Model3D *model;
   AllegroFlare::Placement3D object_placement;
   AllegroFlare::CubemapBuilder builder;
   std::string cube_map_texture_filename = get_fixtures_path() + "/bitmaps/black_prism_1-01.png";
   AllegroFlare::Cubemap *cube_map = builder.glsl_create_cubemap_from_vertical_strip(cube_map_texture_filename.c_str());

   camera.stepout = {0, 0, 4};  // step back from the origin
   camera.tilt = 0.35;          // look down slightly

   model_bin.set_path(get_fixtures_path() + "models");
   model = model_bin["rounded_unit_cube-01.obj"];

   // TODO: setup object

   shader.initialize();
   shader.set_cube_map(cube_map);

   // TODO: Include camera movement

   float number_of_seconds = 3.5f;
   int loops = (int)(number_of_seconds * 60.0f);
   for (int i=0; i<loops; i++)
   {
      // update
      //camera.tilt += 0.01;
      object_placement.rotation.y += 0.001;
      object_placement.rotation.x += 0.00073;

      // draw
      camera.setup_projection_on(get_display_backbuffer());
      al_clear_depth_buffer(1);
      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.105, 0.12, 1.0});

      shader.set_object_placement(&object_placement); // NOTE: For now, this has to be set before activating the shader
                                                      // TODO: Update this behavior so the value can be set
                                                      // after initialization
      shader.activate();
      shader.set_camera_position(camera.get_real_position());
      model->draw();
      shader.deactivate();

      al_flip_display();
   }
}


TEST_F(AllegroFlare_Shaders_CubemapWithAllegroRenderingFixtureTest,
   VISUAL__when_not_reflecting__will_appear_as_expected)
{
   // NOTE: ***This test is still in development***
   // The skybox does not seem to track with the position of the camera when the camera is moving
   AllegroFlare::Shaders::Cubemap shader;
   AllegroFlare::Camera3D camera;
   AllegroFlare::ModelBin model_bin;
   AllegroFlare::Model3D *model;
   AllegroFlare::Placement3D object_placement;
   AllegroFlare::CubemapBuilder builder;
   std::string cube_map_texture_filename = get_fixtures_path() + "/bitmaps/sky5_with_grid_orig.png";
   AllegroFlare::Cubemap *cube_map = builder.glsl_create_cubemap_from_vertical_strip(cube_map_texture_filename.c_str());

   // NOTE: The near plane is 1, so scaling the boxes object placement
   object_placement.scale = { 10, 10, 10 };

   camera.stepout = {0, 0, 10};  // TODO: Test with different camera orientations, positions
   camera.tilt = 0.35;           // 0.35 = look down slightly

   model_bin.set_path(get_fixtures_path() + "models");
   //model = model_bin["rounded_unit_cube-01.obj"];
   model = model_bin["centered_unit_cube-02.obj"];

   // TODO: setup object

   shader.initialize();
   shader.set_cube_map(cube_map);
   shader.set_reflecting(false);

   float number_of_seconds = 4.5f;
   int loops = (int)(number_of_seconds * 60.0f);
   for (int i=0; i<loops; i++)
   {
      // update
      camera.spin -= 0.01;
      camera.tilt = std::sin(i * 0.02) * 0.2;
      //camera.tilt += 0.01;
      //object_placement.rotation.y += 0.001;
      //object_placement.rotation.x += 0.00073;

      // TODO: Include camera movement here
      camera.position.x += 0.025 * 5;
      //camera.position.x += 0.025;
      camera.position.z -= 0.025 * 2;
      //object_placement.position = camera.position;

      // draw
      camera.setup_projection_on(get_display_backbuffer());
      al_clear_depth_buffer(1);
      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.105, 0.12, 1.0});

      if (!shader.get_reflecting())
      {
         AllegroFlare::Vec3D camera_real_position = camera.get_real_position();
         object_placement.position = camera_real_position;
      }
      shader.set_camera_position(camera.get_real_position());
      shader.set_camera_viewing_direction(camera.get_viewing_direction());
      shader.set_object_placement(&object_placement); // NOTE: For now, this has to be set before activating the shader
                                                      // TODO: Update this behavior so the value can be set
                                                      // after initialization
      //shader.set_camera_position(camera.get_real_position());
      //shader.set_camera_viewing_direction(camera.get_viewing_direction());
      shader.activate();
      //shader.set_camera_position(object_placement.position); // TODO: This one seems to work nicely
      //shader.set_camera_position(camera.get_real_position());
      //shader.set_camera_viewing_direction(camera.get_viewing_direction());
      model->draw();

      shader.deactivate();

      al_flip_display();
   }
}


