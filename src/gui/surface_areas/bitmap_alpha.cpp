



#include <allegro_flare/gui/surface_areas/bitmap_alpha.h>
#include <allegro_flare/color.h>




UISurfaceAreaBitmapAlpha::UISurfaceAreaBitmapAlpha(float x, float y, ALLEGRO_BITMAP *bitmap)
   : UISurfaceArea(x, y, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap))
   , bitmap(bitmap)
   , alpha_threshold(0.001)
{}




bool UISurfaceAreaBitmapAlpha::collides(float x, float y)
{
   if (!placement.collide(x, y)) return false;

   placement.transform_coordinates(&x, &y);
   ALLEGRO_COLOR pixel_color = al_get_pixel(bitmap, x, y);

   if (pixel_color.a <= alpha_threshold) return false;
   return true;
}




void UISurfaceAreaBitmapAlpha::draw_bounding_area()
{
   placement.draw_box(color::color(color::aliceblue, 0.2), true);
}




void UISurfaceAreaBitmapAlpha::set_alpha_threshold(float threshold)
{
   alpha_threshold = threshold;
}




float UISurfaceAreaBitmapAlpha::get_alpha_threshold()
{
   return alpha_threshold;
}




ALLEGRO_BITMAP *UISurfaceAreaBitmapAlpha::get_surface_area_bitmap()
{
   return bitmap;
}




