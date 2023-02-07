
#include <gtest/gtest.h>

#include <AllegroFlare/RenderSurfaces/Bitmap.hpp>

#define ALLEGRO_UNSTABLE
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


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
   FOCUS__setup_surface_with_settings_that_match_display__will_create_a_surface_with_the_same_settings_as_a_display)
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
   al_set_new_display_option(ALLEGRO_DEPTH_SIZE, num_depth, ALLEGRO_REQUIRE);

   ALLEGRO_DISPLAY *display = al_create_display(400*3, 240*3);
   ASSERT_NE(nullptr, display);
   ASSERT_EQ(num_samples, al_get_display_option(display, ALLEGRO_SAMPLES));
   ASSERT_EQ(num_depth, al_get_display_option(display, ALLEGRO_DEPTH_SIZE));

   AllegroFlare::RenderSurfaces::Bitmap render_surface;
   render_surface.setup_surface_with_settings_that_match_display(display, 400, 240);

   EXPECT_EQ(num_samples, al_get_bitmap_samples(render_surface.obtain_surface()));
   EXPECT_EQ(num_depth, al_get_bitmap_depth(render_surface.obtain_surface()));

   al_destroy_display(display);
   al_uninstall_system();
}


// DEBUGGING:
#include <AllegroFlare/DeploymentEnvironment.hpp>
TEST_F(AllegroFlare_RenderSurfaces_BitmapTest,
   DISABLED__FOCUS__the_surface_will_render_to_the_display_backbuffer_as_expected)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   al_init();
   al_init_image_addon();
   AllegroFlare::BitmapBin bitmap_bin;
   bitmap_bin.set_path(deployment_environment.get_data_folder_path() + "bitmaps");

   // NOTE: Currently, a display is needed (to setup an OPENGL context) so that the ALLEGRO_UNSTABLE features
   // can be used along with ALLEGRO_OPENGL.
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *display = al_create_display(400*3, 240*3);
   int display_num_samples = al_get_display_option(display, ALLEGRO_SAMPLES);
   int display_depth_size = al_get_display_option(display, ALLEGRO_DEPTH_SIZE);
   AllegroFlare::RenderSurfaces::Bitmap render_surface(
         400,
         240,
         display_num_samples,
         display_depth_size
   ); // NOTE: this should be identical to the display
      // for the purpose of blitting with speed.
   render_surface.initialize();

   render_surface.set_as_target();

   ALLEGRO_BITMAP *toy_train_bitmap = bitmap_bin.auto_get("toy-train-02.png");

   al_draw_bitmap(toy_train_bitmap, 100, 100, 0);

   al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));

   al_draw_bitmap(render_surface.obtain_surface(), 0, 0, 0);
   al_flip_display();

   al_rest(2);

   bitmap_bin.clear();
   al_destroy_display(display);
   al_uninstall_system();
}


