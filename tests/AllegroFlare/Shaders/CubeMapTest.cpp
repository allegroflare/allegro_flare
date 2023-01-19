
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/CubeMap.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/CubemapBuilder.hpp>


class AllegroFlare_Shaders_CubeMapTest: public ::testing::Test {};
class AllegroFlare_Shaders_CubeMapWithAllegroRenderingFixtureTest :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_Shaders_CubeMapTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shaders::CubeMap shader;
}


TEST_F(AllegroFlare_Shaders_CubeMapTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Shaders::CubeMap shader;
   EXPECT_EQ("AllegroFlare/Shaders/CubeMap", shader.get_type());
}


TEST_F(AllegroFlare_Shaders_CubeMapTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Shaders::CubeMap shader;
   EXPECT_EQ(AllegroFlare::Shaders::CubeMap::TYPE, shader.get_type());
}


TEST_F(AllegroFlare_Shaders_CubeMapWithAllegroRenderingFixtureTest, initialize__will_not_blow_up)
{
   AllegroFlare::Shaders::CubeMap shader;
   shader.initialize();
}


TEST_F(AllegroFlare_Shaders_CubeMapWithAllegroRenderingFixtureTest, VISUAL__will_appear_as_expected)
{
   AllegroFlare::Shaders::CubeMap shader;
   AllegroFlare::Camera3D camera;
   AllegroFlare::ModelBin model_bin;
   AllegroFlare::Model3D *model;
   AllegroFlare::CubemapBuilder builder;
   std::string cube_map_texture_filename = get_fixtures_path() + "/bitmaps/sky5_with_grid.png";
   AllegroFlare::Cubemap *cube_map = builder.glsl_create_cubemap_from_vertical_strip(cube_map_texture_filename.c_str());

   camera.stepout = {0, 0, 4};  // step back from the origin
   camera.tilt = 0.35;          // look down slightly

   model_bin.set_path(get_fixtures_path() + "models");
   model = model_bin["rounded_unit_cube-01.obj"];

   // TODO: setup object

   shader.initialize();

   float number_of_seconds = 1.0f;
   int loops = (int)(number_of_seconds * 60.0f);
   for (int i=0; i<loops; i++)
   {
      // update
      camera.spin += 0.01;

      // draw
      camera.setup_projection_on(get_display_backbuffer());
      al_clear_depth_buffer(1);
      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.105, 0.12, 1.0});

      shader.activate();
      model->draw();
      shader.deactivate();

      al_flip_display();
   }
}


