
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/AllegroDefault.hpp>


TEST(AllegroFlare_Shaders_AllegroDefaultTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shaders::AllegroDefault allegro_default;
}


TEST(AllegroFlare_Shaders_AllegroDefaultTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Shaders::AllegroDefault shader;
   EXPECT_EQ("AllegroFlare/Shaders/AllegroDefault", shader.get_type());
}


TEST(AllegroFlare_Shaders_AllegroDefaultTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Shaders::AllegroDefault shader;
   EXPECT_EQ(AllegroFlare::Shaders::AllegroDefault::TYPE, shader.get_type());
}


TEST_F(AllegroFlare_Shaders_CubeMapWithAllegroRenderingFixtureTest, VISUAL__will_appear_as_expected)
{
   AllegroFlare::Shaders::CubeMap shader;
   AllegroFlare::Camera3D camera;
   AllegroFlare::ModelBin model_bin;
   AllegroFlare::Model3D *model;

   model_bin.set_path(get_fixtures_path() + "models");
   model = model_bin["rounded_unit_cube-01.obj"];

   // TODO: setup object

   shader.initialize();
   shader.activate();

   int passes = 60;
   for (int i=0; i<passes; i++)
   {
      camera.setup_projection_on(get_display_backbuffer());
      clear();

      model->draw();

      // TODO: render object
      al_flip_display();
   }

   shader.deactivate();
}


