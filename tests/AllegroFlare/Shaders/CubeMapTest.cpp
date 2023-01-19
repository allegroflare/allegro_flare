
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/CubeMap.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Camera3D.hpp>


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

   // TODO: setup object

   shader.initialize();
   shader.activate();

   int passes = 60;
   for (int i=0; i<passes; i++)
   {
      camera.setup_projection_on(get_display_backbuffer());
      clear();
      // TODO: render object
      al_flip_display();
   }

   shader.deactivate();
}


