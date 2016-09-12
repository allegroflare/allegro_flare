



#include <allegro_flare/shadow_mask.h>




ShadowMask::point2d::point2d(float x, float y)
   : x(x)
   , y(y)
{}




void ShadowMask::update_surface()
{
   ALLEGRO_STATE previous_state;
   al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP | ALLEGRO_STATE_BLENDER);
   al_set_target_bitmap(surface);
   al_clear_to_color(al_map_rgb(0, 0, 0));
   al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);

   for (auto &point : points)
   {
      float half_w = al_get_bitmap_width(light_bitmap) * 0.5;
      float half_h = al_get_bitmap_height(light_bitmap) * 0.5;
      al_draw_bitmap(light_bitmap, point.x - half_w, point.y - half_h, 0);
   }

   al_restore_state(&previous_state);
}




ShadowMask::ShadowMask(int width, int height, ALLEGRO_BITMAP *light_bitmap)
   : surface(al_create_bitmap(width, height))
   , light_bitmap(light_bitmap)
{
   if (!light_bitmap) std::cout << "There was an error loading the light bitmap" << std::endl;
}




ShadowMask::~ShadowMask()
{
   al_destroy_bitmap(surface);
   al_destroy_bitmap(light_bitmap);
}




void ShadowMask::clear_points()
{
   points.clear();
}




void ShadowMask::add_point(float x, float y)
{
   points.push_back(point2d(x, y));
}




void ShadowMask::draw()
{
   update_surface();

   ALLEGRO_STATE previous_state;
   al_store_state(&previous_state, ALLEGRO_STATE_BLENDER);
   al_set_blender(ALLEGRO_ADD, ALLEGRO_DST_COLOR, ALLEGRO_ZERO);

   al_draw_bitmap(surface, 0, 0, 0);

   al_restore_state(&previous_state);
}




