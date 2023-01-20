
#include <gtest/gtest.h>

#include <AllegroFlare/RenderCache.hpp>


TEST(AllegroFlare_RenderCacheTest, can_be_created_without_blowing_up)
{
   AllegroFlare::RenderCache render_cache;
}


TEST(AllegroFlare_RenderCacheTest, setup_surface__will_not_blow_up)
{
   al_init();
   AllegroFlare::RenderCache render_cache;
   render_cache.setup_surface(400, 240, 8, 4);
   al_uninstall_system();
}


TEST(AllegroFlare_RenderCacheTest, setup_surface__will_set_the_bitmap_depth)
{
   al_init();
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);

   ALLEGRO_DISPLAY *display = al_create_display(400*3, 240*3);
   AllegroFlare::RenderCache render_cache;

   render_cache.setup_surface(400, 240, 8, 4);
   
   ALLEGRO_BITMAP *surface = render_cache.get_surface_bitmap();
   EXPECT_EQ(4, al_get_bitmap_depth(surface));

   al_uninstall_system();
}


