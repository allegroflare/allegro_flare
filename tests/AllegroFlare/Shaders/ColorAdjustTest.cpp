
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/ColorAdjust.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Shaders_ColorAdjustTest: public ::testing::Test {};
class AllegroFlare_Shaders_ColorAdjustWithAllegroRenderingFixtureTest :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_Shaders_ColorAdjustTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shaders::ColorAdjust color_adjust_shader;
}


TEST_F(AllegroFlare_Shaders_ColorAdjustTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Shaders/ColorAdjust",
     AllegroFlare::Shaders::ColorAdjust::TYPE
   );
}


TEST_F(AllegroFlare_Shaders_ColorAdjustTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Shaders::ColorAdjust color_adjust_shader;
   EXPECT_EQ(AllegroFlare::Shaders::ColorAdjust::TYPE, color_adjust_shader.get_type());
}


TEST_F(AllegroFlare_Shaders_ColorAdjustWithAllegroRenderingFixtureTest, activate__does_not_blow_up)
{
   AllegroFlare::Shaders::ColorAdjust color_adjust_shader;
   color_adjust_shader.initialize();
   color_adjust_shader.activate();
}


TEST_F(AllegroFlare_Shaders_ColorAdjustWithAllegroRenderingFixtureTest,
   CAPTURE__with_the_color_adjustments__will_render_as_expected)
{
   AllegroFlare::Shaders::ColorAdjust color_adjust_shader;
   color_adjust_shader.initialize();

   ALLEGRO_BITMAP *image = get_bitmap_bin_ref().auto_get("cat_for_color_testing.jpg");

   // Some shader settings
   //color_adjust_shader.set_flat_color(ALLEGRO_COLOR{0.2, 0.8, 0.75, 1.0});
   //color_adjust_shader.set_flat_color_intensity(0.3f);
   //color_adjust_shader.set_hue_shift(0.1f);
   

   int passes = 120 * 4;
   float darkness = 0.0f;
   for (int i=0; i<passes; i++)
   {
      darkness += 0.006;
      //color_adjust_shader.set_darkness(0.2f);

      color_adjust_shader.set_hue_rotation((i / (float)passes));

      //color_adjust_shader.set_saturation(1.0 - (i / (float)passes));

      //color_adjust_shader.set_red_channel_multiplier(0.65f);
      //color_adjust_shader.set_green_channel_multiplier(0.5f);
      //color_adjust_shader.set_blue_channel_multiplier(1.3f);
         //color_adjust_shader.set_flat_color(ALLEGRO_COLOR{0.2, 0.8, 0.75, 1.0});
         //color_adjust_shader.set_flat_color_intensity(0.3);

      // Render the test
      clear();
      al_draw_bitmap(image, 400, 300, 0);

      color_adjust_shader.activate();
      al_draw_bitmap(image, 1000, 300, 0);
      color_adjust_shader.deactivate();

      al_flip_display();
   }

   al_rest(1);
}


