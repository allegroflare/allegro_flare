



#include <allegro_flare/gui/surface_areas/bitmap_alpha.h>
#include <allegro_flare/color.h>




UISurfaceAreaBitmapAlpha::UISurfaceAreaBitmapAlpha(float x, float y, ALLEGRO_BITMAP *bitmap)
   : UISurfaceArea(x, y, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap))
   , bitmap(bitmap)
{}




bool UISurfaceAreaBitmapAlpha::collides(float x, float y)
{
   if (!placement.collide(x, y)) return false;

   // TODO will need to account for nested transforms
   placement.transform_coordinates(&x, &y);

   ALLEGRO_COLOR pixel_color = al_get_pixel(bitmap, x, y);

   if (pixel_color.a < 0.001) return false;
   return true;
}




void UISurfaceAreaBitmapAlpha::draw_bounding_area()
{
   placement.draw_box(color::color(color::aliceblue, 0.2), true);
}




