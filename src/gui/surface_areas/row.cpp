



#include <allegro_flare/gui/surface_areas/row.h>




UISurfaceAreaRow::UISurfaceAreaRow(float y, float h)
   : UISurfaceArea(0, y, 1, h)
{
   placement.align = vec2d(0, 0);
}




void UISurfaceAreaRow::draw_bounding_area()
{
}




bool UISurfaceAreaRow::collides(float x, float y)
{
   placement.transform_coordinates(&x, &y);
   if (y < placement.position.y) return false;
   if (y > placement.position.y + placement.size.y) return false;
   return true;
}




