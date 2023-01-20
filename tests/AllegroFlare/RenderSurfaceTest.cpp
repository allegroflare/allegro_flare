#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#define ALLEGRO_UNSTABLE
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_RenderSurfaceTest : public ::testing::Test {};
class AllegroFlare_RenderSurfaceTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/RenderSurface.hpp>


TEST_F(AllegroFlare_RenderSurfaceTest, can_be_created_without_blowing_up)
{
   AllegroFlare::RenderSurface render_surface;
}


TEST_F(AllegroFlare_RenderSurfaceTestWithAllegroRenderingFixture, setup_surface__will_not_blow_up)
{
   AllegroFlare::RenderSurface render_surface;
   render_surface.setup_surface(400, 240, 4, 8);
}


TEST_F(AllegroFlare_RenderSurfaceTest, setup_surface__will_set_the_bitmap_depth)
{
   al_init();
   // NOTE: Currently, a display is needed (to setup an OPENGL context) so that the ALLEGRO_UNSTABLE features
   // can be used along with ALLEGRO_OPENGL.
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *display = al_create_display(400*3, 240*3);
   AllegroFlare::RenderSurface render_surface;

   render_surface.setup_surface(400, 240, 8, 4);
   
   ALLEGRO_BITMAP *surface = render_surface.get_surface_bitmap();
   EXPECT_EQ(4, al_get_bitmap_depth(surface));

   al_uninstall_system();
}


TEST_F(AllegroFlare_RenderSurfaceTest, setup_surface__will_set_the_bitmap_multisamples)
{
   al_init();
   // NOTE: Currently, a display is needed (to setup an OPENGL context) so that the ALLEGRO_UNSTABLE features
   // can be used along with ALLEGRO_OPENGL.
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *display = al_create_display(400*3, 240*3);
   AllegroFlare::RenderSurface render_surface;

   render_surface.setup_surface(400, 240, 8, 4);
   
   ALLEGRO_BITMAP *surface = render_surface.get_surface_bitmap();
   EXPECT_EQ(8, al_get_bitmap_samples(surface));

   al_uninstall_system();
}


