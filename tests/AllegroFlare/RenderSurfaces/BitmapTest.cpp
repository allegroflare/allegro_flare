
#include <gtest/gtest.h>
#include <gmock/gmock.h> // for ::testing::Contains

#include <AllegroFlare/RenderSurfaces/Bitmap.hpp>

#define ALLEGRO_UNSTABLE
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>


class AllegroFlare_RenderSurfaces_BitmapTest : public ::testing::Test {};
class AllegroFlare_RenderSurfaces_BitmapTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_RenderSurfaces_BitmapTest, can_be_created_without_blowing_up)
{
   AllegroFlare::RenderSurfaces::Bitmap bitmap;
}


TEST_F(AllegroFlare_RenderSurfaces_BitmapTest, TYPE__has_the_expected_value)
{
   AllegroFlare::RenderSurfaces::Bitmap bitmap;
   EXPECT_EQ("AllegroFlare/RenderSurfaces/Bitmap", bitmap.get_type());
}


TEST_F(AllegroFlare_RenderSurfaces_BitmapTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::RenderSurfaces::Bitmap bitmap;
   EXPECT_EQ(AllegroFlare::RenderSurfaces::Bitmap::TYPE, bitmap.get_type());
}


TEST_F(AllegroFlare_RenderSurfaces_BitmapTest, setup_surface__will_set_the_surface_depth)
{
   al_init();
   // NOTE: Currently, a display is needed (to setup an OPENGL context) so that the ALLEGRO_UNSTABLE features
   // can be used along with ALLEGRO_OPENGL.
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *display = al_create_display(400*3, 240*3);
   AllegroFlare::RenderSurfaces::Bitmap render_surface;

   render_surface.setup_surface(400, 240, 8, 4);
   
   ALLEGRO_BITMAP *surface = render_surface.obtain_surface();
   EXPECT_EQ(4, al_get_bitmap_depth(surface));

   al_uninstall_system();
}


TEST_F(AllegroFlare_RenderSurfaces_BitmapTest, setup_surface__will_set_the_surface_multisamples)
{
   al_init();
   // NOTE: Currently, a display is needed (to setup an OPENGL context) so that the ALLEGRO_UNSTABLE features
   // can be used along with ALLEGRO_OPENGL.
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *display = al_create_display(400*3, 240*3);
   AllegroFlare::RenderSurfaces::Bitmap render_surface;

   render_surface.setup_surface(400, 240, 8, 4);
   
   ALLEGRO_BITMAP *surface = render_surface.obtain_surface();
   EXPECT_EQ(8, al_get_bitmap_samples(surface));

   al_uninstall_system();
}


TEST_F(AllegroFlare_RenderSurfaces_BitmapTest, setup_surface__will_set_the_surface_dimensions)
{
   al_init();
   // NOTE: Currently, a display is needed (to setup an OPENGL context) so that the ALLEGRO_UNSTABLE features
   // can be used along with ALLEGRO_OPENGL.
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *display = al_create_display(400*3, 240*3);
   AllegroFlare::RenderSurfaces::Bitmap render_surface;

   render_surface.setup_surface(400, 240, 8, 4);
   
   ALLEGRO_BITMAP *surface = render_surface.obtain_surface();
   EXPECT_EQ(400, al_get_bitmap_width(surface));
   EXPECT_EQ(240, al_get_bitmap_height(surface));

   al_uninstall_system();
}


TEST_F(AllegroFlare_RenderSurfaces_BitmapTest, set_as_target__will_set_the_surface_as_the_target_bitmap)
{
   al_init();
   // NOTE: Currently, a display is needed (to setup an OPENGL context) so that the ALLEGRO_UNSTABLE features
   // can be used along with ALLEGRO_OPENGL.
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *display = al_create_display(400*3, 240*3);
   AllegroFlare::RenderSurfaces::Bitmap render_surface;
   render_surface.setup_surface(400, 240, 8, 4);

   render_surface.set_as_target();
   ALLEGRO_BITMAP *expected_target_bitmap = render_surface.obtain_surface();
   ALLEGRO_BITMAP *actual_target_bitmap = al_get_target_bitmap();
   EXPECT_EQ(expected_target_bitmap, actual_target_bitmap);

   al_uninstall_system();
}


TEST_F(AllegroFlare_RenderSurfaces_BitmapTest,
   setup_surface_with_settings_that_match_display__will_create_a_surface_with_the_same_settings_as_a_display)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   al_init();
   int num_samples = 4;
   int num_depth = 32;

   // NOTE: Currently, a display is needed (to setup an OPENGL context) so that the ALLEGRO_UNSTABLE features
   // can be used along with ALLEGRO_OPENGL.
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_REQUIRE);
   al_set_new_display_option(ALLEGRO_SAMPLES, num_samples, ALLEGRO_REQUIRE);
   al_set_new_display_option(ALLEGRO_DEPTH_SIZE, num_depth, ALLEGRO_SUGGEST);

   ALLEGRO_DISPLAY *display = al_create_display(400*3, 240*3);
   ASSERT_NE(nullptr, display);

   int actual_display_depth = al_get_display_option(display, ALLEGRO_DEPTH_SIZE);
   ASSERT_EQ(num_samples, al_get_display_option(display, ALLEGRO_SAMPLES));
   //ASSERT_EQ(num_depth, actual_display_depth); // NOTE: This fails on my MacMini
                                                 // bug filed here: https://github.com/liballeg/allegro5/issues/1407
   std::vector<int> possible_permissible_depth_sizes = { 16, 24, 32 };
   ASSERT_THAT(possible_permissible_depth_sizes, ::testing::Contains(actual_display_depth)); // TODO: consider revising
                                                 // this test once https://github.com/liballeg/allegro5/issues/1407 is
                                                 // addressed and a fix is applied

   AllegroFlare::RenderSurfaces::Bitmap render_surface;
   render_surface.setup_surface_with_settings_that_match_display(display, 400, 240);

   EXPECT_EQ(num_samples, al_get_bitmap_samples(render_surface.obtain_surface()));
   EXPECT_EQ(actual_display_depth, al_get_bitmap_depth(render_surface.obtain_surface()));

   al_destroy_display(display);
   al_uninstall_system();
}


TEST_F(AllegroFlare_RenderSurfaces_BitmapTest,
   the_surface_will_render_to_the_display_backbuffer_as_expected)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   al_init();
   al_init_image_addon();
   AllegroFlare::BitmapBin bitmap_bin;
   bitmap_bin.set_path(deployment_environment.get_data_folder_path() + "bitmaps");


   int num_samples = 4;
   int num_depth = 32;

   // NOTE: Currently, a display is needed (to setup an OPENGL context) so that the ALLEGRO_UNSTABLE features
   // can be used along with ALLEGRO_OPENGL.
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_REQUIRE);
   al_set_new_display_option(ALLEGRO_SAMPLES, num_samples, ALLEGRO_REQUIRE);
   al_set_new_display_option(ALLEGRO_DEPTH_SIZE, num_depth, ALLEGRO_REQUIRE);

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ASSERT_NE(nullptr, display);

   AllegroFlare::RenderSurfaces::Bitmap render_surface;
   render_surface.setup_surface_with_settings_that_match_display(display, 1920/3, 1080/3);

   int loops = 120;
   for (int i=0; i<loops; i++)
   {
      // draw to the render surface
      render_surface.set_as_target();
      al_clear_to_color(ALLEGRO_COLOR{0.025, 0.03, 0.08, 1});
      ALLEGRO_BITMAP *toy_train_bitmap = bitmap_bin.auto_get("toy-train-02.png");
      al_draw_bitmap(toy_train_bitmap, 100+i, 100, 0);

      // blit the render surface to the display backbuffer
      al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));

      // setup a transform on our surface
      {
         ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(al_get_current_display());
         ALLEGRO_TRANSFORM transform;
         al_identity_transform(&transform);
         al_orthographic_transform(
            &transform,
            0,
            0,
            -1.0,
            // OPTION A:
               //al_get_bitmap_width(backbuffer),
               //al_get_bitmap_height(backbuffer),
            // OPTION B:
               al_get_bitmap_width(render_surface.obtain_surface()),
               al_get_bitmap_height(render_surface.obtain_surface()),
            1.0
         );
         al_use_projection_transform(&transform);
      }

      al_draw_bitmap(render_surface.obtain_surface(), i, i, 0);
      al_flip_display();
   }


   al_rest(1);

   bitmap_bin.clear();
   al_destroy_display(display);
   al_uninstall_system();
}


