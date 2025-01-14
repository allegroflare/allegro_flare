

#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


class AllegroFlare_Elements_Backgrounds_ParallaxWithZoomTest : public ::testing::Test
{};

class AllegroFlare_Elements_Backgrounds_ParallaxWithZoomTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/Backgrounds/ParallaxWithZoom.hpp>


#include <cmath>


TEST_F(AllegroFlare_Elements_Backgrounds_ParallaxWithZoomTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Backgrounds::ParallaxWithZoom parallax;
}


TEST_F(AllegroFlare_Elements_Backgrounds_ParallaxWithZoomTest, TYPE__has_the_expected_value)
{
   EXPECT_EQ("AllegroFlare/Elements/Backgrounds/ParallaxWithZoom", AllegroFlare::Elements::Backgrounds::ParallaxWithZoom::TYPE);
}


TEST_F(AllegroFlare_Elements_Backgrounds_ParallaxWithZoomTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::Backgrounds::ParallaxWithZoom parallax_background;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::ParallaxWithZoom::TYPE, parallax_background.get_type());
}


TEST_F(AllegroFlare_Elements_Backgrounds_ParallaxWithZoomTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::Backgrounds::ParallaxWithZoom parallax;
   EXPECT_THROW_GUARD_ERROR(
      parallax.render(),
      "AllegroFlare::Elements::Backgrounds::ParallaxWithZoom::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Elements_Backgrounds_ParallaxWithZoomTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Camera2D camera;
   AllegroFlare::Elements::Backgrounds::ParallaxWithZoom parallax;
   parallax.set_camera(&camera);
   parallax.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_Backgrounds_ParallaxWithZoomTestWithAllegroRenderingFixture,
   CAPTURE__render__will_draw_the_background_layers_in_the_expected_positions)
{
   AllegroFlare::Camera2D camera;
   camera.size = { 1920, 1080 };
   camera.set_zoom({ 0.8, 0.8 });
   //camera.set_zoom({ 0.1, 0.1 });

   //camera.set_size({1920, 1080});
   //camera.set_zoom({0.8, 0.8});

   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   AllegroFlare::Elements::Backgrounds::ParallaxWithZoom parallax(
      {
         {0, 0, 0.1, bitmap_bin["backgrounds/Sky3.png"]},
         {0, 0, 0.8, bitmap_bin["backgrounds/Cloud3a.png"]},
         {0, 0, 1.0, bitmap_bin["backgrounds/Cloud3b.png"]},

         //{0, 0, 0.1, bitmap_bin["backgrounds/Sky3.png"]},
         //{0, 0, 0.4, bitmap_bin["backgrounds/Cloud3a.png"]},
         //{0, 0, 0.8, bitmap_bin["backgrounds/Cloud3b.png"]},
      }
   );

   int passes = 60 * 3;
   for (int i=0; i<passes; i++)
   {
      // Update
      //parallax.set_offset_x(i * 8);
      //parallax.set_offset_y(sin((float)i/passes * 6.28) * 100);
      float zoom = 0.8 + sin(al_get_time()*3) * 0.2;
      zoom *= 0.2;
      camera.set_zoom({ zoom, zoom });
      camera.position.x = sin(al_get_time()*2) * 1200.0 * 2;
      //camera.position.y = sin(al_get_time()*2) * 1200.0 * 2;

      // Set some zoom
      //parallax.set_zoom(1.0 + sin(al_get_time()) * 0.2);

      // Set the camera
      parallax.set_camera(&camera);

      // Draw
      al_clear_to_color(ALLEGRO_COLOR{0.09, 0.09, 0.092, 1.0});
      parallax.render();
      al_flip_display();

      // flip
      sleep_for_frame();
   }

   //sleep_for(1);

   SUCCEED();
}


