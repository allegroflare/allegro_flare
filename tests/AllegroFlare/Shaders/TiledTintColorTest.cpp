
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/TiledTintColor.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Shaders_TiledTintColorTest: public ::testing::Test {};
class AllegroFlare_Shaders_TiledTintColorWithAllegroRenderingFixtureTest :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_Shaders_TiledTintColorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shaders::TiledTintColor tiled_tint_color_shader;
}


TEST_F(AllegroFlare_Shaders_TiledTintColorTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Shaders/TiledTintColor",
     AllegroFlare::Shaders::TiledTintColor::TYPE
   );
}


TEST_F(AllegroFlare_Shaders_TiledTintColorTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Shaders::TiledTintColor tiled_tint_color_shader;
   EXPECT_EQ(AllegroFlare::Shaders::TiledTintColor::TYPE, tiled_tint_color_shader.get_type());
}


TEST_F(AllegroFlare_Shaders_TiledTintColorWithAllegroRenderingFixtureTest, activate__does_not_blow_up)
{
   AllegroFlare::Shaders::TiledTintColor tiled_tint_color_shader;
   tiled_tint_color_shader.initialize();
   tiled_tint_color_shader.activate();
}


TEST_F(AllegroFlare_Shaders_TiledTintColorWithAllegroRenderingFixtureTest,
   CAPTURE__with_the_tiled_tint_colorments__will_render_as_expected)
{
   AllegroFlare::Shaders::TiledTintColor tiled_tint_color_shader;
   tiled_tint_color_shader.initialize();

   ALLEGRO_BITMAP *image = get_bitmap_bin_ref().auto_get("cat_for_color_testing.jpg");

   // Some shader settings
   //tiled_tint_color_shader.set_hue_shift(0.1f);
   

   int passes = 120 * 4;
   ALLEGRO_COLOR tint_color = ALLEGRO_COLOR{1, 1, 1, 1};

   for (int i=0; i<passes; i++)
   {
      tint_color.r = 1.0 - (i / (float)passes);

      tiled_tint_color_shader.set_tint_color(tint_color);
      tiled_tint_color_shader.set_tint_color_is_used(true);

      // Render the test
      clear();
      al_draw_bitmap(image, 400, 300, 0);

      tiled_tint_color_shader.activate();
      al_draw_bitmap(image, 1000, 300, 0);
      tiled_tint_color_shader.deactivate();

      al_flip_display();
   }

   al_rest(1);
}


