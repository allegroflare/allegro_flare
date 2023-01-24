
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


